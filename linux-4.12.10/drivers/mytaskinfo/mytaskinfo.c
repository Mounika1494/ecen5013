#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/sched/signal.h>

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
MODULE_DESCRIPTION("Traverse from current to parent");
MODULE_VERSION("0.1");

struct task_struct *task;
struct list_head *list;
struct task_struct *my_current;
static int noofchildren = 0 ;

//The module enter with __init function
static int __init tasklist_start(void)
{
printk(KERN_INFO "Loading mytask info module ....\n");

rcu_read_lock();
for(task = current;task!= &init_task;task=task->parent)
{

  noofchildren = 1;
  list_for_each(list,&task->children)
  {
  noofchildren++;
  }
  printk(KERN_INFO "PROCESS NAME: %s PID: %d STATE: %lu has %d children\n",task->comm,task->pid,task->state,noofchildren);

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
