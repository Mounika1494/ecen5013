#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/sched/signal.h>

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
MODULE_DESCRIPTION("Display all the tasks present");
MODULE_VERSION("0.1");
struct task_struct *task;
struct list_head *list;
static int noofchildren = 0 ;


int no_of_children(struct task_struct *present)
{
noofchildren = 0; 
list_for_each(list, &present->children)
{
noofchildren++;
}
return noofchildren;
}

static int __init tasklist_start(void)
{
printk(KERN_INFO "Loading mytask info module ....\n");
printk(KERN_INFO "All tasks\n");

rcu_read_lock();
for_each_process(task)
{
printk("task %s whose pid is %d whose state is %lu no_of_children are %d\n",task->comm,task->pid,task->state,no_of_children(task));
}
rcu_read_unlock();
return 0;
}

//The module is exited with __exit function
static void __exit tasklist_end(void)
{
printk(KERN_INFO "GoodBye\n");
}

module_init(tasklist_start);
module_exit(tasklist_end);
