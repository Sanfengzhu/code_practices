#include "apue.h"
#include <fcntl.h>

int main(int argc, char *args[]){
    int val;
    if ( argc != 2){
        err_quit("argc err");
    }
    if ((val = fcntl(atoi(args[1]), F_GETFL, 0))== -1){
        err_sys("fcnt error");
    }
    switch(val & O_ACCMODE){
        case O_RDONLY:
            printf("read only\n");
            break;
        case O_WRONLY:
            printf("write only\n");
            break;
        case O_RDWR:
            printf("write and read both\n");
            break;
        default:
            printf("bad val\n");
            break;
    }
    if (val & O_APPEND){
        printf("append\n");
    }
    printf("%d\n", val);
    exit(0);
}
