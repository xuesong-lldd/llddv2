/*
 * Demo code for the cancel_work(...) and cancel_work_sync(...)
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/workqueue.h>

enum {
	WORK_IS_EXECUTING,
	WORK_IS_COMPLETED,
	WORK_IS_SLEEPING
};

volatile unsigned long g_work_state;
struct workqueue_struct *wq0;

#define MAX_ACTIVE_WORKS	(3)

static void work0_func(struct work_struct *work);
static void work1_func(struct work_struct *work);
static void work2_func(struct work_struct *work);
static void work3_func(struct work_struct *work);

static DECLARE_WORK(w0, work0_func);
static DECLARE_WORK(w1, work1_func);
static DECLARE_WORK(w2, work2_func);
static DECLARE_WORK(w3, work3_func);

/* work->func */
static void work0_func(struct work_struct *work)
{
	int cpu = raw_smp_processor_id();
	unsigned long timeout = jiffies + msecs_to_jiffies(3000);

	set_bit(WORK_IS_EXECUTING, &g_work_state);
	pr_info("+%s scheduled@cpu#%d, will burn cpu for 3s\n", __func__, cpu);
	while(time_before(jiffies, timeout));
	pr_info("+%s execution completes@cpu#%d\n", __func__, cpu);
}

/* work->func */
static void work1_func(struct work_struct *work)
{
	int cpu = raw_smp_processor_id();
	pr_info("+%s scheduled@cpu#%d\n", __func__, cpu);
}

/* work->func */
static void work2_func(struct work_struct *work)
{
	int cpu = raw_smp_processor_id();
	pr_info("+%s scheduled@cpu#%d\n", __func__, cpu);
	set_bit(WORK_IS_COMPLETED, &g_work_state);
}

/* work->func */
static void work3_func(struct work_struct *work)
{
	int cpu = raw_smp_processor_id();
	pr_info("+%s scheduled@cpu#%d\n", __func__, cpu);
	set_bit(WORK_IS_SLEEPING, &g_work_state);
	pr_info("+%s begin to sleep 3s\n", __func__);
	schedule_timeout_interruptible(msecs_to_jiffies(3000));
	pr_info("+%s sleep completes\n", __func__);
}

static int cancel_init(void)
{
	bool ret;

	pr_info("+%s+\n", __func__);

	wq0 = alloc_workqueue("percpu_wq0", 0, MAX_ACTIVE_WORKS);
	if (!wq0) {
		pr_err("alloc_workqueue failed\n");
		return -1;
	}

	ret = cancel_work(&w1);
	pr_info("cancel a non-queueed work_1: %s\n", ret ? "true" : "false");

	queue_work_on(1, wq0, &w0);
	/* wait for the work_0 be scheduled */
	while (!test_bit(WORK_IS_EXECUTING, &g_work_state));
	pr_info("Begin to cancel work_0...\n");
	ret = cancel_work(&w0);
	pr_info("cancel an executing work_0: %s\n", ret ? "true" : "false");

	queue_work_on(1, wq0, &w2);
	/* wait for the work_2's execution is completed */
	while (!test_bit(WORK_IS_COMPLETED, &g_work_state));
	pr_info("Begin to cancel a completed work_2...\n");
	ret = cancel_work(&w2);
	pr_info("cancel a completed work_2: %s\n", ret ? "true" : "false");

	/* cancel_work_sync a 3s sleeping work */
	queue_work_on(1, wq0, &w3);
	while (!test_bit(WORK_IS_SLEEPING, &g_work_state));
	pr_info("Begin to sync cancel a 3s sleeping work_3...\n");
	ret = cancel_work_sync(&w3);
	pr_info("sync cancel a sleeping work_3: %s\n", ret ? "true" : "false");

	return 0;
}

static void cancel_exit(void)
{
	pr_info("+%s+\n", __func__);

	destroy_workqueue(wq0);
}

module_init(cancel_init);
module_exit(cancel_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
