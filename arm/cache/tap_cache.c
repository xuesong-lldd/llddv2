#include <linux/module.h>
#include <linux/kernel.h>

/* cache line helper */
#define CCSIDR_EL1_LINESIZE_MASK	0x7
#define CCSIDR_EL1_LINESIZE(x)		((x) & CCSIDR_EL1_LINESIZE_MASK)
#define CACHE_LINESIZE(x)	(16 << CCSIDR_EL1_LINESIZE(x))

/* cache set helper */
#define CCSIDR_EL1_NUMSETS_SHIFT	13
#define CCSIDR_EL1_NUMSETS_MASK		0x7fff
#define CCSIDR_EL1_NUMSETS(x) \
	(((x) >> CCSIDR_EL1_NUMSETS_SHIFT) & CCSIDR_EL1_NUMSETS_MASK)
#define CACHE_NUMSETS(x)        (CCSIDR_EL1_NUMSETS(x) + 1)

/* cache associativity helper */
#define CCSIDR_EL1_ASSOCIATIVITY_SHIFT	3
#define CCSIDR_EL1_ASSOCIATIVITY_MASK	0x3ff
#define CCSIDR_EL1_ASSOCIATIVITY(x)	\
	(((x) >> CCSIDR_EL1_ASSOCIATIVITY_SHIFT) & CCSIDR_EL1_ASSOCIATIVITY_MASK)
#define CACHE_ASSOCIATIVITY(x)	(CCSIDR_EL1_ASSOCIATIVITY(x) + 1)


static int cache_demo_init(void)
{
	u64 clidr_el1, csselr_el1, ccsidr_el1;
	int line_sz, nr_set, nr_way;
	printk("++%s++\n", __func__);

	/* get the L1 and L2$ type */
	asm volatile (
		"mrs %0, clidr_el1\t\n"
		:"=r"(clidr_el1)
		);
	pr_info("clidr_el1 = 0x%llx\n", clidr_el1);
	/* we'll get the L1 instruction cache first */
	csselr_el1 = 0x1;
	asm volatile (
		"msr csselr_el1, %0\t\n"
		::"r"(csselr_el1)
		);
	isb();
	/* now get the info of the L1 ins cache */
	asm volatile (
		"mrs %0, ccsidr_el1\t\n"
		:"=r"(ccsidr_el1));
	pr_info("\nL1 INST$ = 0x%llx\n", ccsidr_el1);
	pr_info("-----------------------------------------\n");
	line_sz = CACHE_LINESIZE(ccsidr_el1);
	nr_set = CACHE_NUMSETS(ccsidr_el1);
	nr_way = CACHE_ASSOCIATIVITY(ccsidr_el1);
	pr_info("line size = %d, set = %d, way = %d\n", line_sz, nr_set, nr_way);
	pr_info("total size = %dKB\n", (line_sz * nr_set * nr_way)/1024);

	/* select the L1 data cache */
	csselr_el1 = 0x0;
	asm volatile (
		"msr csselr_el1, %0\t\n"
		::"r"(csselr_el1)
		);
	isb();
	/* now get the info of the L1 data cache */
	asm volatile (
		"mrs %0, ccsidr_el1\t\n"
		:"=r"(ccsidr_el1));
	pr_info("\nL1 DATA$ = 0x%llx\n", ccsidr_el1);
	pr_info("-----------------------------------------\n");
	line_sz = CACHE_LINESIZE(ccsidr_el1);
	nr_set = CACHE_NUMSETS(ccsidr_el1);
	nr_way = CACHE_ASSOCIATIVITY(ccsidr_el1);
	pr_info("line size = %d, set = %d, way = %d\n", line_sz, nr_set, nr_way);
	pr_info("total size = %dKB\n", (line_sz * nr_set * nr_way)/1024);

	/* select the L2 unified cache */
	csselr_el1 = 0x2;
	asm volatile (
		"msr csselr_el1, %0\t\n"
		::"r"(csselr_el1)
		);
	isb();
	/* now get the info of the L1 data cache */
	asm volatile (
		"mrs %0, ccsidr_el1\t\n"
		:"=r"(ccsidr_el1));
	pr_info("\nL2 $ = 0x%llx\n", ccsidr_el1);
	pr_info("-----------------------------------------\n");
	line_sz = CACHE_LINESIZE(ccsidr_el1);
	nr_set = CACHE_NUMSETS(ccsidr_el1);
	nr_way = CACHE_ASSOCIATIVITY(ccsidr_el1);
	pr_info("line size = %d, set = %d, way = %d\n", line_sz, nr_set, nr_way);
	pr_info("total size = %dKB\n", (line_sz * nr_set * nr_way)/1024);

	return 0;
}

static void cache_demo_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(cache_demo_init);
module_exit(cache_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");

