#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#define PAGE_SIZE 256
#define PAGE_ENTRIES 256
#define PAGE_NUM_BITS 8
#define FRAME_SIZE 256
#define FRAME_ENTRIES 256
#define MEM_SIZE (FRAME_SIZE * FRAME_ENTRIES)
#define TLB_ENTRIES 16 int
virtual,page_number,offset,physical,frame_number,value,page_table[PAGE_ENTRIES],tlb[TLB
_ENTRIES][2],tlb_front = -1,tlb_back = -1,mem_index = 0,fault_counter = 0,tlb_counter =
0; char
memory[MEM_SIZE]; int
address_counter = 0;
float fault_rate,tlb_rate;
int get_physical(int virtual),get_offset(int virtual);
int get_page_number(int virtual); void 
initialize_page_table(int n); void initialize_tlb(int
n);
int consult_page_table(int page_number); int
consult_tlb(int page_number);
void update_tlb(int page_number, int frame_number); int
get_frame();
int main(int argc, char *argv[]) {

 char* in_file; char*
out_file; char*
store_file; char*
store_data; int store_fd;
char line[8]; FILE*
in_ptr; FILE* out_ptr;
initialize_page_table(-1);
initialize_tlb(-1); if
(argc != 4) {
 printf("Enter input, output, and store file names!");
exit(EXIT_FAILURE);
 }
else {
 in_file = argv[1];
out_file = argv[2];
store_file = argv[3];
 if ((in_ptr = fopen(in_file, "r")) == NULL) {
printf("Input file could not be opened.\n");
exit(EXIT_FAILURE);
 }
 if ((out_ptr = fopen(out_file, "a")) == NULL) {
printf("Output file could not be opened.\n");
exit(EXIT_FAILURE);
 }
 store_fd = open(store_file, O_RDONLY);
 store_data = mmap(0, MEM_SIZE, PROT_READ, MAP_SHARED, store_fd, 0);
if (store_data == MAP_FAILED) { close(store_fd);
 printf("Error mmapping the backing store file!");
exit(EXIT_FAILURE);
 }
 while (fgets(line, sizeof(line), in_ptr)) {
virtual = atoi(line); address_counter++;
 page_number = get_page_number(virtual);
offset = get_offset(virtual);
frame_number = consult_tlb(page_number);
if (frame_number != -1) { physical =
frame_number + offset; value =
memory[physical];
 }
else {
 frame_number = consult_page_table(page_number);
if (frame_number != -1) { physical =
frame_number + offset;
update_tlb(page_number, frame_number);
value = memory[physical];
 }
else {
 int page_address = page_number * PAGE_SIZE;
if (mem_index != -1) { memcpy(memory +
mem_index,
 store_data + page_address, PAGE_SIZE);
frame_number = mem_index; physical =
frame_number + offset; 

 value = memory[physical];

 page_table[page_number] = mem_index;

 update_tlb(page_number, frame_number);

 if (mem_index < MEM_SIZE - FRAME_SIZE) {
mem_index += FRAME_SIZE;
 }
else {
 mem_index = -1;
 }
} else
{

 }
 }
 }
 fprintf(out_ptr, "Virtual address: %d ", virtual);
fprintf(out_ptr, "Physical address: %d ", physical);
fprintf(out_ptr, "Value: %d\n", value);
 }
 fault_rate = (float) fault_counter / (float) address_counter;
tlb_rate = (float) tlb_counter / (float) address_counter;
 fprintf(out_ptr, "Number of Translated Addresses = %d\n", address_counter);
fprintf(out_ptr, "Page Faults = %d\n", fault_counter); fprintf(out_ptr,
"Page Fault Rate = %.3f\n", fault_rate); fprintf(out_ptr, "TLB Hits =
%d\n", tlb_counter); fprintf(out_ptr, "TLB Hit Rate = %.3f\n", tlb_rate);
fclose(in_ptr); fclose(out_ptr); close(store_fd);
 }
 return EXIT_SUCCESS;
}
int get_physical(int virtual) {
 physical = get_page_number(virtual) + get_offset(virtual);
 return physical;
}
int get_page_number(int virtual) {

 return (virtual >> PAGE_NUM_BITS);
}
int get_offset(int virtual) {

 int mask = 255;
 return virtual & mask;
} void initialize_page_table(int n) {
for (int i = 0; i < PAGE_ENTRIES; i++) {
page_table[i] = n;
 }
}
 
void initialize_tlb(int n) { for (int i
= 0; i < TLB_ENTRIES; i++) {
tlb[i][0] = -1; tlb[i][1] = -1;
 }
}
 int consult_page_table(int page_number)
{ if (page_table[page_number] == -1)
{ fault_counter++;
 }
 return page_table[page_number];
} int consult_tlb(int page_number) {
for (int i = 0; i < TLB_ENTRIES; i++) {
if (tlb[i][0] == page_number) {
tlb_counter++;
 return
tlb[i][1];
 }
 }

return -1;
} void update_tlb(int page_number, int frame_number)
{

 if (tlb_front == -1) {

tlb_front = 0;
tlb_back = 0;

 tlb[tlb_back][0] = page_number;
tlb[tlb_back][1] = frame_number;
 }
else {
 tlb_front = (tlb_front + 1) % TLB_ENTRIES;
tlb_back = (tlb_back + 1) % TLB_ENTRIES;
tlb[tlb_back][0] = page_number; tlb[tlb_back][1] =
frame_number;
 }
return;
}
