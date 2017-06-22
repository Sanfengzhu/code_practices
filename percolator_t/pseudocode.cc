class Transaction {
    struct Write { Row row; Column col; string value; };
    vector<Write> writes_;
    int start_ts_;

    // 事务构造函数会调用 timestamp oracle 拿到当前的时间戳，作为事务启动的时间戳
    // 这个时间戳决定了后面Get操作拿到的快照的版本
    // 只能是小于等于这个时间戳里面的最大版本
    Transaction() : start_ts_(oracle.GetTimestamp()) {}
    // set中的内容直到commit前都是被缓存的 （Q1：缓存到客户端，还是缓存到bigtable）
    void Set(Write w) { writes_.push_back(w); }
    
    bool Get(Row row, Column c, string* value) {
        while (true) {
            bigtable::Txn T = bigtable::StartRowTransaction(row);
            // t1:primary perwrite
            // t2:X cell prewrite
            // t3:primary commit
            // t4:X cell commit
            //                      t1        t2       t3     t4
            // T1                   |---------|--------|------|
            // ==================================================================================
            // T2  |----|----|---|    OK
            // T3                                                |----|----|----| OK
            // 
            // T4                               |----|-----|----|  
            //                           get的时候发现T1里面X已经prewrite，primary没commit，让T1提交(wait) or 让T1回滚(roll-back)
            // 
            // T5                         |----|----|----|----|  get没拿到T1里面X的lock，读到数据
            // 
            // T6                      |----|----|----|---| get没拿到T1里面的lock，准备做prewrite的时候发现冲突了T6跪了
            // 
            // T7                                        |-----|----|----|---| 
            //                           get的时候发现X已经prewrite，primary已经commit，单还没轮到x提交，这时(wait)或者帮着做(roll-forward)
            //
            if (T.Read(row, c + "lock", [0, start_ts_])) {
                // 在其他事务主提交的时候，会先check主的lock，在那个事务启动的时间戳上是否存在，如果存在才做提交
                // 在清除对应的lock先检查主，确认主没提交，如果主lock存在说明另一个事务没提交，这时候可以清除（会不会出现互相都hang在prewrite好久？）
                // 一个worker启动的时候在zk上注册一个lock，如果其他事务读到那个lock说明他还在，否则已经不在了。如果在，就等等，如果不在就处理。
                // zk的lock用超时时间限制，如果超时时间到了，会帮忙清除lock信息，work工作的时候会往zk的lock上蓄时间
                BackoffAndMaybeCleanupLock(row, c);
                continue;
            }
            // 拿最后一次写的时间戳,如果拿不到就是没有数据，如果拿到了根据
            // 写write的时候写入的start_ts能拿到对应data列的value值
            latest_write = T.Read(row, c + "write", [0, start_ts_]);
            if (!latest_write.found()) return false // 没数据
            int data_ts = latest_write.start_timestamp();
            *value = T.Read(row, c+"data", [data_ts, data_ts]);
            return true;
        }
    }
    // 传入的第二个参数是为了拿到主锁
    // 主锁的作用：为了处理客户端失败，主cell结构{row，col}只是用来定位那个cell，
    // 如果A事务执行过程被B事务失败遗留下来的锁冲突了，A会负责清理这些锁
    bool Prewrite(Write w, Write primary) {
        Column c = w.col;
        bigtable::Txn T = bigtable::StartRowTransaction(w.row);

        // write 列存的是在commit阶段获得的 （提交时间戳commit_ts -> 事务启动时间戳start_ts）
        // 通过单行事务读要处理的行里面的write列，时间戳要大于等于当前事务启动的时间戳
        // 读到数据，说明对应行列的数据已经在commit阶段往write列写入了提交时间戳，
        //   当前prewrite失败 （Q4：为什么要从等于开始？）
        // 写写冲突在这里就被处理掉了，如下
        //   t1      t3
        //     pre     commit
        //T1 |-------|--------|
        //
        //      t2
        //       pre      commit
        //T2    |-------|--------|
        // 
        //
        if (T.Read(w.row, c + "write", [start_ts_, MAX_TS]) return false;
        // lock 列存的是 启动时间戳->主锁信息，会在提交阶段按照提交的时间戳标记为删除，
        // 在提交阶段只有主cell是用单行事务的方式提交的，其他的cells并没有在事务的保护下操作
        // 还是有可能出现当前要prewrite的cell刚好不是主，这个cell在另一个事务提交阶段只做了
        // 写write列，但是没做删lock内容
        if (T.Read(w.row, c + "lock", [0, MAX_TS]) return false; 

        T.Write(w.row, c + "data", start_ts_, w.value);
        T.Wtite(w.row, c + "lock", start_ts_, {primary.row, primary.col});
        return T.Commit();
    }

    bool Commit() {
        Write primary = write_[0]; // 真的是随便拿一个
        vector<Write> secondaries(writes_.begin() + 1, writes_end());
        // 任何一个prewrite 都可能会失败，那些成功的部分bigtable已经写入了
        // 对应cell prewrite start_ts_对应的data【value】和lock【primary info】
        // 谁去处理他们，在处理之前，如果其他事务也涉及到对应的cell，
        // 那在读lock的时候会读到信息引起prewrite的失败
        if (!Prewrite(primary, primary) return false;
        // yy 主prewrite完了，这部分可以做并行处理
        for (Write w : secondaries) {
            if (!Prewrite(w, primary)) return false;
        }
        
        int commit_ts = oracle_.GetTimestamp();
        Write p = primary;
        bigtable::Txn T = bigtable::StartRowTransaction(p.row);
        // 其他的事务在prewrite的阶段都会先单行事务的先读他起始时间戳到无穷大是否有lock，
        // 这里单行事务读lock就是保证，他写入的lock还是有效的
        // 这个检查不是防御性的，在其他事务的Get中可能会干掉这个时间戳的lock
        if (!T.Read(p.row, p.col + "lock", [start_ts_,start_ts_]))
            return false;
        T.Write(p.row, p.col + "write", commit_ts, start_ts_);
        // 标记当前提交时间戳之前的lock都是失效的
        T.Erase(p.row, p.col + "lock", commit_ts);
        // 如果主没有提交成功，这时候所有的要写的cell都是prewrite状态的。
        if (!T.Commit)) return false;
        // yy 主提交完了，这部分也可以做并行处理
        for ( Write w : secondaries) {
            bigtable::Write(w.row, w.col + "write", commit_ts, start_ts_);
            bigtable::Erase(w.row, w.col + "lock", commit_ts);
        }
        return true;
    }
}
