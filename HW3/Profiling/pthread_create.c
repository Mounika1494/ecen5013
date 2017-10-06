#include <time.h>
#include <stdint.h>
#include <pthread.h>
#include <stdio.h>

struct profile
{
clock_t create_start;
clock_t create_end;
}stats;

void *no_work(void *args)
{
struct profile *pt_createprofile = (struct profile *)args;  
pt_createprofile->create_end = clock();
}

int main()
{
pthread_t profile_thread;
float create_time = 0;
struct profile *pt_createprofile;
pt_createprofile->create_start = clock();
if(pt_createprofile->create_start == (clock_t) -1)
 {
  fprintf(stdout,"failed to start clock\n");
 }
if(pthread_create(&profile_thread,NULL,no_work,(void *)pt_createprofile) !=0)
 {
  fprintf(stdout,"failed to create thread \n");
 }
 if(pthread_join(profile_thread,NULL) !=0)
 {
  fprintf(stdout,"failed to create thread \n");
 }
 create_time = ((pt_createprofile->create_end)-(pt_createprofile->create_start));
 fprintf(stdout,"CPU time(clocks) it takes to create using pthread is %f\n",create_time);
}
