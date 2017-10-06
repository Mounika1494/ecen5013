#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <time.h>
#include <unistd.h>
/********************************************************
*@Filename: fork_exec.c
*
*@Description: Time taken for Forking the process and creating children. 
*
*@Author: Mounika Reddy Edula
*@Date:10/05/2017
*@Compiler:GCC
*@Debugger:gdb
********************************************************/

int main (int argc, char **argv) 
{ 
int pid,status,ret;
clock_t create_start;
clock_t create_end;
long int time_create;

create_start = clock();

if(create_start == (clock_t) -1)
{
  fprintf(stdout,"failed to start clock\n");
}
printf("time taken by parent is %lu\n",create_start);
pid = fork (); 
if (pid == 0) 
{
  //child
  execl("./child","./child",NULL);
} 

// I am the parent 
printf ("Parent: Waiting for Child to complete.\n"); 
create_end = clock();
printf("end of the fork is %lu\n",create_end);
time_create = create_end -create_start;
printf("time taken for fork is %lu\n",time_create);

//waiting for the child process
if ((ret = waitpid (pid, &status, 0)) == -1) 
printf ("parent:error\n"); 
if (ret == pid) 
printf ("Parent: Child process waited for.\n");

} 
