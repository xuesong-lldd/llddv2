#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <uapi/linux/sched/types.h>

/*
 * Run this demo in the system with PREEMPT-RT kconfig enabled.
 * We create two kthreads in this demo: one is normal, another is realtime(rt-fifo).
 * We make the normal kthread to run first, it will output the pr_info(...) message first,
 * then it will enter a 500ms-duration busy loop which creates a preemption window for the
 * the rt-kthread, the normal kthread will be preempted once the rt-fifo is ready to run.
 *
 * On an PREEMPT-RT enabled RT-Linux system, an example output like below:
 * ...
 * [501967.308570] +normal_kthread_func+: sched_policy = 0@cpu0
 * [501967.315093] +fifo_kthread_func+: sched_policy = 1@cpu0
 * [501967.415067] fifo count = 200446012
 * [501967.807062] normal count = 794840515
 *
 * For the PREEMPT-RT kconfig disabled system, since the kernel code path can't be preempted,
 * so the demo behavior is not predictable because normal kthread is the kernel code
 */

#define RT_CORE_0	0

/* normal kthread func */
static int normal_kthread_func(void *data)
{	
	u64 count = 0;
	unsigned long timeout = jiffies + msecs_to_jiffies(500);
	unsigned int policy = current->policy;
	pr_info("+%s+: sched_policy = %u@cpu%d\n", __func__, policy, smp_processor_id());
	/* add the busy wait to create a preempt window for the rt-kthread... */
	while(time_before(jiffies, timeout))
		count++; 
	pr_info("normal count = %llu\n", count);
	
	return 0;
}
/* rt kthread func */
static int fifo_kthread_func(void *data)
{

	u64 count = 0;
	unsigned long timeout = jiffies + msecs_to_jiffies(100);
	unsigned int policy = current->policy;
	pr_info("+%s+: sched_policy = %u@cpu%d\n", __func__, policy, smp_processor_id());
	
	while(time_before(jiffies, timeout))
		count++;
	pr_info("fifo count = %llu\n", count);
	
	return 0;
}

static int rt_demo_init(void)
{
	int ret = 0;
	struct task_struct *p0, *p1;
	u64 count = 0;
	unsigned long timeout = jiffies + msecs_to_jiffies(5);

	printk("++%s++\n", __func__);
	p0 = kthread_create(normal_kthread_func, NULL, "normal_kthead");
	if (IS_ERR(p0)) {
		ret = PTR_ERR(p0);
		pr_err("normal kthread_create failed\n");
		return ret;
	}
	/* bind the new kthread to the same processor */	
	kthread_bind(p0, RT_CORE_0);
	p1 = kthread_create(fifo_kthread_func, NULL, "fifo_kthead");
	if (IS_ERR(p1)) {
		ret = PTR_ERR(p1);
		pr_err("fifo kthread_create failed\n");
		return ret;
	}
	/* bind the same processor avoid to dispatch it to a different cpu */
	kthread_bind(p1, RT_CORE_0);
	/* set the sched policy as RT-FIFO and sched priority as 50 for the p1 */
	sched_set_fifo(p1);

	/* wakeup the normal thread first... */
	wake_up_process(p0);
	/* busy wait 5ms to make the normal has the chance to execute first... */
	while(time_before(jiffies, timeout))
		count++;
	/* wakeup the rt-kthread, which will preempt the normal kthread in the PREEMPT-RT system */
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
