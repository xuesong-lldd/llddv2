#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/mm.h>

#define ALLOC_SIZE  (8)

unsigned char *p;
static int kmemleak_demo_init(void)
{
	p = kmalloc(ALLOC_SIZE, GFP_KERNEL);
	if (p) 
		printk("kmalloc-8 return 0x%px\n", p);
	else
		printk("kmalloc-8 failed\n");
	
	return 0;
}

static void kmemleak_demo_exit(void)
{
	printk("--%s--\n", __func__);
	/* don't free the p */
	return;
}

module_init(kmemleak_demo_init);
module_exit(kmemleak_demo_exit);

MODULE_LICENSE("GPL");

