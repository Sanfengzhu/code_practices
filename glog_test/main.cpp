#include <glog/logging.h>
#include <gflags/gflags.h>

int main(int argc, char *argv[])
{
    FLAGS_log_dir = "./";
    ::google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "log info";
    return 0;
}
