#include <pthread.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/file.h>


//mutex and condition
pthread_mutex_t usr1_mutex;
pthread_cond_t usr1_sig;
pthread_mutex_t usr2_mutex;
pthread_cond_t usr2_sig;

//globals for state track
static volatile int file_write_state = 1;
static volatile int process_file_state = 1;
static volatile int report_result_state = 1;
static volatile int signal_int = 0;
static volatile int signal_order = 0;

//result
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
            signal_order = 1;
            file_write_state = 0;
            process_file_state = 1;
            fprintf(stdout,"user signal 1 recieved\n");
            pthread_cond_signal(&usr1_sig);
            break;
       case SIGUSR2:
            
           if(signal_order == 0)
            {
              fprintf(stdout,"\nShould Kill SIGUSR1 before SIGUSR2\n");
              break;
            }
            else if(signal_order == 1)
            {
              process_file_state = 0;
              fprintf(stdout,"user signal 2 recieved\n");
              pthread_cond_signal(&usr2_sig);
              break;
            }
            break;
       
       case SIGTERM:
            signal_int = 1;
            file_write_state = 0;
            pthread_cond_signal(&usr1_sig);
            break;
       
       case SIGINT:
            signal_int = 1;
            file_write_state = 0;
            pthread_cond_signal(&usr1_sig);
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
   while(process_file_state == 1)
   {
       pthread_cond_wait(&usr1_sig,&usr1_mutex);
       while(file_write_state == 0)
       {

       input_file = fopen((result->filename),"r");
       if(input_file == NULL)
       return 0;

       while((data=fgetc(input_file))!=EOF)
       {
         putchar(data);
         if(data != ' '&& data != '\n')
          result->char_count++;
         if(data == ' ' || data == '\n')
          result->word_count++;
         if(data == '\n')
          result->line_count++;
       }
       process_file_state = 0;
       fclose(input_file);
       break;
       }
   }
   if(signal_int == 1)
   {
    report_result_state = 0;
    pthread_cond_signal(&usr2_sig);
   }
  return NULL;
}


//Thread for reporting the result
void *report_result(void *args)
{

   struct result_struct *result = (struct result_struct *)args;
   while(report_result_state == 1)
   {
   pthread_cond_wait(&usr2_sig,&usr2_mutex);
   while(process_file_state == 0)
   {
     fprintf(stdout,"***reporting******\n");
     fprintf(stdout,"Lines:%d\n",result->line_count);
     fprintf(stdout,"Words:%d\n",result->word_count);
     fprintf(stdout,"characters:%d\n",result->char_count);
     report_result_state = 0;
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

   memcpy(&(result.filename),filename,strlen(filename));
   user_sig.sa_handler = signal_handler;
  
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
   if(sigaction(SIGINT, &user_sig,NULL)< 0)
   {
    fprintf(stdout,"sigaction can't be linked\n");
    return 1;
   }

   if(sigaction(SIGTERM, &user_sig,NULL)< 0)
   {
    fprintf(stdout,"sigaction can't be linked\n");
    return 1;
   }

   if(pthread_mutex_init(&usr2_mutex,NULL) != 0)
   {
     fprintf(stdout,"mutex init failed\n");
     return 1;
   }
   
   if(pthread_cond_init(&usr1_sig,NULL) != 0)
   {
     fprintf(stdout,"mutex init failed\n");
     return 1;
   }
   
   if(pthread_mutex_init(&usr1_mutex,NULL) != 0)
   {
     fprintf(stdout,"mutex init failed\n");
     return 1;
   }
   if(pthread_cond_init(&usr2_sig,NULL) != 0)
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
   
   
   fprintf(stdout,"Enter the data for the file\n");
   fclose(fopen(filename,"w"));
   while(file_write_state == 1)
   {  
      input_file = fopen(filename,"a");
      if(input_file == NULL)
      {
      fprintf(stdout,"file can't be created\n");
      return 0;
      }
      data = getchar();
      if(data == EOF)
      {
      file_write_state = 0;
      break;
      }
      fputc(data,input_file);
      fclose(input_file);
   }

   err = pthread_join(process_input_thread,NULL);
   if(err!=0)
    fprintf(stdout,"error joining thread %d\n",err);

   err = pthread_join(report_result_thread,NULL);
   if(err!=0)
    fprintf(stdout,"error joining the thread %d\n",err);

   err = pthread_mutex_destroy(&usr1_mutex);
   if(err!=0)
    fprintf(stdout,"error destroying the stackmutex %d\n",err);
    
   err = pthread_cond_destroy(&usr1_sig);
   if(err!=0)
    fprintf(stdout,"error destroying the stackmutex %d\n",err);
     err = pthread_mutex_destroy(&usr2_mutex);
   if(err!=0)
    fprintf(stdout,"error destroying the stackmutex %d\n",err);
    
   err = pthread_cond_destroy(&usr2_sig);
   if(err!=0)
    fprintf(stdout,"error destroying the stackmutex %d\n",err);
}
