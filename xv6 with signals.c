
#include <stdio.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#define BUFSIZE 100
void alrm_handler(int signo);
char buf[BUFSIZE] = "foo\0";
void quit(char *message, int exit_status)
{
 printf(" %s",message);
 exit(exit_status);
}
int main (void)
{
int n;
struct sigaction act;
act.sa_handler = alrm_handler;
if(sigaction(SIGALRM,&act,NULL) == -1)
quit("sigalrm",1);
fprintf(stderr,"enter filename:");
alarm(5);
n = read(STDIN_FILENO, buf, BUFSIZE);
if (n > 1)
fprintf(stderr,"Filename: %s\n", buf);
exit(0);
}
void alrm_handler(int signo)
{
fprintf(stderr,"\nSignal %d received, default filename: %s\n", signo, buf);
exit(1);
}
