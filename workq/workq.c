#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/slab.h>
#include <linux/preempt.h>
#include <linux/smp.h>

typedef struct {
	struct workqueue_struct *wq;
	struct work_struct work;
} wq_container_t;

wq_container_t *g_wq_container;

void demo_work_func(struct work_struct *work)
{
	pr_info("in the demo_work_func...\n");
}

static int workq_init(void)
{
	int cpu;
	pr_info("++%s++\n", __func__);
	g_wq_container = kzalloc(sizeof(*g_wq_container), GFP_KERNEL);
	g_wq_container->wq = create_workqueue("demo_wq");

	INIT_WORK(&g_wq_container->work, demo_work_func);
	pr_info("preempt_count = %d\n", preempt_count());
	cpu = get_cpu();
	pr_info("preempt_count = %d, cpu = %d\n", preempt_count(), cpu);
	queue_work_on(cpu, g_wq_container->wq, &g_wq_container->work);
	put_cpu();
	pr_info("preempt_count = %d\n", preempt_count());
	return 0;
}

static void workq_exit(void)
{
	printk("--%s--\n", __func__);

	cancel_work_sync(&g_wq_container->work);
	destroy_workqueue(g_wq_container->wq);
	kfree(g_wq_container);

	return;
}

module_init(workq_init);
module_exit(workq_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
