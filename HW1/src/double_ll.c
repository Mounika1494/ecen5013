#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "double_ll.h"
/**************************************************************************************
*@Filename:double_ll.c
*
*@Description: Implementation of different functions like adding or deleting node,
search data in the list,size of the double linked list 
*
*@Author:Mounika Reddy Edula
*@Date:09/07/2017
*@compiler:gcc
*@debugger:gdb
**************************************************************************************/


/**dumps data present in linked list****/
void print(struct node **head)
{
	struct node *current = *head;
	while(current!=NULL)
	{
        printf("current has %d\n",*(uint32_t*)current->data);
	current=current->next;
	}
        free(current);
}

/******returns the size of linked list*******/
uint16_t size(struct node **head)
{
	uint16_t dll_size=0;
	struct node *current = *head;
        if(current == NULL)
        {
         return 0;
        }
	while(current!=NULL)
	{
	dll_size++;
	current=current->next;
	}
        free(current);
	return dll_size;
}

/*returns Fail if any null pointer is accessed or adding a node at index greater than size of linked list*/
Status add_node(struct node **head, void *item,uint16_t index)
{
	struct node *new_node = (struct node*) malloc(sizeof(struct node));
	struct node *traverse = *head;
	new_node->data =  malloc(sizeof(int));
	*(int*)(new_node -> data) = *(int*)item;
	new_node -> next = NULL;
        printf("Size is %d\n",size(&traverse));
        if(index>(size(&traverse)+1))
        {
         return Fail;
        }
        if(item == NULL)
        {
        return Fail;
        }
	if (*head ==NULL)
	{
	*head = new_node;
	new_node->previous = NULL;
	}
	else
	{
	for(int i=1;i<(index-1);i++)
	{
	traverse = traverse->next;
	}
	if(index==1)
	{
	new_node->previous=NULL;
	new_node->next = traverse;
	*head=new_node;
	}
	else
	{
	new_node->next = traverse->next;
	traverse->next = new_node;
	new_node->previous = traverse;
	}
	if(new_node->next!=NULL)
	{
	new_node->next->previous=new_node;
	}
	}
	return Success;
}

/*** seraches for an item in the linked list and returns the index pointer***/
uint8_t* search(struct node **head,void *item)
{
	struct node *traverse = *head;
	uint8_t *index  = malloc(sizeof(uint8_t));
        *index=1;
	if(*head == NULL)
        {
        *index = 0;
	return index;
        }
        if(head == NULL)
        {
        *index = 0;
	return index;
        }
        if(item == NULL)
        {
	*index = 0;
	return index;
	}
	while(traverse!=NULL)
	{
	 if(*(int*)(traverse->data) == *(int*)item)
          {
	   return index;
	  }
          traverse=traverse->next;
          (*index)++;
        }
     *index =0;
     free(traverse);
     return index;	
}

/*** destroys all nodes in the linked list****/
Status destroy(struct node **head)
{
	if(*head == NULL)
        {
        return Fail;
        }
        struct node *tmp = NULL;
        struct node *temp_head = *head;
	while(temp_head!=NULL)
	{
	tmp = temp_head;
	free(temp_head);
	temp_head->next = NULL;
        temp_head->previous = NULL;
	temp_head=tmp->next;       
	}
	return Success;
}

/*returns fail if any null pointer is accessed or index > size of linked list*/
Status remove_node(struct node **head,void *data,uint16_t index)
{
        struct node *traverse = *head;
        if(*head == NULL)
        {
        return Fail;
        }
        if(head == NULL)
        {
        return Fail;
        }
        if(data == NULL)
        {
	return Fail;
	}
	if(index>(size(&traverse)))
        {
         printf("out of range\n");
         return Fail;
        }
	for(int i=0;i<(index-1);i++)
	{
	traverse = traverse->next;
	}
        *(int*)data = *(int*)(traverse->data);
        if(traverse->next != NULL && traverse->previous != NULL)
        {
        traverse->previous->next = traverse->next;
        traverse->next->previous = traverse->previous;
        }
        else if(traverse->next == NULL)
        {
        traverse->previous->next = NULL;
        }
        else if(traverse->previous == NULL)
        {
        *head = traverse->next;
        traverse->next->previous = NULL;
        }
        free(traverse);
        return Success;
}

/*int main()
{
struct node *head = NULL;
uint8_t *removed_data1 = malloc(sizeof(uint8_t));
remove_node(&head,removed_data1,1);
uint32_t data1 = 20;
add_node(&head,&data1,1);
print(&head);
uint32_t data2=30;
add_node(&head,&data2,2);
print(&head);
uint32_t data3=40;
add_node(&head,&data3,3);
print(&head);
uint32_t data4=50;
add_node(&head,&data4,1);
print(&head);
uint32_t data5=60;
add_node(&head,&data5,2);
print(&head);
uint32_t data=30;
uint8_t* index;
index=search(&head,&data);
printf("found at %d\n",*index);
uint8_t *removed_data = malloc(sizeof(uint8_t));
remove_node(&head,removed_data,1);
print(&head);
destroy(&head);
return 0;
}*/
