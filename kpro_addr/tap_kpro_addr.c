#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

static struct kprobe kp = {
	.symbol_name = "_do_fork",
};

/* kprobe pre_handler: called just before the probed instruction is executed */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	printk(KERN_INFO "pre_handler: p->addr = 0x%px, ip = 0x%lx,"
			" flags = 0x%lx, cs = %lu\n",
		p->addr, regs->ip, regs->flags, regs->cs);
	dump_stack();
	
	return 0;
}

static int kpro_addr_init(void)
{
	int ret;
	kprobe_opcode_t *addr;

	printk("+%s\n", __func__);
	kp.pre_handler = handler_pre;

	addr = (kprobe_opcode_t *)kallsyms_lookup_name(kp.symbol_name);
	printk("addr = %px, op_code = 0x%lx\n", addr, (unsigned long)*addr);
	ret = register_kprobe(&kp);
	if (ret < 0) {
		printk(KERN_INFO "register_kprobe failed:%d\n", ret);
		return ret;
	}
	printk("addr = %px, op_code = 0x%lx\n", addr, (unsigned long)*addr);
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

