#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mounika Reddy Edula");
MODULE_DESCRIPTION("Test Module");
MODULE_VERSION("0.1");

static struct timer_list my_timer;
static int count;
void my_timer_callback(unsigned long data)
{
count++;
printk("timer is fired for %d\n",count);
my_timer.expires = jiffies+msecs_to_jiffies(200);
add_timer(&my_timer);
}

static int __init hello_start(void)
{
printk(KERN_INFO "Loading hello module ....\n");
printk(KERN_INFO "Hello World\n");
setup_timer(&my_timer,my_timer_callback,0);
mod_timer(&my_timer, jiffies+msecs_to_jiffies(200)); 
return 0;
}

static void __exit hello_end(void)
{
del_timer(&my_timer);
printk(KERN_INFO "Goodbye\n");
}

module_init(hello_start);
module_exit(hello_end);
