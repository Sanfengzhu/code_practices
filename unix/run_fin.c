#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);

int main(void){
    int pid;
    int status;
    char buf[MAXLINE];
    printf("%% ");

    if(signal(SIGINT,sig_int) == SIG_ERR){
        err_sys("signal error");
    }

    while(fgets(buf,MAXLINE, stdin) != NULL){
        if (buf[strlen(buf) - 1] == '\n'){
            buf[strlen(buf) - 1] = '\0';
        }

        if((pid = fork()) < 0){
            err_sys("fork error");
        }else if (pid == 0){
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute : %s", buf);
            exit(127);
        }
        if((pid = waitpid(pid, &status, 0)) < 0){
            err_sys("waitpid error");
        }
        printf("%% ");
    }
    exit(0);
}

static void sig_int(int signo){
    fprintf(stderr, "interrupt %d\n%% ", signo);
}
