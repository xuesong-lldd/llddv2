/*
 * This kmod is used to demo the work->func will be reentrant if the same
 * work object be queued into two different wqs like below:
 *
 *     wq0 --> pwq1 --> pool_1 + work->func
 *     wq1 --> pwq2 --> pool_2 + work->func
 *
 * the same work obj will be queued into wq0 and wq1 respectively. When the
 * 2nd work queued, it will call get_work_pool(work) to get the pool attached by
 * the 1st work item attached, it's pool_1 (last_pool) in this case.
 * The pool attached by the 2nd work is pool_2 when it's queued, moreover, the
 * wq object for the worker who is executing the 1st work is different than the
 * 2nd one:
 *    worker = find_worker_executing_work(last_pool, work);
 *    worker->current_pwq->wq != wq;
 *
 * Thus the 2nd work->func will be executed in a different cpu than the 1st one,
 * the work->func reentrance will be observed if we design the work->func elaborately
 *
 * The output of the 'insmod reent.ko' on x86_64 as below:
 * [2871712.523598] +reent_init+
 * [2871712.523713] jiffies0@cpu#1 = 5012820282
 *                                   <-------- 2nd work->func reentrance begins
 * [2871713.520489] jiffies0@cpu#2 = 5012820532
 * [2871718.520467] jiffies1@cpu#1 = 5012821782
 * [2871718.520472] pool_id@cpu#1 = 2
 * [2871719.520470] jiffies1@cpu#2 = 5012822032
 * [2871719.520475] pool_id@cpu#2 = 4

 */

#include <linux/module.h>
#include <linux/kernel.h>

struct workqueue_struct *wq0, *wq1;
volatile bool flag = false;

/* work->func */
void my_work_func(struct work_struct *work)
{
	int pool_id;
	unsigned long data = atomic_long_read(&work->data);
	unsigned long timeout = jiffies + msecs_to_jiffies(6000);

	/* become true to make the 2nd work item can be queued */
	flag = true;

	pr_info("jiffies0@cpu#%d = %lu\n", smp_processor_id(), jiffies);

	/* ask the work->func run at least 6s to wait 2nd work->func be called */
	while(time_before(jiffies, timeout));
	pr_info("jiffies1@cpu#%d = %lu\n", smp_processor_id(), jiffies);

	pool_id = data >> WORK_OFFQ_POOL_SHIFT;
	pr_info("pool_id@cpu#%d = %d\n", smp_processor_id(), pool_id);
}

static DECLARE_WORK(my_work, my_work_func);

static int reent_init(void)
{
	unsigned long timeout;
	pr_info("+%s+\n", __func__);

	/* to trigger the init_pwq(...) */
	wq0 = alloc_workqueue("percpu_wq0", 0, 0);
	wq1 = alloc_workqueue("percpu_wq1", 0, 0);
	if (!wq0 || !wq1) {
		pr_err("alloc_workqueue failed\n");
		return -1;
	}

	queue_work_on(1, wq0, &my_work);

	/* wait until the 2nd can be queued */
	while (!flag);

	/* let the bullet flying for a while... */
	timeout = jiffies + msecs_to_jiffies(1000);
	while(time_before(jiffies, timeout));

	/* begin to queue the 2nd work item */
	queue_work_on(2, wq1, &my_work);

	return 0;
}

static void reent_exit(void)
{
	pr_info("+%s+\n", __func__);

	destroy_workqueue(wq1);
	destroy_workqueue(wq0);

}

module_init(reent_init);
module_exit(reent_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
