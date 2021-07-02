#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <uapi/linux/sched/types.h>

/*
 * In this demo, we create 2 kthreads, one is normal, another is rt-fifo. Acccording
 * to the scheduling policy, the rt kthread will always run on cpu until it exits,
 * a 3s delay is added to make this more easier to be observed.
 * A different output will get if we comment out the sched_set_fifo(p1) in the code... 
 */

/* normal kthread func */
static int normal_kthread_func(void *data)
{	
	u64 count = 0;
	unsigned long timeout = jiffies + msecs_to_jiffies(5);
	unsigned int policy = current->policy;
	pr_info("+%s+: sched_policy = %u@cpu%d\n", __func__, policy, smp_processor_id());
	
	while(time_before(jiffies, timeout))
		count++; 
	pr_info("normal count = %llu\n", count);
	
	return 0;
}
/* rt kthread func */
static int fifo_kthread_func(void *data)
{

	u64 count = 0;
	unsigned long timeout = jiffies + msecs_to_jiffies(3000);
	unsigned int policy = current->policy;
	pr_info("+%s+: sched_policy = %u@cpu%d\n", __func__, policy, smp_processor_id());
	
	while(time_before(jiffies, timeout))
		count++;
	pr_info("fifo count = %llu\n", count);
	
	return 0;
}
/* this function has been a public GPL exported function in newer kernel version */
static void sched_set_fifo(struct task_struct *p)
{
	struct sched_param sp = { .sched_priority = MAX_RT_PRIO / 2 };
	WARN_ON_ONCE(sched_setscheduler_nocheck(p, SCHED_FIFO, &sp) != 0);
}

static int rt_demo_init(void)
{
	int ret = 0;
	struct task_struct *p0, *p1;
	printk("++%s++\n", __func__);
	p0 = kthread_create(normal_kthread_func, NULL, "normal_kthead");
	if (IS_ERR(p0)) {
		ret = PTR_ERR(p0);
		pr_err("normal kthread_create failed\n");
		return ret;
	}
	/* bind the new kthread to the same processor */	
	kthread_bind(p0, smp_processor_id());
	p1 = kthread_create(fifo_kthread_func, NULL, "fifo_kthead");
	if (IS_ERR(p1)) {
		ret = PTR_ERR(p1);
		pr_err("fifo kthread_create failed\n");
		return ret;
	}
	/* bind the same processor avoid to dispatch it to a different cpu */
	kthread_bind(p1, smp_processor_id());
	sched_set_fifo(p1);
	wake_up_process(p0);
	/* delay to make normal kthread more graceful to enqueue the rq */
	mdelay(1);
	wake_up_process(p1);

	return ret;
}

static void rt_demo_exit(void)
{
	printk("--%s--\n", __func__);

	return;
}

module_init(rt_demo_init);
module_exit(rt_demo_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
