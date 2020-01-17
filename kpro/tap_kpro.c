#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

static struct kprobe kp = {
	.symbol_name = "alloc_workqueue",
};

/* kprobe handler_pre: called just before the probed instruction is executed */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	kprobe_opcode_t *addr;
	printk(KERN_INFO "pre_handler: p->addr = 0x%px, ip = 0x%lx,"
			" flags = 0x%lx, cs = %lu\n",
		p->addr, regs->ip, regs->flags, regs->cs);

	if (user_mode(regs))
		panic("kprobe %s in user mode\n", __func__);
	else
		printk("in kern mode\n");
	addr = (kprobe_opcode_t *)(regs->ip - sizeof(kprobe_opcode_t));
	printk("op_code = 0x%x\n", *addr);
	dump_stack();
	
	return 0;
}

static struct workqueue_struct *g_pwq;
static unsigned long *addr;

static int kpro_init(void)
{
	int ret;
	/* !!!! change this value according to the actual va of func in vmlinux */
	printk("+%s\n", __func__);
	kp.pre_handler = handler_pre;
	addr = (unsigned long*)kallsyms_lookup_name(kp.symbol_name);
	printk("addr = %px\n", addr);
	ret = register_kprobe(&kp);
	if (ret < 0) {
		printk(KERN_INFO "register_kprobe failed:%d\n", ret);
		return ret;
	}
	printk("addr = %px\n", addr);
	g_pwq = alloc_workqueue("Kprobe test", 0, 1);
	printk(KERN_INFO "registed kprobe @0x%px\n", kp.addr);
	return 0;
}

static void kpro_exit(void)
{
	printk("+%s\n", __func__);
	destroy_workqueue(g_pwq);
	printk("addr = %px\n", addr);
	unregister_kprobe(&kp);
	printk("addr = %px\n", addr);
	printk(KERN_INFO "kprobe@ 0x%p unregistered\n", kp.addr);
	return;
}

module_init(kpro_init);
module_exit(kpro_exit);

MODULE_LICENSE("GPL");

