NAME: pthread_cond_signal

DESCRIPTION: This function sends the signal to the blocked threads to unblock.It will unblock atleast one thread
          

SYNTAX: int pthread_cond_signal(pthread_cond_t *cond)

ARGUMENTS: pthread_cond_t        -   variable type pthread_cond_t
        
RETURN:   On Success Pthread_mutex_init returns 0
          On Error Pthread_mutex_init returns > 0

ERRORS:  EINVAL

LOCATION: pthread.h

