#include<stdlib.h>
#include<stdint.h>
//uint8_t length=4;
/**** adding the data to the circular buffer***/
/*uint8_t add_data(structure *s,uint8_t Value,uint8_t length)
{
/*** check before writing the values whether the buffer is full****/
//if(Buffer_Full(s,length))
//{
//printf("Buffer is full");
//return -1;
//}

//*s->HEAD++= Value;/*** writing the value onto the HEAD**/
 //s->HEAD++;
//return 0;
//}*/
/****Buffer full****/
/*uint8_t Buffer_Full(structure *s,uint8_t length)
{
if(s->HEAD==(s->Buffer + (length-1)*(sizeof(uint8_t))))
{
s->HEAD=s->Buffer;
	return 1;
}
else
return 0;
}*/
/****Buffer Empty****/
/*uint8_t Buffer_Empty(structure *s)
{
if((s->HEAD)==(s->TAIL))
return 1;
else
return 0;
}*/
/**** Buffer Remove*****/
/*uint8_t remove_data(structure *s)
{
if(Buffer_Empty(s))
{
//printf("Buffer is Empty");
return -1;
}
else
{
s->TAIL++;
return 0;
}
}
uint8_t get_data(structure *s,uint8_t length)
{
/*** check before writing the values whether the buffer is full****/
/*if(Buffer_Empty(s))
{
//printf("Buffer is Empty");
return -1;
}
if(s->TAIL==(s->Buffer + (length-1)*(sizeof(uint8_t))))
{
	s->TAIL=s->Buffer;
}
//s->HEAD--;
return(*s->TAIL++);/*** writing the value onto the HEAD**/
//s->HEAD++;
// return 0;
//}
typedef enum
{
	false = 0, 
	true =1
}bool;
typedef enum  
{
	Success =0,
	Fail = 1,
	error
}Status;
Status allocate(void ** d_pointer);
Status destroy();
char *p_pointer;
void main()
{	
	//enum Status state;
	allocate(&p_pointer);
}
Status allocate(void ** d_pointer)
{
	if(d_pointer == NULL)
	{
		return error;
	}
	typedef struct {
			uint8_t* HEAD;
			uint8_t* TAIL;
			uint8_t* BASE;
			uint8_t  SIZE;
			uint16_t NO_OF_ITEMS;
			}Buffer;
	 Buffer ** mybuffer;
	 mybuffer =(Buffer **) d_pointer;
        (*mybuffer)->SIZE = 50;
	 char *memory;
	memory = (char*)malloc(sizeof(char)*((*mybuffer)->SIZE));
	if(memory == NULL)
	{
		return Fail;
	}
	(*mybuffer)->BASE = memory;
	(*mybuffer)->HEAD = memory;
	(*mybuffer)->TAIL = memory;
        printf("Circular Buffer Base is at %d",(*mybuffer)->BASE);
        printf("Circular Budder Head is ar %d",(*mybuffer)->HEAD);
        printf("Circular Buffer Tail is at %d",(*mybuffer)->TAIL);
	return Success;
}
Status destroy()
{
	free(&p_pointer);
	return Success;
}
/*bool Is_buffer_full()
{
	if(s->HEAD==(s->Buffer + (length-1)*(sizeof(uint8_t))))
	{
	s->HEAD=s->Buffer;
		return true;
	}
	else
	return false;	
}
bool Is_buffer_empty()
{
	if((s->HEAD)==(s->TAIL))
	return true;
	else
	return false;	
}*/



