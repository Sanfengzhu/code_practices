#include <iostream>
#include <unistd.h>
#include <sched.h>
#include <stdint.h>
#include <stdlib.h>

int32_t cpu_cnt = sysconf(_SC_NPROCESSORS_CONF);

void print_mask(const cpu_set_t *mask){

    for (__cpu_mask i = 0; i < sizeof(mask->__bits); ++i) {
        std::cout << mask->__bits[i] << " ";
        if(i >= cpu_cnt-1){
            break;
        }
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    if( argc < 2){
        return -1;
    }
    int cpu_id = atoi(argv[1]);
    std::cout << cpu_id << std::endl;
    std::cout << "cpu count : " << cpu_cnt << std::endl;
    std::cout << "begin to set cpu" << std::endl;
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu_id, &mask);
    if(sched_setaffinity(0, sizeof(mask), &mask) == -1){
        return -1;
    }
    print_mask(&mask);
    cpu_set_t last_mask;
    CPU_ZERO(&last_mask);
    if(sched_getaffinity(0, sizeof(last_mask), &last_mask) == -1){
        return -1;
    }
    for(int32_t i = 0; i < cpu_cnt; i++){
        if(CPU_ISSET(i, &last_mask)){
            std::cout << getpid() << "\t in cpu : " << i << std::endl;
        }
    }

    for (int i = 0; i < 0; ++i) {
        sleep(1);
        std::cout << i << std::endl;
    }
    std::cout << "end" << std::endl;
    return 0;
}
