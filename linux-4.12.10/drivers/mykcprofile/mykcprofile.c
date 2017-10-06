#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/kthread.h>

/**********************************************************************
*@Filename:mytaskinfo.c
*
*@Description:Implemented a module which traverses from current to parent a
*              and prints the name and no of children
*
*@Author:Mounika Reddy Edula
*@Date:10/05/2017
*@compiler:GCC
*@Debugger:GDB
*@kernel:4.12.10
**********************************************************************/

//parameters for modinfo
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mounika Reddy Edula");
MODULE_DESCRIPTION("Kernel Create Profile");

struct task_struct *task_kthread;
int no_work(void *args)
{
printk("no work\n");
return 1;
}

//The module enter with __init function
static int __init profile_start(void)
{
unsigned long create_start,create_end,create_time;

printk(KERN_INFO "Loading kthreadcreate profile module ....\n");

//start time
create_start = get_jiffies_64();
task_kthread = kthread_create(no_work,NULL,"kthread");
if(IS_ERR(task_kthread))
{
 printk(KERN_INFO"Error creating kthread.Exiting the module\n");
 return 1;
}
create_end = get_jiffies_64();
create_time = create_end -create_start;
printk(KERN_INFO "time it took to do kthread create is %lu\n",create_time);
return 0;
}

//The module is exited with __exit function
static void __exit profile_end(void)
{
int ret = kthread_stop(task_kthread);
if(ret!= -EINTR)
printk(KERN_INFO "thread is stopped\n");
printk(KERN_INFO "GoodBye\n");
}

module_init(profile_start);
module_exit(profile_end);
