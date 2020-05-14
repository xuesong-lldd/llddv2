#include <linux/module.h>
#include <linux/kernel.h>

void demofunc(int a, int b)
{
	printk("from the exported function: %d/%d\n", a, b);

	return;
}

EXPORT_SYMBOL_GPL(demofunc);

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
MODULE_INFO(intree, "Y");
