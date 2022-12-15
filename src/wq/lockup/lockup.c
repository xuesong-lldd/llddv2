/*
 * Demo workqueue stall detection. Only works on the kernel with
 * CONFIG_WQ_WATCHDOG configured
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/workqueue.h>

struct workqueue_struct *wq0;

#define MAX_ACTIVE_WORKS	(3)

static void work_lockup_func(struct work_struct *work);

static DECLARE_WORK(w, work_lockup_func);

static void work_lockup_func(struct work_struct *work)
{
	int cpu = raw_smp_processor_id();
	unsigned long timeout = jiffies + msecs_to_jiffies(60000);

	pr_info("+%s scheduled@cpu#%d, will burn cpu for 60s\n", __func__, cpu);
	while(time_before(jiffies, timeout));
	pr_info("-%s: completed\n", __func__);
}

static int lockup_init(void)
{
	pr_info("+%s+\n", __func__);

	wq0 = alloc_workqueue("percpu_wq0", 0, MAX_ACTIVE_WORKS);
	if (!wq0) {
		pr_err("alloc_workqueue failed\n");
		return -1;
	}

	pr_info("+queue_work_on\n");
	queue_work_on(1, wq0, &w);
	pr_info("-queue_work_on\n");

	return 0;
}

static void lockup_exit(void)
{
	pr_info("+%s+\n", __func__);

	destroy_workqueue(wq0);
}

module_init(lockup_init);
module_exit(lockup_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
