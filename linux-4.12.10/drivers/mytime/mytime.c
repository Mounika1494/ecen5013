#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mounika Reddy Edula");
MODULE_DESCRIPTION("Trigger a timer every 500ms");
MODULE_VERSION("0.1");

static struct timer_list my_timer;
static int count;
void my_timer_callback(unsigned long data)
{
count++;
printk("Timer is fired for %d\n",count);
my_timer.expires = jiffies+msecs_to_jiffies(500);
add_timer(&my_timer);
}

static int __init timer_start(void)
{
printk(KERN_INFO "Loading timer module ....\n");
printk(KERN_INFO "Just a timer\n");
setup_timer(&my_timer,my_timer_callback,0);
mod_timer(&my_timer, jiffies+msecs_to_jiffies(200)); 
return 0;
}

static void __exit timer_end(void)
{
del_timer(&my_timer);
printk(KERN_INFO "Goodbye timer\n");
}

module_init(timer_start);
module_exit(timer_end);
