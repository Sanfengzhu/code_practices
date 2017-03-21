#include "apue.h"
#include <errno.h>

static void err_doit(int errnoflag, int error, const char *fmt, va_list ap){
    char buf[MAXLINE];
    vsnprintf(buf, MAXLINE, fmt, ap);
    if(errnoflag){
        snprintf(buf + strlen(buf), MAXLINE-strlen(buf), ": %s",strerror(error));
    }
    strcat(buf, "\n"); /* 连接buf 和\n 结果写入 buf，覆盖掉原来buf结尾处的\0 */
    fflush(stdout);
    fputs(buf,stderr); 
    fflush(NULL); /* 冲洗缓冲区，把所有打开的file都更新 */
}

/**
 * Fatal error related to system call
 * print a message and terminate
 */
void err_sys(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}

/**
 * Fatal error unrelated to system call
 * print a message and termincate
 */
void err_quit(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    exit(1);
}

/**
 * Unfatal error related to system call
 * print a message and return
 */
void err_ret(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
}

