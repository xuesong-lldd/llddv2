#include <linux/module.h>
#include <linux/kernel.h>

void hello_exported_function(void)
{
	printk("from the exported function\n");

	return;
}

EXPORT_SYMBOL_GPL(hello_exported_function);

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
