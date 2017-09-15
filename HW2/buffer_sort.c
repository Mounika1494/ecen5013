#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <stdio.h>
#include <stdlib.h>

#define sys_sortbuffer 333
int main()
{

int32_t data,swap;
time_t t;
int32_t* buffer = NULL;
int32_t* temp_buffer = NULL;
int32_t* sort_buffer = NULL;
int ret_status;
srand(time(&t));
size_t size;
printf("Enter the size\n");
scanf("%d",&size);
printf("size is %d\n",size);
buffer = malloc(size*sizeof(int32_t));
sort_buffer = malloc(size*sizeof(int32_t));
temp_buffer = buffer;
printf("buffer, temp buffer,sort_buffer are at address %d,%d,%d\n",buffer,temp_buffer,sort_buffer);
if(buffer == NULL)
{
printf("memory not allocated\n");
}

for(int i=0;i<size;i++)
{
 data = rand();
 printf("data added at index %d is %d\n",i,data);
 *temp_buffer++ = data;
}

printf("Invoking System call sortbuffer\n");
printf("buffer is at address %d\n",buffer);
printf("sort_buffer is at address %d\n",sort_buffer);
printf("size is %d\n",size);
ret_status = syscall(sys_sortbuffer,buffer,size,sort_buffer);
printf("Exited the system call and it returned %d",ret_status);

printf("*******sorted buffer *******\n");
for(int i=0;i<size;i++)
{
 printf("data added at index %d is %d\n",i,*sort_buffer++);
}

}


