#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

/*
 * dis load_module, the offset 76 is at 'if (info->len < sizeof(*(info->hdr)))' in
 * elf_header_check()
 */
static struct kprobe kp = {
	.symbol_name = "load_module",
	.offset = 76,
};

/* Called before addr is executed... */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	/* r13 should be the length of the kmod file, for instance, the chrdev.ko */
	printk("original r13 = 0x%lx\n", regs->r13);
	return 0;
}

/* Called after addr is executed, unless... */
static void handler_post(struct kprobe *p, struct pt_regs *regs, unsigned long flags)
{
	regs->r13 = 30; /* 30 < sizeof(*(info->hdr)) */
	return;
}

static int kpro_addr_init(void)
{
	int ret;
	unsigned long *addr;

	printk("+%s\n", __func__);
	kp.post_handler = handler_post;
	kp.pre_handler = handler_pre;

	addr = (unsigned long *)kallsyms_lookup_name(kp.symbol_name);
	ret = register_kprobe(&kp);
	if (ret < 0) {
		printk(KERN_INFO "register_kprobe failed:%d\n", ret);
		return ret;
	}
	printk(KERN_INFO "registed kprobe @0x%px\n", kp.addr);
	return 0;
}

static void kpro_addr_exit(void)
{
	printk("+%s\n", __func__);
	unregister_kprobe(&kp);
	printk(KERN_INFO "kprobe@ 0x%px unregistered\n", kp.addr);
	return;
}

module_init(kpro_addr_init);
module_exit(kpro_addr_exit);

MODULE_LICENSE("GPL");

