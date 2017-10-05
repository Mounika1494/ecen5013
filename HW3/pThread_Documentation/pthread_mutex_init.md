NAME: pthread_mutex_init

DESCRIPTION: This function initialises the mutes referenced by mutex with default attrbutes if given NULL. The default state will be unlocked
          

SYNTAX: int pthread_mutex_init(pthread_t mutex *mutex,const pthread_mutexattr_t *attr)

ARGUMENTS: pthread_mutex_t        -  variable type pthread_mutex_t
           pthread_mutexattr_t    -  If value is NULL then default attributes

RETURN:   On Success Pthread_mutex_init returns 0
          On Error Pthread_mutex_init returns > 0

ERRORS:  EAGAIN,ENOMEM,EPERM,EBUSY,EINVAL,EBUSY,EINVAL

LOCATION: pthread.h

