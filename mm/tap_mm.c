#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/sched/task.h>


static int tap_atomic_init(void)
{
	unsigned long *pv, *pp;
	printk("++%s++\n", __func__);
	printk("page_offset_base = 0x%lx\n", page_offset_base);	
	pv = kzalloc(sizeof(*pv), GFP_KERNEL);
	printk("pv = 0x%px\n", pv);
	*pv = 0xdeadbeaf;
	pp = (unsigned long *)((unsigned long)pv - page_offset_base);
	printk("pp = 0x%px, *pp = 0x%lx\n", pp, *pp);

	return 0;
}

static void tap_atomic_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(tap_atomic_init);
module_exit(tap_atomic_exit);

MODULE_LICENSE("GPL");

