#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

static struct kprobe kp = {
	.symbol_name = "mmap_region",
};

/*
 * prototype of the 'mmap_region()':
 * unsigned long mmap_region(struct file *file, unsigned long addr,
 *		unsigned long len, vm_flags_t vm_flags, unsigned long pgoff,
 *		struct list_head *uf)
 */

/* kprobe handler_pre: called just before the probed instruction is executed */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	/*
	 * according to the x86_64 ABI: the 2nd para is in %rsi, the 3rd is in %rdx,
	 * the 5th is in the %r8
	 */
	unsigned long addr, len, pgoff;
	addr = regs->si;
	len = regs->dx;
	pgoff = regs->r8;

	pr_info("%s: addr = 0x%lx, len = 0x%lx, pgoff = 0x%lx\n", p->symbol_name,
		addr, len, pgoff);
	
	return 0;
}

static int mmap_kpro_init(void)
{
	int ret;

	/* !!!! change this value according to the actual va of func in vmlinux */
	pr_info("+%s\n", __func__);
	kp.pre_handler = handler_pre;
	ret = register_kprobe(&kp);
	if (ret < 0) {
		pr_err("register_kprobe failed:%d\n", ret);
		return ret;
	}

	pr_info("registed kprobe @0x%px\n", kp.addr);

	return 0;
}

static void mmap_kpro_exit(void)
{
	pr_info("+%s\n", __func__);

	unregister_kprobe(&kp);

	return;
}

module_init(mmap_kpro_init);
module_exit(mmap_kpro_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
