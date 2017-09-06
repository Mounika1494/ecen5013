#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
typedef enum  
{
	Success =0,
	Fail = 1,
	error
}status;

struct node
{
void *data;
struct node *previous;
struct node *next;
};

struct node* head=NULL;
status destroy();
status add_node(struct node **head,void *data,uint16_t index);
status remove_node(struct node **base,void *data,uint16_t index);
uint8_t* search(void *data);
uint16_t size();
void print();

void print()
{
	struct node* current = (struct node*) malloc(sizeof(struct node));
	current=head;
	while(current!=NULL)
	{
	printf("%d\n",*(int*)(current->data));
	current=current->next;
	}
}

uint16_t size()
{
	uint16_t dll_size=0;
	struct node* current = (struct node*) malloc(sizeof(struct node));
	current=head;
	while(current!=NULL)
	{
	dll_size++;
	current=current->next;
	}
	return dll_size;
}

status add_node(struct node **head, void *item,uint16_t index)
{
	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	struct node *traverse = *head;
	new_node->data =  malloc(sizeof(int));
	*(int*)(new_node -> data) = *(int*)item;
	new_node -> next = NULL;
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
uint8_t* search(void *item)
{
	uint8_t *index;
        uint8_t temp;
        index=&temp;
        *index=1;
        struct node* traverse = (struct node*) malloc(sizeof(struct node));
        traverse=head;
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
     return index;	
}

status destroy()
{
	while(head!=NULL)
	{
	free(head);
	head=head->next;
	}
	return Success;
}

status remove_node(struct node **head,void *data,uint16_t index)
{
        struct node *traverse = *head;
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

}

void main()
{
uint32_t data1 = 20;
add_node(&head,&data1,1);
print();
printf("size of linked list is %d\n",size());
uint32_t data2=30;
printf("head is at address %d\n",head);
add_node(&head,&data2,2);
print();
printf("head is at address %d\n",head);
uint32_t data3=40;
add_node(&head,&data3,3);
print();
printf("head is at address %d\n",head);
uint32_t data4=50;
add_node(&head,&data4,1);
print();
printf("size of linked list is %d\n",size());
printf("head is at address %d\n",head);
uint32_t data5=60;
add_node(&head,&data5,2);
print();
printf("size of linked list is %d\n",size());
uint32_t data=30;
uint8_t* index;
index=search(&data);
printf("data %d is found at index %d\n",data,*index);
uint8_t *removed_data = malloc(sizeof(uint8_t));
remove_node(&head,removed_data,1);
printf("size of linked list is %d\n",size());
printf("data removed is %d\n",*removed_data);
print();
destroy();
}


