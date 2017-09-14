#include <stdio.h>
#include <stdlib.h>


#define sys_sortbuffer 333
int main()
{

int32_t data,swap;
time_t t;
int32_t* buffer = NULL;
int32_t* sort_buffer = NULL;
int ret_status;
srand(time(&t));
size_t size;
printf("Enter the size\n");
scanf("%d",&size);
printf("size is %d\n",size);
buffer = malloc(size*sizeof(int32_t));
sort_buffer = buffer;
printf("buffer and sorted buffer are at address %d,%d\n",buffer,sort_buffer);
if(buffer == NULL)
{
printf("memory not allocated\n");
}

for(int i=0;i<size;i++)
{
 data = rand();
 printf("data added at index %d is %d\n",i,data);
 *buffer++ = data;
}
for(int i=1;i<size;i++)
 {
  for(int j=0;j<size-i;j++)
  {
   printf("values to be comapred are %d,%d\n",*(sort_buffer+j),*(sort_buffer+j+1));
   if(*(sort_buffer+j)>*(sort_buffer+j+1))
   {
   printf("inside the loop\n");
   swap = *(sort_buffer+j);
   *(sort_buffer+j) = *(sort_buffer+j+1);
   *(sort_buffer+j+1) = swap;
   }
  }
 }

printf("*******sorted buffer *******\n");
for(int i=0;i<size;i++)
{
 printf("data added at index %d is %d\n",i,*sort_buffer++);
}
/*printf("Invoking System call sortbuffer\n");
ret_status = syscall(sys_sortbuffer,new_);
printf("Exited the system call and it returned %d",ret_status);
*/
}


