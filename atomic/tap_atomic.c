#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/slab.h>

static atomic_t g_lck_val = ATOMIC_INIT(1);

static int tap_atomic_init(void)
{
	int old;
	void *p;
	unsigned long pa;
	printk("++%s++\n", __func__);
	p = vmalloc(64);
	pa = __pa_symbol(alloc_workqueue);
	printk("p = %p, pa = 0x%lx\n", p, pa);
	old = atomic_cmpxchg(&g_lck_val, 1, 5);
	printk("old = %d, new_lck_val = %d\n", old, atomic_read(&g_lck_val));
	old = atomic_cmpxchg(&g_lck_val, 5, 3);
	printk("old = %d, new_lck_val = %d\n", old, atomic_read(&g_lck_val));
	vfree(p);		
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

