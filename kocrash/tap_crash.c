#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

static void trigger_bug(void)
{
	int *p = (int *)0x123456;
	*p = 0xdeadbeef;
}

static void trigger_panic(void)
{
	rcu_read_unlock();
	panic("trigger panic in ko");
}

static int crash_init(void)
{
	printk("+%s\n", __func__);
	//trigger_bug();
	trigger_panic();
	return 0;
}

static void crash_exit(void)
{
	printk("+%s\n", __func__);
	return;
}

module_init(crash_init);
module_exit(crash_exit);

MODULE_LICENSE("GPL");

