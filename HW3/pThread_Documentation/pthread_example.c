#define  _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/****************************************************************************
*@Filename:Pthread_example.c
*
*@Description: The program helps in tracking the stack used.If the percentage
*              less than expected then it informs the user about stack utilisation
*
*@Author: Mounika Reddy Edula
*@Date:10/05/2017
*@Compiler:GCC
*@Debugger:GDB
******************************************************************************/

char* value=NULL;
static volatile int stack_utilised = 0;
static volatile int guard_utilised = 0;
static volatile float st_utlisation = 0;
pthread_mutex_t stack_mutex;
pthread_mutex_t guard_mutex;
pthread_cond_t stack_condition;
pthread_mutex_t stack_cond_mutex;

//tracks the stack utilisation of a thread by getting the value from attribute
void *track_process(void *args) 
{
     pthread_attr_t attr;
     size_t stacksize;
     size_t guardsize;
     int ret;
     pthread_t tid;
     tid = pthread_self();
     fprintf(stdout,"Track process thread created %lu\n",tid);  
     
     //mutex_lock example
     if(pthread_attr_init(&attr) == -1)
     {
     fprintf(stdout,"error in attributr init\n");
     pthread_exit(NULL);
     }

     ret = pthread_mutex_lock(&stack_mutex);
     if(ret!=0)
     fprintf(stdout,"error locking mutex %d\n",ret);

     //get_attribute example
     ret = pthread_attr_getstacksize(&attr,&stacksize);
     if(ret!=0)
     fprintf(stdout,"error getting attribute stack %d\n",ret);
     stack_utilised = stacksize + stack_utilised;
     
     //mutex_unlock example
     ret = pthread_mutex_unlock(&stack_mutex);
     if(ret!=0)
     fprintf(stdout,"error unlocking mutex %d\n",ret);
     
     ret = pthread_mutex_lock(&guard_mutex);
     if(ret!=0)
     fprintf(stdout,"error locking mutex %d\n",ret);

     ret = pthread_attr_getguardsize(&attr,&guardsize);
     if(ret!=0)
     fprintf(stdout,"error getting guard size %d\n",ret);

     guard_utilised = guardsize + guard_utilised;
     ret = pthread_mutex_unlock(&guard_mutex);
     if(ret!=0)
     fprintf(stdout,"error locking mutex %d\n",ret);

     if(pthread_attr_destroy(&attr) == -1)
     fprintf(stdout,"error in destroying\n");
     pthread_exit(NULL);

}

//Clean up the resources using a detached thread
void *cleanup(void *args)
{   
   pthread_t tid;
   tid = pthread_self();
   fprintf(stdout,"Cleanup detached thread created %lu\n",tid);
   free(value);
   pthread_exit(NULL);
}

//thread to calculate the percentage of stack usage
void *track_efficiency(void *args)
{
    pthread_attr_t attr;
    size_t stacksize;
    size_t guardsize;
    int ret;
    
    pthread_t tid;
    //pthread_self() example
    tid = pthread_self();
    fprintf(stdout,"Track efficiency thread created %lu\n",tid);
    
    if(pthread_attr_init(&attr) == -1)
    {
     fprintf(stdout,"error in attributr init\n");
     pthread_exit(NULL);
    }
    //getattr example
    ret = pthread_getattr_np(tid,&attr);
    if(ret!=0)
    fprintf(stdout,"error getting default attributes\n");

    ret = pthread_attr_getstacksize(&attr,&stacksize);
    if(ret!=0)
    fprintf(stdout,"error getting stack size %d\n",ret);
    
    //mutex_trylock example
    if(pthread_mutex_trylock(&stack_mutex)==0)
    {
      st_utlisation = (float)stacksize/stack_utilised;
      fprintf(stdout,"utlisation is %f\n",st_utlisation);
      ret =  pthread_mutex_lock(&stack_cond_mutex);
      if(ret!=0)
      fprintf(stdout,"error locking mutex %d\n",ret);
      //pthread_cond_signal example
      if(st_utlisation < 0.5)
      {
        pthread_cond_signal(&stack_condition);
      }
      ret = pthread_mutex_unlock(&stack_cond_mutex);
      if(ret!=0)
      fprintf(stdout,"error unlocking mutex %d\n",ret);
      ret = pthread_mutex_unlock(&stack_mutex);
      if(ret!=0)
      fprintf(stdout,"error unlocking mutex %d\n",ret);
    }
    ret = pthread_attr_getguardsize(&attr,&guardsize);
    if(ret!=0)
    fprintf(stdout,"error getting guard size %d\n",ret);

    if(pthread_mutex_trylock(&guard_mutex)==0)
    {
      st_utlisation = guardsize/guard_utilised;
      ret = pthread_mutex_unlock(&guard_mutex);
      if(ret!=0)
      fprintf(stdout,"error unlocking mutex %d\n",ret);
     
    }
    if(pthread_attr_destroy(&attr) == -1)
      fprintf(stdout,"error in destroying\n");
    pthread_exit(NULL);
}

