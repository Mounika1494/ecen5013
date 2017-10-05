NAME: pthread_attr_getattribute,pthread_getattr_np(pthread_t thread,pthread_attr_t *attr)

DESCRIPTION: This function is used to get attribute of the current thread. There are many variations
             with attribute like detachstate,stacksize,guardsize..

SYNTAX: int pthread_attr_getattribute(const pthread_attr_t *attr,int *attribute)
        int pthread_getattr_np(pthread_t thread,pthread_attr_t *attr)

ARGUMENTS: pthread_attr_t         -  address of the variable of type pthread_attr_t
           attribute              -  address at which you want attribute to be stored
           pthread_t              -  tid of the thread whose attributes you want to get 

RETURN:   On Success returns 0
          On Error returns 0

ERRORS:  EINVAL,ENOMEM

Note: Before using attribute pthread_attr_t we should initialise before using them for getatribute

LOCATION: pthread.h

COMPILE: -lpthread
