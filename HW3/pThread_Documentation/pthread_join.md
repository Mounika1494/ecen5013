NAME: pthread_join

DESCRIPTION: This function waits for the thread specified. The thread specified must be joinable
             If multiple threads try to join then results are undefined

SYNTAX: int pthread_join(pthread_t thread,void **retval)

ARGUMENTS: pthread_t thread       -  variable type pthread
           retval                 -  If value is not NULL thread joined return value will be stored

RETURN:   On Success Pthread_join returns 0
          On Error Pthread_join returns > 0

ERRORS:  EDEADLK,EINVAL,EINVAL,ESRCH

LOCATION: pthread.h

COMPILE: -lpthread
