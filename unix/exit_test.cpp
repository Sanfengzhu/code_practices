#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    FILE *fp = fopen("pid.c", "r");
    char buf[10];
    int c;
    while(c = fread(buf, sizeof(char), 20, fp) > 0){
        std::cout << c << " " << buf << std::endl;
    }
    fclose(fp);
    return 0;
}
