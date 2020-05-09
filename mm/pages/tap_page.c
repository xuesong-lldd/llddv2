#include <linux/module.h>
#include <linux/gfp.h>
#include <linux/mm.h>

struct page * pg_addr;
static int tap_page_init(void)
{
	printk("++%s++\n", __func__);
	
	pg_addr = alloc_pages(GFP_KERNEL|GFP_DMA, 4);
	if (!pg_addr) {
		printk("allocate pages failed\n");
		return -1;
	}

	return 0;
}

static void tap_page_exit(void)
{
	void *pg;
	printk("--%s--\n", __func__);
	pg = page_address(pg_addr);
	printk("pg = 0x%px\n", pg);
	/* teardown the resource allocated */
	free_pages((unsigned long)pg, 4);
	return;
}

module_init(tap_page_init);
module_exit(tap_page_exit);

MODULE_LICENSE("GPL");

