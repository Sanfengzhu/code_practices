#include <glog/logging.h>
#include <iostream>
#include <gflags/gflags.h>
#include <stdlib.h>     /* _Exit, EXIT_FAILURE */
#include <unistd.h>

int main(int argc, char *argv[])
{
    FLAGS_log_dir = "./";
    FLAGS_logbufsecs = 1;
    ::google::InitGoogleLogging(argv[0]);
    int i;
    for(i = 0; i < 10000; i++){
        LOG(ERROR) << "xdddsffdddf" << i;
        LOG(ERROR) << "xdddsffdddf" << i;
        LOG(ERROR) << "xdddsffdddf" << i;
        LOG(ERROR) << "xdddsffdddf" << i;
        usleep(10000);
    }
    LOG(ERROR) << "log info";
    _Exit(EXIT_FAILURE);
    return 0;
}
