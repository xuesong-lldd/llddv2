#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

static struct kprobe kp = {
	//.symbol_name = "free_task",
	.symbol_name = "put_task_struct_rcu_user",
};

/* kprobe handler_pre: called just before the probed instruction is executed */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	struct task_struct *tsk;
	tsk = (struct task_struct *)regs->di;
	if (!strncmp(tsk->comm, "mykthead@cpu0", sizeof("mykthead@cpu0"))) {
		printk("kthread name: %s[pid = %d]\n", tsk->comm, tsk->pid);
		dump_stack();
	}

	return 0;
}

static int kpro_init(void)
{
	int ret;

	printk("+%s\n", __func__);
	kp.pre_handler = handler_pre;
	ret = register_kprobe(&kp);
	if (ret < 0) {
		printk(KERN_INFO "register_kprobe failed:%d\n", ret);
		return ret;
	}
	pr_info("registed kprobe @0x%px\n", kp.addr);

	return 0;
}

static void kpro_exit(void)
{
	printk("+%s\n", __func__);

	printk(KERN_INFO "kprobe@ 0x%px unregistered\n", kp.addr);
	unregister_kprobe(&kp);

	return;
}

module_init(kpro_init);
module_exit(kpro_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
