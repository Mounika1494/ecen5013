#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdbool.h>
#include "double_ll.h"


void test_add_node(void **state)
{
struct node* test_head=NULL;
int return_value;
uint32_t data;
//test if you try to remove node on empty list
uint8_t *removed_data = malloc(sizeof(uint8_t));
return_value = remove_node(&test_head,removed_data,1);
assert_int_equal(return_value,Fail);
//add a node
data = 20;
return_value = add_node(&test_head,&data,1);
assert_int_equal(return_value,Success);
//add nodes sequentially
data = 30;
return_value = add_node(&test_head,&data,2);
assert_int_equal(return_value,Success);
data = 40;
return_value = add_node(&test_head,&data,3);
assert_int_equal(return_value,Success);
data =50;
return_value = add_node(&test_head,&data,1);
assert_int_equal(return_value,Success);
data =80;
return_value = add_node(&test_head,&data,1);
assert_int_equal(return_value,Success);
data = 60;
return_value = add_node(&test_head,&data,2);
assert_int_equal(return_value,Success);
data = 70;
return_value = add_node(&test_head,&data,3);
assert_int_equal(return_value,Success);
destroy(&test_head);
test_head = NULL;
printf("***1.test to add node passed*****\n");
}

void test_remove_node(void **state)
{
struct node* test_head=NULL;
struct node* remove_head=NULL;
int return_value;
int32_t data;
//test when buffer is not allocated and item is removed
data = 20;
add_node(&test_head,&data,1);
//add nodes sequentially
data = 30;
add_node(&test_head,&data,2);
data = 40;
add_node(&test_head,&data,3);
//add item and then remove 
data = 2000;
add_node(&test_head,&data,4);
uint16_t *removed_data = malloc(sizeof(uint8_t));
return_value = remove_node(&test_head,removed_data,1);
printf("After node remove at 1\n");
print(&test_head);
assert_int_equal(*removed_data,20);
assert_int_equal(return_value,Success);
return_value = remove_node(&test_head,removed_data,5);
assert_int_equal(return_value,Fail);
return_value = remove_node(&remove_head,removed_data,2);
assert_int_equal(return_value,Fail);
return_value = remove_node(&test_head,NULL,3);
assert_int_equal(return_value,Fail);
return_value = remove_node(&test_head,removed_data,3);
assert_int_equal(*removed_data,2000);
assert_int_equal(return_value,Success);
return_value = remove_node(&test_head,removed_data,4);
assert_int_equal(return_value,Fail);
return_value = remove_node(&test_head,removed_data,1);
assert_int_equal(*removed_data,30);
destroy(&test_head);
printf("***2. delete item test passed****\n");
}



void test_size(void **state)
{
struct node* test_head=NULL;
int return_value;
int32_t data;
return_value = size(&test_head);
assert_int_equal(return_value,0);
//test when buffer is not allocated and item is removed
data = 20;
add_node(&test_head,&data,1);
//add nodes sequentially
data = 30;
add_node(&test_head,&data,2);
data = 40;
add_node(&test_head,&data,3);
//add item and then remove 
data = 2000;
add_node(&test_head,&data,4);
return_value = size(&test_head);
assert_int_equal(return_value,4);
remove_node(&test_head,&data,3);
return_value = size(&test_head);
assert_int_equal(return_value,3);
destroy(&test_head);
test_head = NULL;
printf("***5. size test passed*****\n");
}

void test_search(void **state)
{
struct node* test_head=NULL;
int32_t data;
uint8_t *index=NULL;
uint8_t *error=malloc(sizeof(uint8_t));;
*error =0;
index = search(&test_head,&data);
assert_int_equal(*index,*error);
index = search(&test_head,NULL);
assert_int_equal(*index,*error);
//test when buffer is not allocated and item is removed
data = 20;
add_node(&test_head,&data,1);
//add nodes sequentially
data = 30;
add_node(&test_head,&data,2);
data = 40;
add_node(&test_head,&data,3);
//add item and then remove 
data = 2000;
add_node(&test_head,&data,4);
data = 20;
index = search(&test_head,&data);
assert_int_equal(*index,1);
data = 2000;
index = search(&test_head,&data);
assert_int_equal(*index,4);
data = 40;
index = search(&test_head,&data);
assert_int_equal(*index,3);
remove_node(&test_head,&data,3);
data = 40;
index = search(&test_head,&data);
assert_int_equal(*index,0);
destroy(&test_head);
test_head = NULL;
printf("***5. search test passed*****\n");
}

void test_destroy(void **state)
{
struct node* test_head=NULL;
int return_value;
uint8_t data;
return_value = destroy(&test_head);
assert_int_equal(return_value,Fail);
data = 20;
add_node(&test_head,&data,1);
return_value = destroy(&test_head);
assert_int_equal(return_value,Success);
}

int main(int argc,char **argv)
{
const struct CMUnitTest test[] = {
       cmocka_unit_test(test_add_node),
       cmocka_unit_test(test_remove_node),
       cmocka_unit_test(test_size),
       cmocka_unit_test(test_search),
       cmocka_unit_test(test_destroy)
       };

return cmocka_run_group_tests(test,NULL,NULL);
}

