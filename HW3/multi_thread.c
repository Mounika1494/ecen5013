#include <pthread.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

static volatile sig_atomic_t start_report = 0;
static volatile sig_atomic_t start_process = 0;

struct result_struct 
{
   int line_count;
   int word_count;
   int char_count;
   char filename[25];
}args;

void *process_file(void *args)
{  
   //printf("*********thread2 created************\n");
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
   while((data=fgetc(input_file))!=EOF)
   {
    fprintf(stdout,"%c",data);
    if(start_process == 1)
     {
      if(data != ' '&& data != '\n')
      result->char_count++;
      if(data == ' ' || data == '\n')
       result->word_count++;
      if(data == '\n')
       result->line_count++;
     }
  }
  if(start_process == 1)
  {
   fprintf(stdout,"Lines:%d\n",result->line_count);
   fprintf(stdout,"Words:%d\n",result->word_count);
   fprintf(stdout,"characters:%d\n",result->char_count);
  break;
  }
 }
  return NULL;
}

void signal_process(int signal)
{
   fprintf(stdout,"user signal 1 recieved\n");
   start_process = 1;
}

void signal_report(int signal)
{
   fprintf(stdout,"user signal 2 recieved\n");
   start_report = 1;
}

void *report_result(void *args)
{
   struct result_struct *result = (struct result_struct *)args;
   while(1)
   {
   //fprintf(stdout,"reporting thread\n");
   if(start_report ==1)
   {
   fprintf(stdout,"***reporting******\n");
   fprintf(stdout,"Lines:%d\n",result->line_count);
   fprintf(stdout,"Words:%d\n",result->word_count);
   fprintf(stdout,"characters:%d\n",result->char_count);
   }
   }
   return NULL;
}

int main()
{
   FILE *input_file = NULL;
   pthread_t process_input_thread;
   pthread_t report_result_thread;
   pthread_mutex_t file_mutex;
   struct sigaction user_sig1;
   struct sigaction user_sig2;
   struct result_struct result;
   char *filename = malloc(25*(sizeof(char)));
   char data;
   
   fprintf(stdout,"Enter the filename\n");
   scanf("%s",filename);
   input_file = fopen(filename,"w+");
   if(input_file == NULL)
   {
    fprintf(stdout,"file can't be created\n");
    return 0;
   }
   memcpy(&(result.filename),filename,strlen(filename));
   user_sig1.sa_handler = signal_process;
   user_sig2.sa_handler = signal_report;
   if(sigaction(SIGUSR1, &user_sig1,NULL)< 0)
   {
    fprintf(stdout,"sigaction can't be linked\n");
    return 1;
   }
   if(sigaction(SIGUSR2, &user_sig2,NULL)< 0)
   {
    fprintf(stdout,"sigaction can't be linked\n");
    return 1;
   }

   if(pthread_create(&process_input_thread,NULL,process_file,(void *)&result))
   {
    fprintf(stdout,"Error creating thread\n");
    return 0;
   } 
  
   /*if(pthread_create(&report_result_thread,NULL,report_result,(void*)&result))
   {
    fprintf(stdout,"Error creating thread\n");
    return 0;
   }*/
   fprintf(stdout,"Enter the data for the file");  
   while((data = getchar()) != EOF)
   {
   //pthread_mutex_lock(&file_mutex);
   fputc(data,input_file);
   //pthread_mutex_unlock(&file_mutex); 
   }
   fclose(input_file);
   fprintf(stdout,"***reporting******\n");
   fprintf(stdout,"Lines:%d\n",result.line_count);
   fprintf(stdout,"Words:%d\n",result.word_count);
   fprintf(stdout,"characters:%d\n",result.char_count);
   pthread_kill(process_input_thread,SIGUSR1);   
   if(pthread_join(process_input_thread,NULL))
   {
   fprintf(stdout,"Error joining the thread\n");
   return 0;
   }
   fprintf(stdout,"***reporting******\n");
   fprintf(stdout,"Lines:%d\n",result.line_count);
   fprintf(stdout,"Words:%d\n",result.word_count);
   fprintf(stdout,"characters:%d\n",result.char_count);
   pthread_kill(report_result_thread,SIGUSR2);
   fprintf(stdout,"signal2 is triggered\n");
}


