#include <stdio.h> 
#include <pthread.h> void* 
worker( void* p ) { int* ip 
= (int*)p; 
 printf("Hello world from thread ID:%d,thread number %i!\n",pthread_self(),*ip); 
} 
int main() { 
 pthread_t OtherThread[4]; 
int i; 
 for(i=0;i<4;i++) { 
 pthread_create( &OtherThread[i], NULL, worker, &i ); 
sleep(1); 
 } 
}
