#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
typedef enum  
{
	Success =0,
	Fail = 1,
	error
}status;
typedef struct {
	uint8_t* HEAD;
	uint8_t* TAIL;
	uint8_t* BASE;
	uint8_t  SIZE;
	uint16_t NO_OF_ITEMS;
	      }Buffer;
Buffer *ptr;
Buffer mybuffer;
Buffer *ptr = &mybuffer;
status allocate(Buffer ** d_pointer);
status destroy();
bool Is_buffer_full();
bool Is_buffer_empty();
status add(uint8_t data);
status remove_item();
void dump();
uint8_t size();

status allocate(Buffer ** d_pointer)
{
	if(d_pointer == NULL)
	{
	printf("error");
 	return error;
	}
        (*d_pointer)->SIZE = 50;
	 char *memory;
	memory = (char*)malloc(sizeof(char)*((*d_pointer)->SIZE));
	if(memory == NULL)
	{
	printf("fail");	
        return Fail;
	}
	(*d_pointer)->BASE = memory;
	(*d_pointer)->HEAD = memory;
	(*d_pointer)->TAIL = memory;
        printf("success");
        printf("Circular Buffer Base is at %d",(*d_pointer)->BASE);
        printf("Circular Budder Head is ar %d",(*d_pointer)->HEAD);
        printf("Circular Buffer Tail is at %d",(*d_pointer)->TAIL);
	return Success;
}

bool Is_buffer_full()
{	
     if(ptr->HEAD==(ptr->BASE + (ptr->SIZE)*(sizeof(uint8_t))))
	{
        ptr->HEAD=ptr->BASE;
	return true;
	}
	else
	return false;	
}
/*bool Is_buffer_empty()
{
	if((ptr->HEAD)==(ptr->TAIL))
	return true;
	else
	return false;	
}*/
status add(uint8_t data)
{
printf("data is %d", data);
if(Is_buffer_full())
{
return error;
}
*(ptr->HEAD++) = data;
 ptr->NO_OF_ITEMS=ptr->NO_OF_ITEMS+1;
 printf("no of items is %d",ptr->NO_OF_ITEMS);
return Success;
}
status remove_item()
{
/*
if(Is_buffer_empty())
{
return error;
}*/
ptr->TAIL++;
(ptr->NO_OF_ITEMS)--;
}
uint8_t size()
{
return ptr->NO_OF_ITEMS;
}

status destroy()
{
        free(ptr);
	return Success;
}


void main()
{       printf("main");
        
	allocate(&ptr);
        add(5);
        uint8_t s = size();
        printf("size is %d",s);
        add(6);
        uint8_t s1 = size();
        printf("size is %d",s);
        add(7);
        uint8_t s2 = size();
        printf("size is %d",s);
        //destroy();
        //printf("size after free the memory is %d",ptr->SIZE);
}

