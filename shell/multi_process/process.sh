# curl call one by one from query_file
function mulit_process(){
    SEND_THREAD_NUM=40   #设置线程数，在这里所谓的线程，其实就是几乎同时放入后台（使用&）执行的进程。
    tmp_fifofile="/tmp/$$.fifo" # 脚本运行的当前进程ID号作为文件名
    mkfifo "$tmp_fifofile" # 新建一个随机fifo管道文件
    exec 6<>"$tmp_fifofile" # 定义文件描述符6指向这个fifo管道文件
    rm "$tmp_fifofile"
    for ((i=0;i<$SEND_THREAD_NUM;i++));do
    echo # for循环 往 fifo管道文件中写入13个空行
    done >&6

	# init your veriables
	# mkdir dir for each process
	mkdir -p ${result}
    now_line=1
    all_line=`cat ${somefile} | wc -l`
    cat ${somefile} | while read line
    do
        read -u6
        {
			echo "${result} : ${now_line} : ${line}"
            sleep 1
            echo >&6
        } &
		processbar $now_line $all_line
        now_line=$(($now_line+1))
    done
    wait
    exec 6>&-
}
