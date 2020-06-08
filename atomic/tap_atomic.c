#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/sched/task.h>

static atomic_t g_lck_val = ATOMIC_INIT(1);

struct task_struct *pt = &init_task;
static int tap_atomic_init(void)
{
	int old;
	
	printk("++%s++, pid of init_task = %d\n", __func__, pt->pid);

	/* 
	 * atomic_cmpxchg(ptr, compared_var, new)
	 * atomic_cmpxchg will compare the value in [ptr] with the 'compared_var':
	 * if *ptr == compared_var, then *ptr = new, return the original val of ptr,
	 * if *ptr != compared_var, then do nothing, return the original val of ptr
	 */	
	old = atomic_cmpxchg(&g_lck_val, 1, 5);
	printk("old = %d, new_lck_val = %d\n", old, atomic_read(&g_lck_val));
	
	old = atomic_cmpxchg(&g_lck_val, 5, 3);
	printk("old = %d, new_lck_val = %d\n", old, atomic_read(&g_lck_val));
	
	old = atomic_cmpxchg(&g_lck_val, 4, 6);
	printk("old = %d, new_lck_val = %d\n", old, atomic_read(&g_lck_val));

	return 0;
}

static void tap_atomic_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(tap_atomic_init);
module_exit(tap_atomic_exit);

MODULE_LICENSE("GPL");

