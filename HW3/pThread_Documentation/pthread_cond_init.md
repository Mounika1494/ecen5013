NAME: pthread_cond_init

DESCRIPTION: This function initialises the condition  with default attrbutes if given NULL. The default state will be initialised
          

SYNTAX: int pthread_cond_init(pthread_cond_t *cond,const pthread_condattr_t *attr)

ARGUMENTS: pthread_cond_t        -   variable type pthread_cond_t
           pthread_condattr_t    -  If value is NULL then default attributes

RETURN:   On Success Pthread_mutex_init returns 0
          On Error Pthread_mutex_init returns > 0

ERRORS:  EAGAIN,ENOMEM,EPERM,EBUSY,EINVAL,EBUSY,EINVAL

LOCATION: pthread.h

