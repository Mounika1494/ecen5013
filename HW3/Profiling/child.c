#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <time.h>
#include <unistd.h>

/********************************************************
*@Filename: child.c
*
*@Description: Child process for fork
*
*@Author: Mounika Reddy Edula
*@Date:10/05/2017
*@Compiler:GCC
*@Debugger:gdb
********************************************************/
//child 
int main(int argc,char **argv)
{
 clock_t create_end = 0;
 create_end = clock();
 if(create_end == (clock_t) -1)
 {
  fprintf(stdout,"failed to start clock\n");
 }
 printf("in child\n");
 exit(0);
}
