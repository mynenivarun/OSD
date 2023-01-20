Thread Join

outside xv6 

gcc <.c> -lpthread 

#include
#include
#include
/* ==================================
 Thread prints "Hello World"
 ================================== */
void *worker(void *arg)
{
 printf("\n\nHello World !\n\n");
 return(NULL); /* Thread exits (dies) */
}
/* =================================================
 MAIN: create a trhead and wait for it to finish
 ================================================= */
int main(int argc, char *argv[])
{
 pthread_t tid;
 /* ---------------------
 Create threads
 --------------------- */
 if ( pthread_create(&tid, NULL, worker, NULL) )
 {
 printf("Cannot create thread\n");
 exit(1);
 }
 printf("Main waits for thread to finish....");
 pthread_join(tid, NULL);
}
