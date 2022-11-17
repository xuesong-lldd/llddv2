#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <linux/version.h>
#include <uapi/linux/sched/types.h>

void smp_func_on_cpu(void *p)
{
	pr_info("%s running on cpu#%d\n", __func__, smp_processor_id());
}

static int smp_call_init(void)
{
	int ret = 0;
	pr_info("++%s running on cpu#%d++\n", __func__, smp_processor_id());
	smp_call_function_single(3, smp_func_on_cpu, NULL, true);

	return ret;
}

static void smp_call_exit(void)
{
	printk("--%s--\n", __func__);

	return;
}

module_init(smp_call_init);
module_exit(smp_call_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
