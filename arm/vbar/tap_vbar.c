#include <linux/module.h>

#define ELx_INFO(el) \
do { \
	if ((el) == 0) \
		pr_info("" #el " is not implemented\n"); \
	else if ((el) == 1) \
		pr_info("" #el " can be executed in AArch64 state only\n"); \
	else if ((el) == 2) \
		pr_info("" #el " can be executed in either AArch64 or AArch32 state\n"); \
	else \
		pr_info("" #el ": reserved value(0x%x)\n", (el)); \
} while (0)

typedef struct {
	int counter;
} my_atomic_t;

#ifdef LSE_SUPPORT
static void lse_add_test(int i, my_atomic_t *v)
{
	asm volatile("stadd %w[i], %[v]\n"
		      : [i] "+r" (i), [v] "+Q" (v->counter)
		      : "r" (v));
}
#endif

static void dump_processor_features(u64 fea)
{
	u8 el0, el1, el2, el3;

	pr_info("fea = 0x%llx\n", fea);
	el3 = (fea & 0xf << 12) >> 12;
	el2 = (fea & 0xf << 8) >> 8;
	el1 = (fea & 0xf << 4) >> 4;
	el0 = fea & 0xf;
	ELx_INFO(el3);
	ELx_INFO(el2);
	ELx_INFO(el1);
	ELx_INFO(el0);
}

static int pe_tap_init(void)
{
	u64 vbar_el1_var, cur_el, sp_sel;
	u64 a64_isattr_reg_0, a64_feature_reg_0;
	u8 el;
#ifdef LSE_SUPPORT
	my_atomic_t v = {
		.counter = 10
	};
#endif
	pr_info("++%s++\n", __func__);

	asm volatile (
		"mrs %0, vbar_el1\t\n"
		"mrs %1, CurrentEL\t\n"
		"mrs %2, SPSel\t\n"
		"mrs %3, ID_AA64PFR0_EL1\t\n"
		"mrs %4, ID_AA64ISAR0_EL1\t\n"
		:"=r"(vbar_el1_var), "=r"(cur_el), "=r"(sp_sel),
		"=r"(a64_feature_reg_0), "=r"(a64_isattr_reg_0));
	pr_info("vbar_el1 = 0x%llx\n", vbar_el1_var);
	el = (cur_el & (3ULL << 2)) >> 2;
	pr_info("currentEL = %u\n", el);
	pr_info("SP sel = SP_EL%u\n", sp_sel & 1ULL ? el : 0);

	/* lse feature check */
	pr_info("isa att = 0x%llx\n", a64_isattr_reg_0);
	pr_info("LSE supported: %s\n", (a64_isattr_reg_0 & 0xf << 20) >> 20 != 0 ? "YES" : "NO");
#ifdef LSE_SUPPORT
	lse_add_test(5, &v);
#endif
	dump_processor_features(a64_feature_reg_0);

	return 0;
}


static void pe_tap_exit(void)
{
	printk("--%s--\n", __func__);

	return;
}

module_init(pe_tap_init);
module_exit(pe_tap_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
