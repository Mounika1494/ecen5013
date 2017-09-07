/**********************************************************************************************************
* Copyright (C) 2017 by Mounika Reddy Edula
*
*Redistribution,modification or use of this software in source or binary fors is permitted as long 
*as the files maintain this copyright.Mounika Reddy Edula is not liable for any misuse of this material
*
*********************************************************************************************************/
/**
*@file double_ll.h
*@brief Double linked list implemetation
*
*This header file provides how to add/delete,search nodes in double linked list via function calls
*
*@author Mounika Reddy Edula
*@date September 92017
*@version 1.0
*
*/
#ifndef __DOUBLE_LL_H__
#define __DOUBLE_LL_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*enum for status of the function*/
typedef enum  
{
	Success =0,
	Fail = 1,
	error
}Status;

/* struct for each node in the linked list*/
struct node
{
void *data;
struct node *previous;
struct node *next;
};

/**
* @brief destroys all nodes in the linked list
*
* head of the linked list will be traversed till the
* last node and all nodes are freed
*
*@param void
*
*@return Status fail - any null pointer access
*               success - successfull destruction of the linked list
*/
Status destroy();

/**
* @brief adds a node to the list at index provided and data given 
* by the pointer
*
* head of the linked list will be traversed till the previous node of
* index and node is attached to previous and next nodes
* 
*
*@param head double pointer to the head of the linked list
*@param data pointer to the data to be added to the list
*@param index number at which the node is added
*
*@return Status fail - any null pointer access, index > (size of linked list+1)
*               success - successfull addition of node to the linked list
*/
Status add_node(struct node **head,void *data,uint16_t index);

/**
* @brief removes a node from the list at index provided and data at node 
* is stored at the pointer
*
* base of the linked list will be traversed till the previous node of
* index and node is removed, linking of previous and next nodes is updated
* 
*
*@param base double pointer to the head of the linked list
*@param data pointer to the data which stores the data from the node
*@param index number at which the node is deleted
*
*@return Status fail - any null pointer access, index > (size of linked list+1)
*               success - successfull addition of node to the linked list
*/
Status remove_node(struct node **base,void *data,uint16_t index);

/**
* @brief searches through the list for the data provided  
* 
*
* head of the linked list will be traversed through
* entire list till the data provided by pointer is found
* 
*
*@param data pointer to the data to be found
*
*@return pointer the index is returned in the form of a pointer
*/
uint8_t* search(void *data);

/**
* @brief number of nodes in the linked list  
* 
*
* head of the linked list will be traversed through
* entire list and number of nodes is updated
* 
*
*@param void
*
*@return uint16_t size of the linked list is returned
*/
uint16_t size();

void print();

#endif /*__DOUBLE_LL_H__*/
