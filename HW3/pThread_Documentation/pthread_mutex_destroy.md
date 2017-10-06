NAME: pthread_mutex_destroy

DESCRIPTION: This function destroys the mutex object which was initialised.After destroyed object 
             can be reinitialsied
          
SYNTAX: int pthread_mutex_destroy(pthread_t mutex *mutex)

ARGUMENTS: pthread_mutex_t        -  variable type pthread_mutex_t
          

RETURN:   On Success Pthread_mutex_init returns 0
          On Error Pthread_mutex_init returns > 0

ERRORS:  EAGAIN,ENOMEM,EPERM,EBUSY,EINVAL,EBUSY,EINVAL

LOCATION: pthread.h