//When the stack usage is less than expected then inform user
void *action(void *args)
{
   
   pthread_t tid;
   int ret;
   tid = pthread_self();
   fprintf(stdout,"Track process thread created %lu\n",tid);
   while(1)
   {
   ret = pthread_mutex_lock(&stack_cond_mutex);
   if(ret!=0)
    fprintf(stdout,"error locking mutex %d\n",ret);
   //cond_wait example
   pthread_cond_wait(&stack_condition,&stack_cond_mutex);
   fprintf(stdout,"CPU is not overloaded\n");
   ret = pthread_mutex_unlock(&stack_cond_mutex);
   if(ret!=0)
   fprintf(stdout,"error unlocking mutex %d\n",ret);
   break;
   }
   pthread_exit(NULL);
}


int main()
{
   int16_t err,errno;
   pthread_t thread1, thread2,thread3;
   pthread_t thread4,thread5;
   pthread_attr_t attr;
   pthread_attr_t default_attr;
   err = pthread_attr_init(&attr);
   if(err !=0)
     {
      fprintf(stdout,"attribute initialisation error\n");
      return(err);
      }
   //atrr_init example
   err = pthread_attr_init(&default_attr);
   if(err !=0)
     {
      fprintf(stdout,"default attribute initialisation error\n");
      return(err);
     }
   //mutex_init example
   if(pthread_mutex_init(&stack_mutex,NULL) != 0)
     {
      fprintf(stdout,"mutex init failed\n");
      return 1;
      }
  if(pthread_mutex_init(&stack_cond_mutex,NULL) != 0)
     {
      fprintf(stdout,"mutex init failed\n");
      return 1;
      }
  //cond_init example
   if(pthread_cond_init(&stack_condition,NULL) != 0)
     {
      fprintf(stdout,"condition init failed\n");
      return 1;
      }
   if(pthread_mutex_init(&guard_mutex,NULL) != 0)
     {
      fprintf(stdout,"mutex init failed\n");
      return 1;
      }
   //setattribute example
   err = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
   if(err == 0)
      {
       fprintf(stdout,"attribute set to detached state\n");
       errno = pthread_create( &thread1,&attr,cleanup,NULL);
       fprintf(stdout,"detached thread id is %d\n",errno);
      }  
   //attr_destroy example
   err = pthread_attr_destroy(&attr);
   if(err!=0)
    fprintf(stdout,"error destroying the attribute %d\n",err);
   //getattr_default example
   err = pthread_getattr_default_np(&default_attr);
   if(err!=0)
    fprintf(stdout,"error getting default attributes\n");
   
   //pthread_create example
   err = pthread_create(&thread1,&default_attr,track_process,NULL);
   if(err!=0)
    fprintf(stdout,"error creating thread %d\n",err);
   
   err = pthread_create(&thread2,NULL,track_process,NULL);
   if(err!=0)
    fprintf(stdout,"error creating thread %d\n",err);

   err = pthread_create(&thread3,NULL,track_process,NULL);
   if(err!=0)
    fprintf(stdout,"error creating thread %d\n",err);

   //pthread_join example
   err = pthread_join(thread1,NULL);
   if(err!=0)
    fprintf(stdout,"error joining threads %d\n",err);

   err = pthread_join(thread2,NULL);
   if(err!=0)
    fprintf(stdout,"error joining threads %d\n",err);

   err = pthread_join(thread3,NULL);
   if(err!=0)
    fprintf(stdout,"error joining threads %d\n",err);

   fprintf(stdout,"stacksize is %d\n",stack_utilised);
   fprintf(stdout,"guardsize is %d\n",guard_utilised);
   
   err = pthread_create(&thread4,NULL,track_efficiency,NULL);
   if(err!=0)
    fprintf(stdout,"error creating threads %d\n",err);

   err = pthread_create(&thread5,NULL,action,NULL);
   if(err!=0)
    fprintf(stdout,"error creating threads %d\n",err);

   err = pthread_join(thread4,NULL);
   if(err!=0)
    fprintf(stdout,"error joining threads %d\n",err);


   err = pthread_join(thread5,NULL);
   if(err!=0)
    fprintf(stdout,"error joining threads %d\n",err);

   //mutex_destroy example
   err = pthread_mutex_destroy(&stack_mutex);
   if(err!=0)
    fprintf(stdout,"error destroying the stackmutex %d\n",err);

   err = pthread_mutex_destroy(&guard_mutex);
   if(err!=0)
    fprintf(stdout,"error destroying the guardmutex %d\n",err);

   err = pthread_mutex_destroy(&stack_cond_mutex);
   if(err!=0)
    fprintf(stdout,"error destroying the stackcondmutex %d\n",err);
   
   //cond_destroy example
   err = pthread_cond_destroy(&stack_condition);
   if(err!=0)
    fprintf(stdout,"error destroying the condition %d\n",err);
   
   //exit example
   pthread_exit(NULL);
}

