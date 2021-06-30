#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/slab.h>

struct completion *g_done;

/* kthread func */
static int my_kthread_func(void *data)
{
	pr_info("+%s+\n", __func__);
	pr_info("before mdelay\n");
	mdelay(10);
	pr_info("after mdelay\n");
	complete(g_done);
	return 0;
}

static int comp_demo_init(void)
{
	int ret = 0;
	struct task_struct *p;
	printk("++%s++\n", __func__);
	g_done = kmalloc(sizeof(*g_done), GFP_KERNEL);
	if (!g_done) {
		pr_err("kmalloc() failed\n");
		return -1;
	}
	init_completion(g_done);
	/* Don't pass the address of a stack var to the kthread_creat(...) */
	p = kthread_run(my_kthread_func, NULL, "mykthead");
	if (IS_ERR(p)) {
		ret = PTR_ERR(p);
		pr_err("kthread_create failed\n");
		return -1;
	}	
	
	/* now let's sync the kthread func and the current via completion obj */
	pr_info("%s is waiting for the kthread func to complete...\n", current->comm);
	wait_for_completion(g_done);
	pr_info("Now we can go because the kthread func has done\n");

	/* just a demo, so we don't handle the tear down case... */
	return ret;
}

static void comp_demo_exit(void)
{
	printk("--%s--\n", __func__);
	if (g_done)
		kfree(g_done);

	return;
}

module_init(comp_demo_init);
module_exit(comp_demo_exit);

MODULE_LICENSE("GPL");

