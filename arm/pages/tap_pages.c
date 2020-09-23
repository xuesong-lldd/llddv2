#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/ptrace.h>

static int page_gran_init(void)
{
	u64 mmfr0_el1;
	bool b_4k, b_16k, b_64k;
	printk("++%s++\n", __func__);

	asm volatile (
		"mrs %0, id_aa64mmfr0_el1\t\n"
		:"=r"(mmfr0_el1));
	b_4k = ((mmfr0_el1 & (0xfULL << 28)) >> 28) == 0;
	b_16k = ((mmfr0_el1 & (0xfULL << 20)) >> 20) == 1;
	b_64k = ((mmfr0_el1 & (0xfULL << 24)) >> 24) == 0;
	
	pr_info("4KB page supported [%s]\n", b_4k ? "YES" : "NO");
	pr_info("16KB page supported [%s]\n", b_16k ? "YES" : "NO");
	pr_info("64KB page supported [%s]\n", b_64k ? "YES" : "NO");

	return 0;
}

static void page_gran_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(page_gran_init);
module_exit(page_gran_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");

