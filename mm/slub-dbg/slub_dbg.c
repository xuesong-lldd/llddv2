#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

#define ALLOC_SIZE  (8)

unsigned char *p;
static int slub_dbg_init(void)
{
	int i = 0;
	p = kmalloc(ALLOC_SIZE, GFP_KERNEL);
	
	for (i = 0; i < ALLOC_SIZE; i++) {
		printk("p[%2d] = 0x%x\n", i, p[i]);
	}

	/* red zone check */
	for (i = ALLOC_SIZE; i < ALLOC_SIZE + 64; i++){
		printk("p[%2d] = 0x%x\n", i, p[i]);
	}

	kfree(p);

	for (i = 0; i < ALLOC_SIZE; i++) {
		printk("After freed:p[%-2d] = 0x%x\n", i, p[i]);
	}
	return 0;
}

static void slub_dbg_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(slub_dbg_init);
module_exit(slub_dbg_exit);

MODULE_LICENSE("GPL");

