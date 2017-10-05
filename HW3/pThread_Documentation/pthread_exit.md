NAME: pthread_exit

DESCRIPTION: This function terminates the thread with a retval which will be stored in pthread_join      
             arguments

SYNTAX: void pthread_exit(void *retval)

ARGUMENTS: retval   -  return value which will be given to the thread_join

RETURN: This function does'nt return to the caller

ERROR: It always succeeds

LOCATION: pthread.h

COMPILE: -lpthread
