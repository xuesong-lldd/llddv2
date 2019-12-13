#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>

atomic_t g_flag = ATOMIC_INIT(0);
struct workqueue_struct *g_my_wq;
spinlock_t g_spinlck;

struct work_struct work_a;
void work_a_func(struct work_struct *work)
{
	printk("+%s\n", __func__);
	spin_lock(&g_spinlck);
	do {
		cpu_relax();	
	} while(!atomic_read(&g_flag));
	spin_unlock(&g_spinlck);
	printk("-%s\n", __func__);
}

struct work_struct work_b;
void work_b_func(struct work_struct *work)
{
	printk("+%s\n", __func__);
	spin_lock(&g_spinlck);
	atomic_cmpxchg(&g_flag, 0, 1);
	spin_unlock(&g_spinlck);
	printk("-%s\n", __func__);
}

static int demodev_init(void)
{
	printk("+%s\n", __func__);
	spin_lock_init(&g_spinlck);
	g_my_wq = alloc_workqueue("wq_softlockup_test", 0, 0);
	INIT_WORK(&work_a, work_a_func);
	INIT_WORK(&work_b, work_b_func);
	queue_work(g_my_wq, &work_a);
	queue_work(g_my_wq, &work_b);
	return 0;
}

static void demodev_exit(void)
{
	printk("+%s\n", __func__);
	destroy_workqueue(g_my_wq);
	return;
}

module_init(demodev_init);
module_exit(demodev_exit);

MODULE_LICENSE("GPL");

