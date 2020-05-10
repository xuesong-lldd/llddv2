#include <linux/module.h>
#include <linux/gfp.h>
#include <linux/mm.h>

static int tap_vmalloc_init(void)
{
	unsigned long vm_size;
	printk("++%s++\n", __func__);
	pr_info("VMALLOC_START = 0x%lx, VMALLOC_END = 0x%lx\n", VMALLOC_START, VMALLOC_END);	
	vm_size = (VMALLOC_END - VMALLOC_START + 1)/(1024UL * 1024UL * 1024UL * 1024UL);
	pr_info("vmalloc area range = %ld TB\n", vm_size);

	return 0;
}

static void tap_vmalloc_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(tap_vmalloc_init);
module_exit(tap_vmalloc_exit);

MODULE_LICENSE("GPL");

