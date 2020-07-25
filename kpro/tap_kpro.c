#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

static struct kprobe kp = {
	.symbol_name = "alloc_workqueue",
};

/* kprobe handler_pre: called just before the probed instruction is executed */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	char *wq_name;
	kprobe_opcode_t *addr;
	printk(KERN_INFO "pre_handler: p->addr = 0x%px, ip = 0x%lx, cs = %lu\n",
		p->addr, regs->ip, regs->cs);

	if (user_mode(regs))
		panic("kprobe %s in user mode\n", __func__);
	else
		printk("in kern mode\n");
	addr = (kprobe_opcode_t *)(regs->ip - sizeof(kprobe_opcode_t));
	printk("op_code = 0x%x\n", *addr);
	wq_name = (char *)regs->di;
	printk("wq name: %s\n", wq_name);
	/* dump_stack(); */
	
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
	printk("insv@%px = 0x%lx\n", addr, *addr);
	ret = register_kprobe(&kp);
	if (ret < 0) {
		printk(KERN_INFO "register_kprobe failed:%d\n", ret);
		return ret;
	}
	printk("insv@%px = 0x%lx (after registered)\n", addr, *addr);

	/* allocate a workqueue after the kprobe is registered */
	g_pwq = alloc_workqueue("Kprobe test", 0, 1);
	printk(KERN_INFO "registed kprobe @0x%px\n", kp.addr);

	return 0;
}

static void kpro_exit(void)
{
	printk("+%s\n", __func__);

	destroy_workqueue(g_pwq);
	printk(KERN_INFO "kprobe@ 0x%px unregistered\n", kp.addr);
	unregister_kprobe(&kp);


	return;
}

module_init(kpro_init);
module_exit(kpro_exit);

MODULE_LICENSE("GPL");

