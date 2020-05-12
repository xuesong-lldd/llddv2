#include <linux/module.h>
#include <linux/kernel.h>

static int black_demo_init(void)
{
	printk("++%s++\n", __func__);

	return 0;
}

static void black_demo_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(black_demo_init);
module_exit(black_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");

