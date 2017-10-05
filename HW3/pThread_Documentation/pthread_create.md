NAME: pthread_create

DESCRIPTION: This function creates new thread using 
             clone(CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND,0)

SYNTAX: int pthread_create(pthread_t *thread,const pthread_attr_t *attr,
                          void *(*start_routine)(void *),void *arg);

ARGUMENTS: pthread_t *thread      -  address of variable type pthread
           pthread_attr_t *attr   -  address of variable typr pthread_attr_t which should be initialised
           start_routine          -  function name to be implemented by thread
           arg                    -  address of arguments to pass to the thread

RETURN:   On Success Pthread_create returns 0
          On Error Pthread_create returns > 0

ERRORS:  EAGAIN,EINVAL,EPERM

LOCATION: pthread.h

COMPILE: -lpthread
