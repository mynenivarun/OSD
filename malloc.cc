outside xv6 
./a.out 1000 10240 1 1 999

#include <stdio.h> 
#include <stdio.h> 
#include <stdlib.h>
int main()
{
// This pointer will hold the
// base address of the block created 
int* ptr;
int n, i;
// Get the number of elements for the array 
n = 5;
// Dynamically allocate memory using malloc() 
ptr = (int*)malloc(n * sizeof(int));
// Check if the memory has been successfully
// allocated by malloc or not 
if (ptr == NULL) {
printf("Memory not allocated.\n"); 
exit(0);
}
