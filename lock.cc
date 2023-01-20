#lock_init, lock_acquire(), and lock_release() to
#control the thread library hardware, using X86
#atomic exchange to facilitate spin lock.


#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
int
jointestchild(void *a, void *b)
{
 int *x = (int *)a;
 int *y = (int *)b;
 int temp;
 temp = *x;
 *x = *y;
 *y = temp;
 sleep(100);
 exit();
}
// creates a thread, passes the address of two variables
// calls join to wait on the thread
// thread swaps the values of the two variables (shared memory)
// if values are swapped when main thread comes out of join(), 
test OK
int
jointest(void)
{
 int a, b;
 a = 42;
 b = 25;
 int retval;
 char *buffer;
 buffer = sbrk(4096);
 if (buffer == (char *)-1)
 return -1;
 retval = clone(jointestchild, (void *)&a, (void *)&b, buffer + 
4096, 0);
 join(retval);
 sbrk(-4096);
 if (a == 25 && b == 42)
 printf(1, "jointest ok\n");
 else
 printf(1, "jointest failed\n");
 return 0;
}
int
jointestchild1(void *a, void *b)
{
 int x = *((int *)a);
 sleep(x);
 exit();
}
// creates two threads using clone, the first one sleeps for 100ms
// second one sleeps for 50ms. 
// join is called on the first thread. join should return on first 
thread 
// even if the second thread exits first
// also ensures that wait is not cleaning up before join
int
jointest1(void)
{
 int tid1, tid2;
 int ret1, ret2;
 int one, two;
 char *buffer1, *buffer2;
 buffer1 = sbrk(4096);
 buffer2 = sbrk(4096);
 one = 100;
 two = 50;
 tid1 = clone(jointestchild1, (void *)&one, 0, buffer1 + 4096, 0);
 tid2 = clone(jointestchild1, (void *)&two, 0, buffer2 + 4096, 0);
 ret1 = join(tid1);
 ret2 = join(tid2);
 if (ret1 == tid1 && ret2 == tid2)
 
int
twoexectest(void)
{
 cthread_t t0, t1, t2;
 int ret;
 ret = fork();
 if(!ret){
 cthread_create(&t0, wait_er, 0, 0);
 cthread_create(&t1, execchild, 0, 0);
 cthread_create(&t2, execchild, 0, 0);
 cthread_join(&t2);
 }
 wait();
 printf(1, "twoexec test passed\n");
 return 0;
}
#define TOO_MANY 100
int
toomanythreadstest(void)
{
 cthread_t arr[TOO_MANY];
 int i, j, ret;
 char *initial = sbrk(0);
 char *final;
 int flag = 0;
 int time = 100;
 for(i = 0; i < TOO_MANY; i++){
 ret = cthread_create(&arr[i], jointestchild1, &time, 0);
 if(ret == -1){
 break;
 }
 }
 if(i < 61){
 // NPROC is 64
 printf(1, "toomanythreads test failed\n");
 flag = 1;
 }
 for (j = 0; j < i; j++){
 ret = cthread_join(&arr[j]);
 }
 final = sbrk(0);
 printf(1, "toomanythreads: %d -> %d\n", initial, final);
 if(!flag)
 printf(1, "toomanythreads test passed\n");
return 0;
}
int
cottonticket(void *a, void *b)
{
 tlock_t *lk = (tlock_t *)b;
 tlock_acquire(lk);
 printf(1, "%d\t", getpid());
 tlock_release(lk);
 exit();
}
// child should be killed before it changes the value of the flag
ltest(void)
{
 cthread_t child;
 int count = 1000;
 int value = 0;
 int pid;
 pid = cthread_create(&child, wayvard_child, (void *)count, (void 
*)value);
 kill(pid);
 join(pid);
 if(value)
 printf(1, "childkilltest failed\n");
 else
 printf(1, "childkilltest suceeded\n");
 return 0;
}
// T1 increases process size
// T2 checks arguments of a system call, finds them to be fine
eases the process size
// T2 dereferences the argument (which is a buffer), and gets 
killed due to out
// of bounds access
struct baton{
 int turn;
 slock_t lock;
};
#define BUFFERSIZE (4096 * 4)
int
vmmessfunc(void *a, void *b){
 char *buf = (char *)b;
 char *flag = (char *)a;
 int fp;
 int ret;
 fp = open("data.bin", O_RDONLY);
 while(!(*flag));
 ret = read(fp, buf, BUFFERSIZE);
 if(ret == -1)
 printf(1, "vmsynctest ok\n");
 else
 printf(1, "vmsynctest failed\n");
 
 cthread_exit();
 close(fp);
}
// process creates child, passes it a buffer
// sets flag and immediately sbrk's the buffer out of the memory 
space
// read should fail in the child. 
// yields() have been added in the kernel which cause wrong 
access when safe copy primitives
// are not used
int
vmsynctest(void)
{
 char *stack = sbrk(4096);
 char *buf = sbrk(BUFFERSIZE);
 int ret;
 char flag = 0;
 int fp;
 memset(buf, '0', BUFFERSIZE);
 fp = open("data.bin", O_CREATE | O_WRONLY);
 write(fp, buf, BUFFERSIZE);
 memset(buf, '1', BUFFERSIZE);
 ret = clone(vmmessfunc, (void *)&flag, (void *)buf, stack + 4096, 
0);
 flag = 1;
 sbrk(-BUFFERSIZE); 
 join(ret);
 close(fp);
 return 0;
}
int
checker(void *a, void *b){
 char *buf = (char *)a;
 }
 return 0;
}
#define SMALLBUFFERSIZE 512
struct container{
 char *buffer;
 int *pipefd;
};
int
clonevmmessfunc(void *a, void *b){
 char *flag = (char *)a;
 int fp;
 int ret;
 struct container *x = (struct container *)b;
 char *buf = x->buffer;
 int *pipefd = x->pipefd;
 while(!(*flag));
 ret = read(pipefd[0], buf, SMALLBUFFERSIZE);
 if(ret == -1)
 printf(1, "clonevmsynctest ok\n");
 
 cthread_exit();
 close(fp);
}
// similar to the filewrite safe copy primitives test, except for 
pipes
// not using safe copy primitives causes TOCTOU panics in the 
kernel
int
pipevmsynctest(void)
{
 char *stack = sbrk(4096);
 char *buf = sbrk(SMALLBUFFERSIZE);
 int ret;
 char flag = 0;
 int pipefd[2];
 slock_release(&printlock);
 */
 sem_down(&forks[fork1]);
 sleep(1);
 sem_down(&forks[fork2]);
 /*slock_acquire(&printlock);
 printf(1, "%d eating\n", no);
 slock_release(&printlock);
 */
 ate[no] = 1;
 sem_up(&forks[fork2]);
 sleep(1);
_up(&forks[fork1]);
}
exit();
}
// no deadlocks in dining philosophers and everyone is able to eat
// (as the while loop is not infinite, there will not be starvation 
anyway)
int
diningphilosophers(void)
{
 int i;
 cthread_t philosophers[PHILOSOPHERS];
 int numbers[PHILOSOPHERS];
 for(i = 0; i < PHILOSOPHERS; i++)
 sem_init(&forks[i], 1);
 for(i = 0; i < PHILOSOPHERS; i++){
 numbers[i] = i;
 cthread_create(&philosophers[i], philosopher, (void 
*)&numbers[i], 0);
 }
 for(i = 0; i < PHILOSOPHERS; i++)
 cthread_join(&philosophers[i]);
 for(i = 0; i < PHILOSOPHERS; i++)
 if(!ate[i])
 break;
 if(i != PHILOSOPHERS)
 printf(1, "diningphilosopherstest failed\n");
 else
 printf(1, "diningphilosopherstest ok\n");
 return 0;
}
int 
main(void)
{
 jointest1();
 jointest1();
 waitjointest();
 childwaittest();
 exectest();
 memtest();
 cottontest1();
 twoexectest();
 toomanythreadstest(); 
 tickettest();
 racetest();
 childkilltest();
 vmemtest();
 vmsynctest();
 cwdsynctest();
 pipevmsynctest();
 //tlbtest(); --failes, no TLB shootdown
 parkunparktest();
 wakeuptest();
 queuetest();
 producerconsumertest();
 diningphilosophers();
 exit();
}
