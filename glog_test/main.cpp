//#include <glog/logging.h>
#include <iostream>
#include <gflags/gflags.h>

DEFINE_int32(tera_master_load_balance_ts_load_threshold, 5000, "threshold of one tabletnode in QPS load-balance decision");


int main(int argc, char *argv[])
{
    google::ParseCommandLineFlags(&argc, &argv, true);
    int node_read_pending = 12;
    if (node_read_pending <= FLAGS_tera_master_load_balance_ts_load_threshold) {
        std::cout<< "aaa\n";
    }
    std::cout << "ddddd\n";
    std::cout << FLAGS_tera_master_load_balance_ts_load_threshold << "\n";
    /*
    FLAGS_log_dir = "./";
    ::google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "log info";
    */
    return 0;
}
