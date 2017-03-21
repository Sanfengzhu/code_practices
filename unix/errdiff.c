#include "apue.h"
#include "errno.h"

int main(int argc, char *args[]){
    errno = EACCES;
    fprintf(stderr, "EACCESS : %s\n", strerror(errno));
    errno = ENOENT;
    perror(args[0]);
    exit(0);
}
