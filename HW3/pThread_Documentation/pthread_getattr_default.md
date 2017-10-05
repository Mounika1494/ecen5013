NAME: pthread_getattr_default_np

DESCRIPTION: This function is used to get default attributes of the current thread.

SYNTAX: int pthread_getattr_default_np(pthread_attr_t *attr)

ARGUMENTS: pthread_attr_t         -  address of the variable of type pthread_attr_t
       

RETURN:   On Success returns 0
          On Error returns 0

ERRORS:  EINVAL,ENOMEM

Note: Before using attribute pthread_attr_t we should initialise before using them for getatribute
      #define _GNU_SOURCE should be added

LOCATION: pthread.h

COMPILE: -lpthread
