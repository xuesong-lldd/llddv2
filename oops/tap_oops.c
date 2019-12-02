#include <linux/module.h>
#include <linux/kernel.h>

static int demodev_init(void)
{
	printk("+%s\n", __func__);
	//*((int *)0x00) = 0xdeadbeef;
	panic("intension oops");
	return 0;
}

static void demodev_exit(void)
{
	printk("+%s\n", __func__);
	return;
}

module_init(demodev_init);
module_exit(demodev_exit);

MODULE_LICENSE("GPL");

