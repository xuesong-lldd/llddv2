#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/ptrace.h>

static int pstate_demo_init(void)
{
	u64 cur_el, sp_sel, spsr_el1;
	u64 el, state_el0;
	printk("++%s++\n", __func__);

	asm volatile (
		"mrs %0, CurrentEL\t\n"
		"mrs %1, SPSel\t\n"
		"mrs %2, SPSR_EL1\t\n"
		:"=r"(cur_el), "=r"(sp_sel), "=r"(spsr_el1)
		);
	el = (cur_el & (3ULL << 2)) >> 2;
	state_el0 = (spsr_el1 & (1UL << 4)) >> 4;
	pr_info("current EL = %lld\n", el);
	pr_info("SP sel = SP_EL%lld\n", sp_sel & 1ULL ? el : 0);
	pr_info("Execution State in EL0 is %s\n", state_el0 ? "AArch32" : "AArch64");

	return 0;
}

static void pstate_demo_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(pstate_demo_init);
module_exit(pstate_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");

