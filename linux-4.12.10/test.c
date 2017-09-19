#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{
 printf("Invoking 'listProcessInfo' system call");
 long int ret_status = syscall(333);
 if(ret_status ==0)
   printf("system call 'listProcessInfo' executed correctly. Use dmesg to check processInfo\n");
 else
   printf("system call 'listprocessinfo' did not execute as expected\n");
 return 0;
}
