#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

static struct kprobe kp = {
	.symbol_name = "_do_fork",
};

/* kprobe pre_handler: called just before the probed instruction is executed */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	printk(KERN_INFO "pre_handler: p->addr = 0x%p, ip = %lx,"
			" flags = 0x%lx, cs = %lu\n",
		p->addr, regs->ip, regs->flags, regs->cs);
	
	return 0;
}

/* kprobe post_handler: called after the probed instruction is executed */
static void handler_post(struct kprobe *p, struct pt_regs *regs,
				unsigned long flags)
{
	printk(KERN_INFO "post_handler: p->addr = 0x%p, flags = 0x%lx\n",
		p->addr, regs->flags);
}

static int kpro_init(void)
{
	int ret;
	printk("+%s\n", __func__);
	kp.pre_handler = handler_pre;
	kp.post_handler = handler_post;

	ret = register_kprobe(&kp);
	if (ret < 0) {
		printk(KERN_INFO "register_kprobe failed:%d\n", ret);
		return ret;
	}
	printk(KERN_INFO "registed kprobe @0x%p\n", kp.addr);
	return 0;
}

static void kpro_exit(void)
{
	printk("+%s\n", __func__);
	unregister_kprobe(&kp);
	printk(KERN_INFO "kprobe@ 0x%p unregistered\n", kp.addr);
	return;
}

module_init(kpro_init);
module_exit(kpro_exit);

MODULE_LICENSE("GPL");

