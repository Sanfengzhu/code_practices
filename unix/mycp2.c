#include "apue.h"

int main(int argc, char * args[]){
    char c;
    while((c = getc(stdin)) != EOF){
        if(putc(c, stdout) == EOF){
            err_sys("write err");
        }
    }
    if(ferror(stdin)){
        err_sys("read err");
    }
    exit(0);
}
