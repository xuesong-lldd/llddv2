#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/ptrace.h>

static int vbar_demo_init(void)
{
	u64 vbar_el1_var;
	u64 *opcode;
	printk("++%s++\n", __func__);

	asm volatile (
		"mrs %0, vbar_el1\t\n"
		:"=r"(vbar_el1_var)
		);
	opcode = (u64 *)vbar_el1_var;
	pr_info("vbar_el1 = 0x%llx, opcode = 0x%llx\n", vbar_el1_var, *opcode);
	pr_info("sizeof pt_regs = 0x%lx\n", sizeof(struct pt_regs));
	return 0;
}

static void vbar_demo_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(vbar_demo_init);
module_exit(vbar_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");

