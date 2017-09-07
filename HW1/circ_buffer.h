/**********************************************************************************************************
* Copyright (C) 2017 by Mounika Reddy Edula
*
*Redistribution,modification or use of this software in source or binary fors is permitted as long 
*as the files maintain this copyright.Mounika Reddy Edula is not liable for any misuse of this material
*
*********************************************************************************************************/
/**
*@file circ_buffer.h
*@brief Circular Buffer implementation
*
*This header file provides how to add/delete,se
*
*@author Mounika Reddy Edula
*@date September 92017
*@version 1.0
*
*/
#ifndef __DOUBLE_LL_H__
#define __DOUBLE_LL_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*enum for status of the function*/
typedef enum  
{
	Success =0,
	Fail = 1,
	error
}Status;

/* struct for the circular buffer*/
typedef struct
{
	uint8_t* HEAD;
	uint8_t* TAIL;
	uint8_t* BASE;
	uint8_t  SIZE;
	uint16_t NO_OF_ITEMS
}Buffer;

bool Is_buffer_full();
bool Is_buffer_empty();
Status add(void *data);
Status remove_item();
void dump();
uint8_t size();

/**
* @brief destroys the circular buffer
*
* free the circular buffer
* 
*
*@param void
*
*@return Status fail - any null pointer access
*               success - successfull deletion of circular buffer
*/
Status destroy();

/**
* @brief allocates and initialises the buffer and the structure in
* dynamic memory
*
* allocates memory for circular buffer and strucure and intialises the 
* head,tail,buffer to the circular buffer 
* 
*@param d_pointer double pointer to the buffer structure 
*
*@return Status fail - memory allocation for buffer fails
*        success - successfull initialisation of buffer/structure to the linked list
*/
Status allocate(Buffer ** d_pointer);

/**
* @brief check if buffer is full
*
* if head reaches the end point in circular buffer which is base + size of circular
* buffer 
*
*@param void
*
*@return bool true - buffer is full
*               false - buffer is not full
*/
bool Is_buffer_full();

/**
* @brief check if buffer is empty
*
* as head moves forward with addition of new data if head and data are at same address
* then buffer is empty 
*
*@param void
*
*@return bool true - buffer is empty
*               false - buffer is not empty
*/
bool Is_buffer_empty();

/**
* @brief adds data provided to the buffer
* 
*
* head is moved forward if we reach the end then we loop back
*
*@param void
*
*@return Status fail - if data pointer is NULL
*        success - when the data is added successfully
*/
Status add(void *data);

/**
* @brief removes the item from buffer 
*
* removes the item tail was pointing to 
* when tail meets the head then buffer is empty
*
*@param void
*
*@return Status fail - if buffer is empty
*        success - when the data is removed successfully
*/
Status remove_item();

/**
* @brief number of data in the buffer  
* 
* the variable in the structure which is constantly 
* updated when data is added and removed
*
*@param void
*
*@return uint16_t number of elements added is returned
*/
uint16_t size();

/**
* @brief print the data in the buffer in a readable format 
* 
* read the data from tail add another pointer from tail 
* so that operations are not affected
*
*@param void
*
*@return void
*/
void dump();

#endif /*__DOUBLE_LL_H__*/
