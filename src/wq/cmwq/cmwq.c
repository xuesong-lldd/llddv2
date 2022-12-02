/*
 * This code is to demo the CMWQ.
 * With scheduler hook, the sleep of work0->func will wakeup other worker to handle
 * work instead of waiting for worker0.
 * The output on x86_64 with max_active = 3 as:
 *
 * [73736.744675] 1 jiffies = 4(ms)
 * [73736.744713] w0:jiffies0@cpu#1 = 4313326438
 * [73736.750092] w0:jiffies0@cpu#1 = 4313326440
 * [73736.750105] w1:jiffies0@cpu#1 = 4313326440
 * [73736.758093] w1:jiffies0@cpu#1 = 4313326442
 * [73736.758102] w2:jiffies0@cpu#1 = 4313326442
 * [73736.766154] w2:jiffies0@cpu#1 = 4313326444
 * [73736.770209] w0:jiffies1@cpu#1 = 4313326445
 * [73736.778098] w1:jiffies1@cpu#1 = 4313326446
 * [73736.778155] w0:jiffies1@cpu#1 = 4313326447
 * [73736.786204] w2:jiffies1@cpu#1 = 4313326449
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

struct workqueue_struct *wq0, *wq1;

#define MAX_ACTIVE_WORKS	(3)

/* work->func */
void work0_func(struct work_struct *work)
{
	int cpu = smp_processor_id();
	unsigned long timeout;

	pr_info("w0:jiffies0@cpu#%d = %lu\n", cpu, jiffies);
	timeout = jiffies + msecs_to_jiffies(5);
	/* burns cpu for 5ms */
	while(time_before(jiffies, timeout));
	pr_info("w0:jiffies0@cpu#%d = %lu\n", cpu, jiffies);
	/* sleep for 10ms */
	schedule_timeout_interruptible(msecs_to_jiffies(10));
	pr_info("w0:jiffies1@cpu#%d = %lu\n", cpu, jiffies);
	/* burns cpu for 5ms again */
	timeout = jiffies + msecs_to_jiffies(5);
	while(time_before(jiffies, timeout));
	pr_info("w0:jiffies1@cpu#%d = %lu\n", cpu, jiffies);
}

/* work->func */
void work1_func(struct work_struct *work)
{
	int cpu = smp_processor_id();
	unsigned long timeout;

	pr_info("w1:jiffies0@cpu#%d = %lu\n", cpu, jiffies);
	timeout = jiffies + msecs_to_jiffies(5);
	/* burns cpu for 5ms */
	while(time_before(jiffies, timeout));
	pr_info("w1:jiffies0@cpu#%d = %lu\n", cpu, jiffies);
	/* sleep for 10ms */
	schedule_timeout_interruptible(msecs_to_jiffies(10));
	pr_info("w1:jiffies1@cpu#%d = %lu\n", cpu, jiffies);
}

/* work->func */
void work2_func(struct work_struct *work)
{
	int cpu = smp_processor_id();
	unsigned long timeout;

	pr_info("w2:jiffies0@cpu#%d = %lu\n", cpu, jiffies);
	timeout = jiffies + msecs_to_jiffies(5);
	/* burns cpu for 5ms */
	while(time_before(jiffies, timeout));
	pr_info("w2:jiffies0@cpu#%d = %lu\n", cpu, jiffies);
	/* sleep for 10ms */
	schedule_timeout_interruptible(msecs_to_jiffies(10));
	pr_info("w2:jiffies1@cpu#%d = %lu\n", cpu, jiffies);
}

static DECLARE_WORK(w0, work0_func);
static DECLARE_WORK(w1, work1_func);
static DECLARE_WORK(w2, work2_func);

static int cmwq_init(void)
{
	pr_info("+%s+\n", __func__);
	pr_info("1 jiffies = %u(ms)\n", jiffies_to_msecs(1));
	/* to trigger the init_pwq(...) */
	wq0 = alloc_workqueue("percpu_wq0", 0, MAX_ACTIVE_WORKS);
	wq1 = alloc_workqueue("percpu_wq1", 0, 0);
	if (!wq0 || !wq1) {
		pr_err("alloc_workqueue failed\n");
		return -1;
	}

	queue_work_on(1, wq0, &w0);
	queue_work_on(1, wq0, &w1);
	queue_work_on(1, wq0, &w2);

	return 0;
}

static void cmwq_exit(void)
{
	pr_info("+%s+\n", __func__);

	destroy_workqueue(wq1);
	destroy_workqueue(wq0);

}

module_init(cmwq_init);
module_exit(cmwq_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
