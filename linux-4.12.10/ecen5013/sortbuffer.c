#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <uapi/asm-generic/errno-base.h>
#include <linux/uaccess.h>
#include <linux/gfp.h>

/*******************************************************************************
*@Filename:sortbuffer.c
*
*@Description:Implementation of syscall for sorting buffer
*
*@param buffer,size of buffer,pointer to sorted buffer
*@return enum Error numbers look into errno.h,errno-base.h
*
*@Author: Mounika Reddy Edula
*@Date:09/18/2017
*@Compiler:gcc
*@Debugger:gdb
*@Kernel version:4.12.10
******************************************************************************/

/*Syscall macro will be converted to asmlinkage as in the header syscalls.h*/
SYSCALL_DEFINE3(sortbuffer, int32_t*, buffer, uint32_t, size, int32_t*, sort_buffer)
{

 /***intialise local variables validate inputs****/
 int32_t* k_buffer = NULL;
 int32_t swap = 0;
 int status=0;
 int i=0;
 int j=0;
 if(buffer == NULL || sort_buffer == NULL || size == 0)
 {
 printk("Invalid arguments\n");
 return EINVAL ;
 }
 k_buffer = (int32_t *)kmalloc( sizeof(int32_t)*size,GFP_KERNEL);
 if(k_buffer == NULL)
 {
 printk("memory allocation failed\n");
 return ENOMEM;
 }
 status = copy_from_user(k_buffer,buffer,sizeof(int32_t)*size);
 if(status < 0)
 {
 printk("can't copy from user space\n");
 return EFAULT;
 }
 printk("copied buffer from user space\n");
 /***Bubble sort for sorting***/
 printk("*******Bubble Sort starts******\n");
 for(i=1;i<size;i++)
 {
  for(j=0;j<size-i;j++)
  {
   if(*(k_buffer+j)<*(k_buffer+j+1))
   {
   swap = *(k_buffer+j);
   *(k_buffer+j) = *(k_buffer+j+1);
   *(k_buffer+j+1) = swap;
   }
  }
 }
 printk("******Bubble Sort Completed******\n");
 status = copy_to_user(sort_buffer,k_buffer,sizeof(int32_t)*size);
 if(status < 0)
 {
 printk("can't copy to user\n");
 return EFAULT;
 }
 printk("copied buffer from kernel to user space\n");
 return 0;
}
