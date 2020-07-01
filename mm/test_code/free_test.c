#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

static char *buf;

/* multiple free the same pointer */
void create_dfree_error(void)
{
	buf = kmalloc(32, GFP_KERNEL);
	if(buf) {
		memset(buf, 0x55, 32);
		kfree(buf);
		printk("dfree: object already freed");
		kfree(buf);
	}
}

static int __init dfree_test_init(void)
{
	printk("++%s++\n", __func__);
	create_dfree_error();
	return 0;
}

static void __exit dfree_test_exit(void)
{
	printk("++%s++\n", __func__);
	return;
}

MODULE_LICENSE("GPL");
module_init(dfree_test_init);
module_exit(dfree_test_exit);
