#include "apue.h"
#include <sys/wait.h>
#include <iostream>

void call_child_vfork(){
    // vfork 出的子进程和父进程共享资源，需要子进程调用exit或者
    // exec族函数否则父进程一直处于D状态
    pid_t pid;
    std::cout << "parent process begin " << getpid() << std::endl;
    if((pid = vfork()) == 0){
    // if((pid = fork()) == 0){
        std::cout << "child process begin " << getpid() << std::endl;
        printf("child %d\n", pid);
        sleep(10);
        std::cout << "child process end" << std::endl;
        // return 0;
        exit(0);
    }
    printf("parent %d\n", pid);
    if (waitpid(pid, NULL, 0) == 0) {
        std::cout << "child process exited" << std::endl;
    }
    sleep(5);
    std::cout << "parent process end" << std::endl;
}

void call_child_fork(){
    // fork 出的子进程和父进程不共享资源
    pid_t pid;
    std::cout << "parent process begin " << getpid() << std::endl;
    // if((pid = vfork()) == 0){
    if((pid = fork()) == 0){
        std::cout << "child process begin " << getpid() << std::endl;
        printf("child %d\n", pid);
        sleep(10);
        std::cout << "child process end" << std::endl;
        return;
        // exit(0);
    }
    printf("parent %d\n", pid);
    if (waitpid(pid, NULL, 0) == 0) {
        std::cout << "child process exited" << std::endl;
    }
    sleep(5);
    std::cout << "parent process end" << std::endl;
}



int main(){
    std::cout << std::endl << "by fork" << std::endl;
    call_child_fork();
    std::cout << std::endl << "by vfork" << std::endl;
    call_child_vfork();
    return 0;
}
