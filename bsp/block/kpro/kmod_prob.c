#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/device.h>
#include <linux/of.h>
#include <asm-generic/module.h>
#include <uapi/linux/elf-em.h>

u16 nr_node = 0;
static struct kprobe kp = {
	.symbol_name = "of_match_node",
};

void dump_device_node(struct device_node *dn)
{
	printk("\tDUMP OF DEVICE NODE\n");
	printk("\t==================\n");
	printk("\t[%d]name = %s, full_name = %s\n", nr_node++, dn->name, dn->full_name);
}

/* kprobe handler_pre: called just before the probed instruction is executed */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	//struct device *dev;
	struct device_node *dn;
	if (user_mode(regs))
		panic("kprobe %s in user mode\n", __func__);
	else
		printk("in kern mode\n");

	/* dev = (struct device *)regs->user_regs.regs[1]; */
	dn = (struct device_node *)regs->user_regs.regs[1];
	//pr_info("compatible = %s\n", comp);
	dump_device_node(dn);

	return 0;
}

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
	printk(KERN_INFO "registed kprobe %s:@0x%px\n", kp.symbol_name, kp.addr);

	return 0;
}

static void kpro_exit(void)
{
	printk("+%s\n", __func__);
	unregister_kprobe(&kp);
	printk(KERN_INFO "kprobe@ 0x%px unregistered\n", kp.addr);

	return;
}

module_init(kpro_init);
module_exit(kpro_exit);

MODULE_LICENSE("GPL");

