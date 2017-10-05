NAME: pthread_attr_setattribute

DESCRIPTION: This function is used to sent attribute to the current thread. There are many variations
             with attribute like detachstate,stacksize,guardsize..

SYNTAX: int pthread_attr_setattribute(pthread_attr_t *attr,int attribute)
       

ARGUMENTS: pthread_attr_t         -  address of the variable of type pthread_attr_t
           attribute              -  new value of the attribute you want to set 
          

RETURN:   On Success returns 0
          On Error returns >0

ERRORS:  EINVAL

Note: Before using attribute pthread_attr_t we should initialise before using them for getatribute

LOCATION: pthread.h

COMPILE: -lpthread
