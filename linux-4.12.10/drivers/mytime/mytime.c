#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>

/**********************************************************************
*@Filename:mytime.c
*
*@Description:Implemented a module which is triggered every 500ms
*
*@Author:Mounika Reddy Edula
*@Date:09/19/2017
*@compiler:GCC
*@Debugger:GDB
*@kernel:4.12.10
**********************************************************************/
//parameters for modinfo
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mounika Reddy Edula");
MODULE_DESCRIPTION("Trigger a timer every 500ms");
MODULE_VERSION("0.1");

//static as the count value should be stored
static struct timer_list my_timer;
static int32_t count;

//callback when timer expires
void my_timer_callback(unsigned long data)
{
count++;
printk("Timer is fired for %d\n",count);
my_timer.expires = jiffies+msecs_to_jiffies(500);
add_timer(&my_timer);
}

//The module is started with init function
static int __init timer_start(void)
{
printk(KERN_INFO "Loading timer module ....\n");
printk(KERN_INFO "Just a timer\n");
setup_timer(&my_timer,my_timer_callback,0);
mod_timer(&my_timer, jiffies+msecs_to_jiffies(200)); 
return 0;
}

//The module is exited with __exit function
static void __exit timer_end(void)
{
del_timer(&my_timer);
printk(KERN_INFO "Goodbye timer\n");
}

module_init(timer_start);
module_exit(timer_end);
