#include <pthread.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/file.h>

static volatile sig_atomic_t start_report = 0;
static volatile sig_atomic_t start_process = 0;
pthread_mutex_t file_mutex;

struct result_struct 
{
   int line_count;
   int word_count;
   int char_count;
   char filename[25];
}args;

void signal_handler(int signal);

/********************************************************
*@Filename: multi_thread.c
*
*@Description: Multi threaded program where threads are triggered
*by the signals. One thread for processing other for reporting
*
*@Author: Mounika Reddy Edula
*@Date:10/05/2017
*@Compiler:GCC
*@Debugger:gdb
********************************************************/

//Signal_handler for all the signals
void signal_handler(int signal)
{

  switch(signal) {
       case SIGUSR1:
            fprintf(stdout,"user signal 1 recieved\n");
            start_process = 1;
            break;
       case SIGUSR2:
            fprintf(stdout,"user signal 2 recieved\n");
            start_report = 1;
            break;
       default:
            fprintf(stdout,"unknown signal caught\n");
            return;
        }
}


//thread for processing the contents from user
void *process_file(void *args)
{  

   struct result_struct *result = (struct result_struct *)args;
   char data;
   FILE *input_file;
   result->line_count = 0;
   result->word_count = 0;
   result->char_count = 0;
   input_file = fopen((result->filename),"r");
   if(input_file == NULL)
   return 0;
   while(1)
   {
    if(start_process == 1)
     {
     while((data=fgetc(input_file))!=EOF)
     {
      if(data != ' '&& data != '\n')
      result->char_count++;
      if(data == ' ' || data == '\n')
       result->word_count++;
      if(data == '\n')
       result->line_count++;
     }
     fprintf(stdout,"Lines:%d\n",result->line_count);
     fprintf(stdout,"Words:%d\n",result->word_count);
     fprintf(stdout,"characters:%d\n",result->char_count);
     fclose(input_file);
     break;
     }
    }
  return NULL;
}


//Thread for reporting the result
void *report_result(void *args)
{

   struct result_struct *result = (struct result_struct *)args;
   while(1)
   {
   if(start_report ==1)
   {
   fprintf(stdout,"***reporting******\n");
   fprintf(stdout,"Lines:%d\n",result->line_count);
   fprintf(stdout,"Words:%d\n",result->word_count);
   fprintf(stdout,"characters:%d\n",result->char_count);
   break;
   }
   }
   return NULL;
}


int main()
{
   fprintf(stdout,"Parent pid is: %d\n",getpid());
   FILE *input_file = NULL;
   pthread_t process_input_thread;
   pthread_t report_result_thread;
   int err;
   struct sigaction user_sig;
   struct result_struct result;
   char *filename = malloc(25*(sizeof(char)));
   char data;
   
   fprintf(stdout,"Enter the filename\n");
   scanf("%s",filename);
   input_file = fopen(filename,"w");
   if(input_file == NULL)
   {
    fprintf(stdout,"file can't be created\n");
    return 0;
   }

   memcpy(&(result.filename),filename,strlen(filename));
   user_sig.sa_handler = signal_handler;
   sigfillset(&user_sig.sa_mask);
  
   if(sigaction(SIGUSR1, &user_sig,NULL)< 0)
   {
    fprintf(stdout,"sigaction can't be linked\n");
    return 1;
   }

   if(sigaction(SIGUSR2, &user_sig,NULL)< 0)
   {
    fprintf(stdout,"sigaction can't be linked\n");
    return 1;
   }

   if(pthread_mutex_init(&file_mutex,NULL) != 0)
   {
     fprintf(stdout,"mutex init failed\n");
     return 1;
   }

   if(pthread_create(&process_input_thread,NULL,process_file,(void *)&result))
   {
    fprintf(stdout,"Error creating thread\n");
    return 0;
   } 
  
   if(pthread_create(&report_result_thread,NULL,report_result,(void*)&result))
   {
    fprintf(stdout,"Error creating thread\n");
    return 0;
   }
   fprintf(stdout,"Enter the data for the file");  
   
   while((data = getchar())!=EOF)
   {
   pthread_mutex_lock(&file_mutex);
   fputc(data,input_file);
   pthread_mutex_unlock(&file_mutex); 
   }
   fclose(input_file);

   err = pthread_kill(process_input_thread,SIGUSR1);
   if(err!=0)
    fprintf(stdout,"error killing thread %d\n",err);

   err = pthread_join(process_input_thread,NULL);
   if(err!=0)
    fprintf(stdout,"error joining thread %d\n",err);

   err = pthread_kill(report_result_thread,SIGUSR2);
   if(err!=0)
    fprintf(stdout,"error killing thread %d\n",err);

   err = pthread_join(report_result_thread,NULL);
   if(err!=0)
    fprintf(stdout,"error joining the thread %d\n",err);

   err = pthread_mutex_destroy(&file_mutex);
   if(err!=0)
    fprintf(stdout,"error destroying the stackmutex %d\n",err);

}
