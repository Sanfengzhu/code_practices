#include "apue.h"
#include <fcntl.h>
#include <limits.h>

int main(void){
    char pathname[PATH_MAX] = "/tmp/u";
    char buf1[10] = "1234567890";
    char buf2[] = "asdfghjklq";
    int fd;
    //close(STDERR_FILENO);
    if((fd = open(pathname, O_RDWR | O_EXCL | O_APPEND, FILE_MODE)) < 0){
        err_sys("open err");
    }
    ssize_t write_num;
    if((write_num = write(fd, buf1, strlen(buf1))) != 10){
        err_sys("write err");
    }
    off_t offset = lseek(fd, 0, SEEK_CUR);
    printf("%d\n", offset);
    offset = lseek(fd, 10, SEEK_CUR);
    printf("%d\n", offset);
    if((write_num = write(fd, buf2, strlen(buf2))) != 10){
        err_sys("write err");
    }
    offset = lseek(fd, 0, SEEK_CUR);
    printf("%d\n", offset);
    ssize_t read_num;
    lseek(fd,-5,SEEK_END);
    if((read_num = read(fd,buf2,5))== -1){
        err_sys("read err");   
    }else if(read_num == 0){
        printf("read @ end");
    }else{
        printf("%s",buf2);
    }
    close(fd);
    exit(0);
}

