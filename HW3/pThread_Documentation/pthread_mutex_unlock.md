NAME: pthread_mutex_unlock

DESCRIPTION: This function unlocks the initialsed mutex. This function releases the mutex object.

SYNTAX: int pthread_mutex_unlock(pthread_t mutex *mutex)

ARGUMENTS: pthread_mutex_t        -  variable type pthread_mutex_t


RETURN:   On Success Pthread_mutex_init returns 0
          On Error Pthread_mutex_init returns > 0

ERRORS:  EAGAIN,ENOMEM,EPERM,EBUSY,EINVAL,EBUSY,EINVAL

LOCATION: pthread.h
