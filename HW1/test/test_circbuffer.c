#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdbool.h>
#include "circ_buffer.h"


void test_add_item(void **state)
{
Buffer* test_buffer = NULL;
int32_t data = 30982;
int return_value;
//test if buffer accessed without buffer being allocated
return_value = add(test_buffer,&data);
assert_int_equal(return_value,error);
//Buffer allocation
return_value = allocate(&test_buffer);
assert_int_equal(return_value,Success);
//test to add item after buffer allocation
return_value = add(test_buffer,&data);
assert_int_equal(return_value,Success);
//test to see if data is overwritten
data = 2000;
add(test_buffer,&data);
data = -1000;
add(test_buffer,&data);
data = 500;
add(test_buffer,&data);
data = 60000;
add(test_buffer,&data);
data = 50;
return_value = add(test_buffer,&data);
assert_int_equal(return_value,Fail);
//test to see if buffer is looped back
remove_item(test_buffer);
data = 100;
return_value = add(test_buffer,&data);
assert_int_equal(return_value,Success);
destroy(test_buffer);
test_buffer = NULL;
printf("***1.add item test passed*****\n");
}

void test_remove_item(void **state)
{
Buffer* test_buffer = NULL;
int return_value;
int32_t data;
//test when buffer is not allocated and item is removed
return_value = remove_item(test_buffer);
assert_int_equal(return_value,error);
//remove item when buffer is empty
allocate(&test_buffer);
return_value = remove_item(test_buffer);
assert_int_equal(return_value,Fail);
//add item and then remove 
data = 2000;
add(test_buffer,&data);
return_value = remove_item(test_buffer);
assert_int_equal(return_value,Success);
data = -1000;
add(test_buffer,&data);
data = 500;
add(test_buffer,&data);
data = 60000;
add(test_buffer,&data);
data = 50;
add(test_buffer,&data);
//remove all items in the buffer
return_value = remove_item(test_buffer);
//see if tail is looped back to remove the item
return_value = remove_item(test_buffer);
assert_int_equal(return_value,Success);
return_value = remove_item(test_buffer);
assert_int_equal(return_value,Success);
remove_item(test_buffer);
//when buffer is empty
return_value = remove_item(test_buffer);
assert_int_equal(return_value,Fail);
destroy(test_buffer);
test_buffer = NULL;
printf("***2. delete item test passed****\n");
}

void test_is_buffer_full(void **state)
{
Buffer* test_buffer = NULL;
int32_t data;
bool value;
//test if buffer is full when it is empty
allocate(&test_buffer);
//test if buffer is full when item is added
data = 2000;
add(test_buffer,&data);
data = -1000;
add(test_buffer,&data);
assert_false(Is_buffer_full(test_buffer));
//assert_int_equal(value,false);
data = 500;
add(test_buffer,&data);
data = 60000;
add(test_buffer,&data);
data = 40;
add(test_buffer,&data);
assert_true(Is_buffer_full(test_buffer));
//test if buffer is full after removing an item
remove_item(test_buffer);
printf("size after removing an element is %d\n",size(test_buffer));
data = 40;
add(test_buffer,&data);
data = 40;
add(test_buffer,&data);
assert_false(Is_buffer_full(test_buffer));
destroy(test_buffer);
test_buffer = NULL;
printf("***3. Is buffer full test passed*****\n");
}

void test_is_buffer_empty(void **state)
{
Buffer* test_buffer = NULL;
int return_value = 0;
int32_t data;
//remove item when buffer is empty
allocate(&test_buffer);
assert_true(Is_buffer_empty(test_buffer));
//add item and then remove 
data = 2000;
add(test_buffer,&data);
assert_false(Is_buffer_empty(test_buffer));
data = -1000;
add(test_buffer,&data);
data = 500;
add(test_buffer,&data);
data = 60000;
add(test_buffer,&data);
data = 50;
add(test_buffer,&data);
//remove all items in the buffer
remove_item(test_buffer);
//see if tail is looped back to remove the item
remove_item(test_buffer);
remove_item(test_buffer);
remove_item(test_buffer);
//when buffer is empty
remove_item(test_buffer);
assert_true(Is_buffer_empty(test_buffer));
destroy(test_buffer);
test_buffer = NULL;
printf("******4. Is buffer empty test passed*****\n");
}

void test_size(void **state)
{
Buffer* test_buffer = NULL;
int return_value;
int32_t data;
//remove item when buffer is empty
allocate(&test_buffer);
return_value = size(test_buffer);
assert_int_equal(return_value,0);
//add item 
data = 2000;
add(test_buffer,&data);
return_value = size(test_buffer);
assert_int_equal(return_value,1);
remove_item(test_buffer);
return_value = size(test_buffer);
assert_int_equal(return_value,0);
data = -1000;
add(test_buffer,&data);
return_value = size(test_buffer);
assert_int_equal(return_value,1);
data = 500;
add(test_buffer,&data);
return_value = size(test_buffer);
assert_int_equal(return_value,2);
data = 60000;
add(test_buffer,&data);
return_value = size(test_buffer);
assert_int_equal(return_value,3);
data = 50;
add(test_buffer,&data);
return_value = size(test_buffer);
assert_int_equal(return_value,4);
data = 90;
add(test_buffer,&data);
return_value = size(test_buffer);
assert_int_equal(return_value,5);
data = 100;
add(test_buffer,&data);
return_value = size(test_buffer);
assert_int_equal(return_value,5);
destroy(test_buffer);
test_buffer = NULL;
printf("***5. size test passed*****\n");
}



int main(int argc,char **argv)
{
const struct CMUnitTest test[] = {
       cmocka_unit_test(test_add_item),
       cmocka_unit_test(test_remove_item),
       cmocka_unit_test(test_is_buffer_full),
       cmocka_unit_test(test_is_buffer_empty),
       cmocka_unit_test(test_size)
       };

return cmocka_run_group_tests(test,NULL,NULL);
}

