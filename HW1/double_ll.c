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
status remove_node(struct node **base,uint16_t index);
void search(void *data);
uint16_t size();

status add_node(struct node **head, void *item,uint16_t index)
{
struct node* new_node = (struct node*) malloc(sizeof(struct node));
printf("new node address is at %d", new_node);
struct node *traverse = *head;
new_node -> data = item;
new_node -> next = NULL;
if (*head ==NULL)
{
printf("linked list is empty\n");
*head = new_node;
new_node->previous = NULL;
printf("data %d is added at index %d whose next is %d and previous is at %d\n",index,*(int*)(new_node->data),new_node->next,new_node->previous);  
}
else
{
for(int i=1;i<(index-1);i++)
{
traverse = traverse->next;
}
new_node->next = traverse->next;
traverse->next = new_node;
new_node->previous = traverse;
if(new_node->next!=NULL)
{
new_node->next->previous=new_node;
printf("next node is at address %d and next to %d and previous to %d\n",new_node->next,new_node->next->next,new_node->next->previous);
}
printf("previous node is at address %d and next to %d and previous to %d\n",traverse,traverse->next,traverse->previous);
printf("data %d is added at index %d whose next is %d and previous is at %d\n",index,*(int*)(new_node->data),new_node->next,new_node->previous);
}
return Success;
}

void main()
{
uint32_t data = 20;
add_node(&head,&data,1);
data=30;
printf("head is at address %d\n",head);
add_node(&head,&data,2);
printf("head is at address %d\n",head);
data=40;
add_node(&head,&data,3);
printf("head is at address %d\n",head);
data=50;
add_node(&head,&data,1);
}


