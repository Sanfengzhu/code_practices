#include "apue.h"
#include <dirent.h>

int main(int argc, char *args[]){
    DIR *dr;
    struct dirent *dirp;
    if (argc != 2){
        err_quit("argc less :%d", argc);
    }
    if ((dr = opendir(args[1])) == NULL){
        err_sys("args error :%s", args[1]);
    }
    while((dirp = readdir(dr))!= NULL){
        printf("%s\n",dirp->d_name);
    }
    closedir(dr);
    exit(0);
}
