NAME: pthread_cond_destroy

DESCRIPTION: This function releases the object during the initilisation.
          

SYNTAX: int pthread_cond_destroy(pthread_cond_t *cond)

ARGUMENTS: pthread_cond_t        -   variable type pthread_cond_t
           pthread_condattr_t    -  If value is NULL then default attributes

RETURN:   On Success Pthread_mutex_init returns 0
          On Error Pthread_mutex_init returns > 0

ERRORS:  EAGAIN,ENOMEM,EPERM,EBUSY,EINVAL,EBUSY,EINVAL

LOCATION: pthread.h

