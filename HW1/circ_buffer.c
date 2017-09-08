#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "circ_buffer.h"
/**************************************************************************************
*@Filename:circ_buffer.c
*
*@Description: Implementation of different functions like allocation,
destroy,is_buffer_full,is_buffer_empty,add,remove data to buffer,
dump - print the elements,size - number of items 
*
*@Author:Mounika Reddy Edula
*@Date:09/07/2017
*@compiler:gcc
*@debugger:gdb
**************************************************************************************/

Buffer* new_buffer = NULL;

/*allocate and initialise the buffer and structure*/
Status allocate(Buffer ** d_pointer)
{
        void *memory = NULL;
        Buffer* mybuffer =  (Buffer*)malloc(sizeof(Buffer));
        scanf("%d",&(mybuffer->SIZE));
	memory = (void*)malloc(sizeof(void*)*(mybuffer->SIZE));
	if(memory == NULL)
	{
        return Fail;
	}
	mybuffer->BASE = memory;
	mybuffer->HEAD = memory;
	mybuffer->TAIL = memory;
        (*d_pointer) = mybuffer;
	return Success;
}

/*if head has reached the end then loop back*/
bool Is_buffer_full()
{	
     if(new_buffer->HEAD==(new_buffer->BASE + ((new_buffer->SIZE)*(sizeof(void*)))))
	{
        new_buffer->HEAD=new_buffer->BASE;
	return true;
	}
	else
	return false;	
}

/*if head and tail are pointed to the same address then buffer is empty*/
bool Is_buffer_empty()
{
	if((new_buffer->HEAD)==(new_buffer->TAIL))
	return true;
	else
	return false;	
}

/*add the data pointed by the pointer */
Status add(void *data)
{
        if(Is_buffer_full())
        {
        printf("Buffer is full looping back\n");
        }
        *(uint32_t*)(new_buffer->HEAD) = *(uint32_t*)data;
        printf("buffer at address %d has %d\n",(new_buffer->HEAD),*(uint32_t*)(new_buffer->HEAD));
        new_buffer->HEAD = new_buffer->HEAD + sizeof(void*);
        new_buffer->NO_OF_ITEMS=new_buffer->NO_OF_ITEMS+1;
        if(new_buffer->NO_OF_ITEMS > new_buffer->SIZE)
        new_buffer->NO_OF_ITEMS=new_buffer->SIZE;
        return Success;
}

/*removes the item where tail is pointed to*/
Status remove_item()
{
         if(Is_buffer_empty())
         {
         printf("Buffer Empty\n");
         return Fail;
         }
         new_buffer->TAIL = new_buffer->TAIL+sizeof(void*);
         new_buffer->NO_OF_ITEMS--;
         return Success;
}

/*returns the variable in the buffer structure*/
uint16_t size()
{
         return new_buffer->NO_OF_ITEMS;
}

/*destroys the circular buffer*/
Status destroy()
{
         free(new_buffer->BASE);
         free(new_buffer);
         new_buffer = 0;
         return Success;
}

/*prints the data in the buffer in a readable format*/
void dump()
{
         void *traverse = NULL;
         traverse = (void*)new_buffer->TAIL;
         if(traverse==NULL)
         {
         printf("Error in the address\n");
         }
         for(int i=0;i<(new_buffer->NO_OF_ITEMS);i++)
         {
         printf("buffer at address %d index  %d has %d\n",(traverse),i,*(uint32_t*)(traverse));
         traverse = traverse + sizeof(void*);
         }
}

int main()
{        
	allocate(&new_buffer);
        uint32_t item;
        item =5;
        add(&item);
        item =6;
        add(&item);
        item=7;
        add(&item);
        item=8;
        add(&item);
        item=9;
        add(&item);
        item=10;
        add(&item);
        dump();
        remove_item();
        dump();
        destroy();
        return 0;
}

