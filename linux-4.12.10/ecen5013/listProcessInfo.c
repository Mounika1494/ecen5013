#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>

#include "processInfo.h"

asmlinkage long sys_listProcessInfo(void) 
{

struct task_struct *process;

for_each_process(process)
{

printk(
    "Process: %s\n \
     PID_Number: %ld\n \
     Process State: %ld\n \
     Priority: %ld\n \
     RT_Priority: %ld\n \
     Static Priority: %ld\n \
     Normal Priority: %ld\n", \
     process->comm,\
      (long)task_pid_nr(process),\
      (long)process->state,\
      (long)process->prio,\
      (long)process->rt_priority,\
      (long)process->static_prio,\
      (long)process->normal_prio\
);

if(process->parent)
printk(
    "Parent process: %s, \
     PID_Number: %ld",\
     process->parent->comm,\
     (long)task_pid_nr(process->parent) \
 );

printk("\n\n");
}
return 0;
} 

