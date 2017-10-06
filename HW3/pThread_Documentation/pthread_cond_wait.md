NAME: pthread_cond_wait

DESCRIPTION: This function block on the condition. they shall be called with mutex locked by the calling thread or undefined behaviour results.
          

SYNTAX: int pthread_cond_wait(pthread_cond_t *cond,pthread_mutex_t *mutex)

ARGUMENTS: pthread_cond_t        -   variable type pthread_cond_t
           pthread_mutex_t    -  variable type pthread_mutex_t

RETURN:   On Success Pthread_mutex_init returns 0
          On Error Pthread_mutex_init returns > 0

ERRORS:  EPERM,EINVAL,EINVAL,ETIMEDOUT

LOCATION: pthread.h

