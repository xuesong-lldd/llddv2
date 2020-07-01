#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

static char *buf;

/* left oob issue */
void create_loob_error(void)
{
	buf = kmalloc(32, GFP_KERNEL);
	if(buf) {
		buf[-1] = 0x55;
	}
}

static int __init loob_test_init(void)
{
	printk("++%s++\n", __func__);
	create_loob_error();
	return 0;
}

static void __exit loob_test_exit(void)
{
	printk("++%s++\n", __func__);
	/* trigger the left oob check */
	kfree(buf);
	return;
}

MODULE_LICENSE("GPL");
module_init(loob_test_init);
module_exit(loob_test_exit);
