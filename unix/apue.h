#ifndef _APUE_H
#define _APUE_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h> /* exit function define */
#include <string.h>
#include <unistd.h> /* STDIN_FILENO, STDOUT_FILENO and so on*/
#include <errno.h> /* for errno */

#define MAXLINE 4096

void err_sys(const char *, ...);
void err_quit(const char *, ...);
void err_ret(const char *, ...);


#endif /* _APUE_H */
