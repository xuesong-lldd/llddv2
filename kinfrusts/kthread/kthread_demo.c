#include <linux/module.h>
#include <linux/kthread.h>

struct kthread_para {
	int a;
	int cpu_idx;
};

struct task_struct *g_kthread[NR_CPUS] = {0};

/* kthread func */
static int my_kthread_func(void *data)
{
	struct kthread_para *p = (struct kthread_para *)data;
	while (1) {
		if (kthread_should_stop())
			break;
		pr_info("%s: a = %d, cpu = %d\n", __func__, p->a, p->cpu_idx);
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	}
	pr_info("%s will exit...\n", __func__);
	return p->a;
}

struct kthread_para kp[NR_CPUS];

struct task_struct *t;
static int kthread_demo_init(void)
{
	int i, ret = 0;
	printk("++%s++\n", __func__);

	for_each_online_cpu(i) {
		kp[i].a = 10 * i;
		kp[i].cpu_idx = i;
		/* Don't pass the address of a stack var to the kthread_creat(...) */
		g_kthread[i] = kthread_create(my_kthread_func,
			&kp[i], "mykthead@cpu%d", i);
		if (IS_ERR(g_kthread[i])) {
			ret = PTR_ERR(g_kthread[i]);
			pr_err("kthread_create %d failed\n", i);
			goto tear_down;
		}	
		wake_up_process(g_kthread[i]);
	} 
tear_down:
	/* just a demo, so we don't handle the tear down case... */
	return ret;
}

static void kthread_demo_exit(void)
{
	int i, ret;
	printk("--%s--\n", __func__);
	
	for_each_online_cpu(i) {
		if (g_kthread[i]) {
			ret = kthread_stop(g_kthread[i]);
			pr_info("kthread[%d] return %d\n", i, ret);
			g_kthread[i] = NULL;
		}
	}

	return;
}

module_init(kthread_demo_init);
module_exit(kthread_demo_exit);

MODULE_LICENSE("GPL");

