#include <linux/module.h>
#include <linux/kernel.h>

static int hello_init(void)
{
	printk("++%s++\n", __func__);
	printk("hello world!\n");
	return 0;
}

static void hello_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");

