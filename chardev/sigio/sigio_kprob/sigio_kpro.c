#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/fs.h>
#include <linux/sched.h>

static struct kprobe kp = {
	.symbol_name = "send_sigio",
};

/*
 * prototype of the 'send_sigio()':
 * void send_sigio(struct fown_struct *fown, int fd, int band);
 * we use this kprob to demo how the fcntl(fd, F_SETOWN, getpid())
 * to affect the behavior of the kill_fasync(...) --> send_sigio(...)
 */

/* kprobe handler_pre: called just before the probed instruction is executed */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	/*
	 * according to the x86_64 ABI: the 1st in %rdi, the 2nd para is in %rsi,
	 * the 3rd is in %rdx, the 5th is in the %r8
	 */
	struct pid *pid;
	struct fown_struct *fown;
	struct task_struct *t;
	
	fown = (struct fown_struct *)regs->di;
	pid = fown->pid;
	if (pid) {
		t = pid_task(pid, PIDTYPE_PID);
		if (t)
			pr_info("pid = %d\n", t->pid);
		else
			pr_info("pid is not null, but failed to get task\n");
	} else
		pr_info("pid is NULL\n");		
	
	return 0;
}

static int sigio_kpro_init(void)
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

static void sigio_kpro_exit(void)
{
	pr_info("+%s\n", __func__);

	unregister_kprobe(&kp);

	return;
}

module_init(sigio_kpro_init);
module_exit(sigio_kpro_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
