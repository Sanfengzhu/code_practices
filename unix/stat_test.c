#include "apue.h"
#include <sys/stat.h>
#include <sys/fcntl.h>

typedef struct timespec TS;

int main(void)
{
	struct stat buf;
	char file_path[] = "./";
	int fd;
	if((fd = open(file_path, O_RDONLY)) == -1){
		err_sys("open error");
	}
	if(fstat(fd, &buf) == -1){
		err_sys("stat error");
	}
	gid_t gid = buf.st_gid;
	uid_t uid = buf.st_uid;
	mode_t m = buf.st_mode;
	if(S_ISREG(m)){
		printf("is reg\n");
	}else if(S_ISDIR(m)){
		printf("is dir\n");
	}
	printf("m = %o\n", m);

	printf("gid= %d\n", gid);
	printf("uid= %d\n", uid);
	blkcnt_t b = buf.st_blocks;
	printf("b= %lld\n", b);
	TS t = buf.st_ctimespec;
	long tns = t.tv_sec;
	printf("tns = %ld\n", tns);
	close(fd);
	return 0;
}
