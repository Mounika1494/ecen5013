#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
/***********************************************************************
*@Filename:sort_buffer.c
*
*@Description:Utilising the syscall created for sorting the buffer
*
*@Author:Mounika Reddy Edula
*@Date:09/19/2017
*compiler:gcc
*debugger:gdb
*linux:linux-4.12.10
***********************************************************************/
#define sys_sortbuffer 333


int main()
{
int32_t data =0;
time_t t = 0;
int32_t* buffer = NULL;
int32_t* temp_buffer = NULL;
int32_t* sort_buffer = NULL;
int ret_status = 0;
srand(time(&t));
size_t size = 0;

//Create a random buffer with user specs
printf("Enter the size\n");
scanf("%lu",&size);
printf("size is %lu\n",size);
buffer = malloc(size*sizeof(int32_t));
sort_buffer = malloc(size*sizeof(int32_t));
temp_buffer = buffer;
if(buffer == NULL)
{
printf("memory not allocated\n");
}

for(int i=0;i<size;i++)
{
 data = rand();
 //printf("data added at index %d is %d\n",i,data);
 *temp_buffer++ = data;
}

//Invoking the system call
printf("Invoking System call sortbuffer\n");
ret_status = syscall(333,buffer,size,sort_buffer);
printf("Exited the system call and it returned %d\n",ret_status);

//print the output
/*
if(ret_status ==0)
{
printf("*******sorted buffer *******\n");
for(int i=0;i<size;i++)
{
 printf("data added at index %d is %d\n",i,*sort_buffer++);
}
}*/
}


