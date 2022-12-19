/*
 * WQ_CPU_INTENSIVE demo code. Usage:
 * # insmod cpuintensive.ko is_cpu_intensive = [0/1].
 * The output with 'is_cpu_intensive=0':
 * [424247.512423] +cpuintensive_init+
 * [424247.512445] +queue_work_on wq0 w/o WQ_CPU_INTENSIVE
 * [424247.512450] -queue_work_on wq0 w/o WQ_CPU_INTENSIVE
 * [424247.512468] +work_cpuintensive_func scheduled@cpu#1, will burn cpu for 3s
 * [424250.509767] -work_cpuintensive_func: completed
 * [424250.509770] +work_normal_func: scheduled <-- normal work->func can be scheduled
 * only after the cpu-intensive work->func finished
 *
 * The output with 'is_cpu_intensive=1':
 * [424480.298210] +cpuintensive_init+
 * [424480.298232] +queue_work_on wq1 w/ WQ_CPU_INTENSIVE
 * [424480.298237] -queue_work_on wq1 w/ WQ_CPU_INTENSIVE
 * [424480.298258] +work_cpuintensive_func scheduled@cpu#1, will burn cpu for 3s
 * [424480.311117] +work_normal_func: scheduled <-- normal work->func can be scheduled 
 * even if the cpu-intensive work->func is running
 * [424483.294992] -work_cpuintensive_func: completed
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/workqueue.h>

static bool is_cpu_intensive;
module_param(is_cpu_intensive, bool, 0644);

struct workqueue_struct *wq0, *wq1;

#define MAX_ACTIVE_WORKS	(3)

static void work_cpuintensive_func(struct work_struct *work);
static void work_normal_func(struct work_struct *work);

static DECLARE_WORK(w0, work_cpuintensive_func);
static DECLARE_WORK(w1, work_normal_func);

static void work_cpuintensive_func(struct work_struct *work)
{
	int cpu = raw_smp_processor_id();
	unsigned long timeout = jiffies + msecs_to_jiffies(3000);

	pr_info("+%s scheduled@cpu#%d, will burn cpu for 3s\n", __func__, cpu);
	while(time_before(jiffies, timeout));
	pr_info("-%s: completed\n", __func__);
}

static void work_normal_func(struct work_struct *work)
{
	pr_info("+%s: scheduled\n", __func__);
}

static int cpuintensive_init(void)
{
	pr_info("+%s+\n", __func__);

	wq0 = alloc_workqueue("percpu_wq0", 0, MAX_ACTIVE_WORKS);
	wq1 = alloc_workqueue("percpu_wq1", WQ_CPU_INTENSIVE, MAX_ACTIVE_WORKS);
	if (!wq0 || !wq1) {
		pr_err("alloc_workqueue failed\n");
		return -1;
	}

	if (!is_cpu_intensive) {
		pr_info("+queue_work_on wq0 w/o WQ_CPU_INTENSIVE\n");
		queue_work_on(1, wq0, &w0);
		queue_work_on(1, wq0, &w1);
		pr_info("-queue_work_on wq0 w/o WQ_CPU_INTENSIVE\n");
	} else {
		pr_info("+queue_work_on wq1 w/ WQ_CPU_INTENSIVE\n");
		queue_work_on(1, wq1, &w0);
		queue_work_on(1, wq1, &w1);
		pr_info("-queue_work_on wq1 w/ WQ_CPU_INTENSIVE\n");
	}

	return 0;
}

static void cpuintensive_exit(void)
{
	pr_info("+%s+\n", __func__);

	destroy_workqueue(wq1);
	destroy_workqueue(wq0);
}

module_init(cpuintensive_init);
module_exit(cpuintensive_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
