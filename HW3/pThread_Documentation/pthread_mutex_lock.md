NAME: pthread_mutex_lock

DESCRIPTION: This function locks the initialsed mutex. If already locked it will block till gets unlocked.
          

SYNTAX: int pthread_mutex_lock(pthread_t mutex *mutex)

ARGUMENTS: pthread_mutex_t        -  variable type pthread_mutex_t


RETURN:   On Success Pthread_mutex_init returns 0
          On Error Pthread_mutex_init returns > 0

ERRORS:  EAGAIN,ENOMEM,EPERM,EBUSY,EINVAL,EBUSY,EINVAL

LOCATION: pthread.h

