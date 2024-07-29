#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/ptrace.h>

/* check current EL, SP selection, VHE and LSE support or not */
static int pstate_demo_init(void)
{
	u64 cur_el, sp_sel, spsr_el1, id_mmfr, id_isar;
	u64 el, state_el0;
	pr_info("++%s++\n", __func__);

	asm volatile (
		"mrs %0, CurrentEL\t\n"
		"mrs %1, SPSel\t\n"
		"mrs %2, SPSR_EL1\t\n"
		"mrs %3, ID_AA64MMFR1_EL1\t\n"
		"mrs %4, ID_AA64ISAR0_EL1\t\n"
		:"=r"(cur_el), "=r"(sp_sel), "=r"(spsr_el1), "=r"(id_mmfr), "=r"(id_isar)
		::"memory"
		);
	el = (cur_el & (3ULL << 2)) >> 2;
	state_el0 = (spsr_el1 & (1UL << 4)) >> 4;
	pr_info("current EL = %lld\n", el);
	pr_info("SP sel = SP_EL%lld\n", sp_sel & 1ULL ? el : 0);
	pr_info("Execution State in EL0 is %s\n", state_el0 ? "AArch32" : "AArch64");
	pr_info("VHE is%ssupported\n", id_mmfr & (1UL << 8) ? " " : " not ");
	pr_info("LSE is%ssupported\n", id_isar & (1UL << 21) ? " " : " not ");

	return 0;
}

static void pstate_demo_exit(void)
{
	pr_info("--%s--\n", __func__);
	return;
}

module_init(pstate_demo_init);
module_exit(pstate_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");

