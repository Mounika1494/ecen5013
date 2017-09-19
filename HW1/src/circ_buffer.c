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



/*allocate and initialise the buffer and structure*/
Status allocate(Buffer ** d_pointer)
{
        void *memory = NULL;
        Buffer* mybuffer =  (Buffer*)malloc(sizeof(Buffer));
        //printf("Enter the size \n");
        //scanf("%d",&(mybuffer->SIZE));
        mybuffer->SIZE = 5;
	memory = (void*)malloc(sizeof(void*)*(mybuffer->SIZE));
	if(memory == NULL)
	{
        return Fail;
	}
	mybuffer->BASE = (Buffer*)memory;
	mybuffer->HEAD = (Buffer*)memory;
	mybuffer->TAIL = (Buffer*)memory;
        (*d_pointer) = mybuffer;
	return Success;
}

/*if head has reached the end then loop back*/
bool Is_buffer_full(Buffer *new_buffer)
{	
     if(new_buffer->HEAD==(new_buffer->BASE + ((new_buffer->SIZE)*(sizeof(void*)))))
	{
        printf("Buffer is full\n");
	return true;
	}
	else
	return false;	
}

/*if head and tail are pointed to the same address then buffer is empty*/
bool Is_buffer_empty(Buffer *new_buffer)
{	
        //printf("head is at %d tail is at %d\n",new_buffer->HEAD,new_buffer->TAIL);
	if((new_buffer->HEAD)==(new_buffer->TAIL))
	return true;
	else
	return false;	
}

/*add the data pointed by the pointer */
Status add(Buffer *new_buffer,void *data)
{
        //printf("data is %d\n",*(uint32_t*)data);
        //printf("newbuffer head is at %d\n",new_buffer->HEAD);
        if(new_buffer == NULL)
        {
        return error;
        }
	if(data == NULL)
        {
	return error;
	}
        if(new_buffer->TAIL == NULL || new_buffer->HEAD == NULL || new_buffer->BASE == NULL)
        {
        return error;
        }
        if(Is_buffer_full(new_buffer))
        {
        if(new_buffer->TAIL==new_buffer->BASE)
        {
        printf("Buffer is full.Should remove an item before adding\n");
        return Fail;
        }
        else
        {
        new_buffer->HEAD=new_buffer->BASE;
	//printf("looping back\n");
        }
        }       
        *(uint32_t*)(new_buffer->HEAD) = *(uint32_t*)data;
        new_buffer->HEAD = new_buffer->HEAD + sizeof(void*);
        new_buffer->NO_OF_ITEMS = new_buffer->NO_OF_ITEMS+1;
        if(new_buffer->NO_OF_ITEMS > new_buffer->SIZE)
        new_buffer->NO_OF_ITEMS=new_buffer->SIZE;
        return Success;
}

/*removes the item where tail is pointed to*/
Status remove_item(Buffer *new_buffer)
{
         if(new_buffer == NULL)
         {
          return error;
         }
         if(new_buffer->TAIL == NULL || new_buffer->HEAD == NULL || new_buffer->BASE == NULL)
         {
          return error;
         }
         if(Is_buffer_empty(new_buffer))
         {
         printf("Buffer Empty\n");
         return Fail;
         }
	 if((new_buffer->TAIL) == (new_buffer->BASE + ((new_buffer->SIZE)*sizeof(void*))))
         {
         //printf("tail looping back\n");
         new_buffer->TAIL = (void *)new_buffer->BASE;
         }
         new_buffer->TAIL = new_buffer->TAIL+sizeof(void*);
         new_buffer->NO_OF_ITEMS--;
         return Success;
}

/*returns the variable in the buffer structure*/
uint16_t size(Buffer *new_buffer)
{
	if(new_buffer == NULL)
	{
	return error;
	}
        return new_buffer->NO_OF_ITEMS;
}

/*destroys the circular buffer*/
Status destroy(Buffer *new_buffer)
{
	 if(new_buffer->TAIL == NULL || new_buffer->HEAD == NULL || new_buffer->BASE == NULL)
         {
         return error;
         }
         free(new_buffer->BASE);
         free(new_buffer);
         new_buffer->TAIL = NULL;
	 new_buffer->HEAD = NULL;
         new_buffer->NO_OF_ITEMS = 0;
         new_buffer = 0;
         return Success;
}

/*prints the data in the buffer in a readable format*/
void dump(Buffer *new_buffer)
{
         void *traverse = NULL;
         traverse = (void*)new_buffer->TAIL;
         if(traverse==NULL)
         {
         printf("Error in the address\n");
         }
         for(int i=0;i<(new_buffer->NO_OF_ITEMS);i++)
         {
         printf("buffer at index  %d has %d\n",i,*(uint32_t*)(traverse));
         traverse = traverse + sizeof(void*);
         if(traverse == (new_buffer->BASE + ((new_buffer->SIZE)*sizeof(void*))))
         {
         printf("tail looping back\n");
         traverse = (void *)new_buffer->BASE;
         }
         }
}

/*int main()
{      
        Buffer* new_buffer = NULL;  
	allocate(&new_buffer);
        uint32_t item;
        item =5;
        add(new_buffer,&item);
        item =6;
        add(new_buffer,&item);
        item=7;
        add(new_buffer,&item);
        item=8;
        add(new_buffer,&item);
        item=9;
        add(new_buffer,&item);
        item=10;
        add(new_buffer,&item);
        dump(new_buffer);
        remove_item(new_buffer);
        printf("removed an item\n");
        dump(new_buffer);
        item=11;
        add(new_buffer,&item);
        dump(new_buffer);
        destroy(new_buffer);
        return 0;
}*/

