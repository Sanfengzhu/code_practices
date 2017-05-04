#include "apue.h"
#include <iostream>

int main(){
    std::cout << "parent process" << std::endl;
    if(!vfork()){
        std::cout << "child process" << std::endl;
        sleep(100);
    }
    return 0;
}
