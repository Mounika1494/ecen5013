#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
typedef enum  
{
	Success =0,
	Fail = 1,
	Error
}Status;

typedef struct
{
	uint8_t* HEAD;
	uint8_t* TAIL;
	uint8_t* BASE;
	uint8_t  SIZE;
	uint16_t NO_OF_ITEMS
}Buffer;

Buffer* new_buffer = NULL;

Status allocate(Buffer ** d_pointer);
Status destroy();
bool Is_buffer_full();
bool Is_buffer_empty();
Status add(void *data);
Status remove_item();
void dump();
uint8_t size();

/*allocateand initialise the buffer and structure*/
Status allocate(Buffer ** d_pointer)
{
        char *memory;
        Buffer* mybuffer =  (Buffer*)malloc(sizeof(Buffer));
        printf("Enter the size of circular buffer\n");
        scanf("%d",&(mybuffer->SIZE));
        printf("buffer size is %d\n",mybuffer->SIZE);
	memory = (char*)malloc(sizeof(char)*(mybuffer->SIZE));
	if(memory == NULL)
	{
	printf("fail");	
        return Fail;
	}
	mybuffer->BASE = memory;
	mybuffer->HEAD = memory;
	mybuffer->TAIL = memory;
        printf("Head of buffer is at %d\n",mybuffer->HEAD);
        printf("Tail of buffer is at %d\n",mybuffer->TAIL);
        (*d_pointer) = mybuffer;
	return Success;
}

/*if head has reached the end then loop back*/
bool Is_buffer_full()
{	
     if(new_buffer->HEAD==(new_buffer->BASE + (new_buffer->SIZE)*(sizeof(uint8_t))))
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
        printf("item added at address %d index  %d has %d\n",(new_buffer->HEAD),new_buffer->NO_OF_ITEMS,*(int*)data);
        *(new_buffer->HEAD++) = *(int*)data;
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
         //return Error;
         }
         printf("item is removed at address %d\n",new_buffer->TAIL);
         new_buffer->TAIL++;
         new_buffer->NO_OF_ITEMS--;
         return Success;
}

/*returns the variable in the buffer structure*/
uint8_t size()
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
         uint8_t *traverse;
         traverse = malloc(sizeof(uint8_t));
         traverse = new_buffer->TAIL;
         if(traverse==NULL)
         {
         printf("Error in the address\n");
         }
         for(int i=0;i<(new_buffer->NO_OF_ITEMS);i++)
         {
         printf("buffer at address %d index  %d has %d\n",(traverse),i,*(traverse));
         traverse++;
         if(traverse == (new_buffer->BASE + (((new_buffer->SIZE))*(sizeof(uint8_t)))))
         traverse=new_buffer->BASE;
         }
}

void main()
{        
	allocate(&new_buffer);
        uint8_t item;
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
}

