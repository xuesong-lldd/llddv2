#include <linux/module.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#include <uapi/asm-generic/poll.h>
#include <linux/poll.h>

struct my_poll_list {
	struct my_poll_list *next;
	int len;
	struct pollfd entries[0];
};

#define N_STACK_PPS ((sizeof(stack_pps) - sizeof(struct my_poll_list))  / \
			sizeof(struct pollfd))

#define DMA_ALLOC_ORDER (2)

struct page * pg_addr;
static int tap_page_init(void)
{
	long stack_pps[POLL_STACK_ALLOC/sizeof(long)];

	printk("++%s++\n", __func__);

	printk("sizeof(struct my_poll_list) = %ld\n", sizeof(struct my_poll_list));
	printk("sizeof(stack_pps) = %ld, N_STACK_PPS = %ld\n", sizeof(stack_pps), N_STACK_PPS);

	pg_addr = alloc_pages(GFP_KERNEL|GFP_DMA, DMA_ALLOC_ORDER);
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
	free_pages((unsigned long)pg, DMA_ALLOC_ORDER);
	return;
}

module_init(tap_page_init);
module_exit(tap_page_exit);

MODULE_LICENSE("GPL");

