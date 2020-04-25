#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/mm.h>


static int tap_atomic_init(void)
{
	unsigned long *kp;
	void *sym_p, *vp, *pg_addr;
	phys_addr_t pa;
	struct page *pg, *ipg;
	int valid;

	printk("++%s++\n", __func__);
	printk("__PHYSICAL_START = 0x%x\n", __PHYSICAL_START);
	/* check some addr translation macro */
	printk("__START_KERNEL_map = 0x%lx, PAGE_OFFSET = 0x%lx, phys_base =0x%lx\n",__START_KERNEL_map, PAGE_OFFSET, phys_base);

	/* check the 'kernel text mapping' area in the kernel virtual mem space */
	pa = __pa_symbol(alloc_workqueue);
	sym_p = alloc_workqueue;

	/* check the 'direct mapping of all physical memory (page_offset_base)' area */
	printk("page_offset_base = 0x%lx\n", page_offset_base);	
	kp = kzalloc(sizeof(*kp), GFP_KERNEL);
	printk("kp = 0x%px, pa = 0x%llx, sym_p = 0x%px\n", kp, pa, sym_p);

	/* check the 'vmalloc/ioremap space (vmalloc_base)' area */
	vp = vmalloc(sizeof(unsigned long));
	printk("vp = 0x%px\n", vp);

	/* page allocator */
	pg = alloc_page(GFP_KERNEL);
	pg_addr = page_address(pg);
	printk("pg_addr = 0x%px\n", pg_addr);

	/* chack address valid */
	valid = !!virt_addr_valid(sym_p);
	printk("sym_p valid = %d\n", valid);

	valid = !!virt_addr_valid(pg_addr);
	printk("pg_addr valid = %d\n", valid);

	valid = !!virt_addr_valid(vp);
	printk("vp valid = %d\n", valid);
	valid = !!virt_addr_valid(kp);
	printk("kp valid = %d\n", valid);

	/* dissect the page corresponding to the kernel image mapping area */
	ipg = virt_to_page(sym_p);
	printk("ipg = %px, virp of page = %px\n", ipg, page_address(ipg));

	free_page((unsigned long)pg_addr);
	free_page((unsigned long)sym_p);
	vfree(vp);
	kfree(kp);
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

