/*
 * This kmod register a kprob@init_pwq to verify that the 2nd wq object with
 * the same attrs as the 1st one will point to the same worker_pool, looks like:
 *
 *     wq0 --> pwq0 --> |
 *                      +--> pool
 *     wq1 --> pwq1 --> | 
 * The output of the 'insmod tap_kpro.ko' on an arm64 platform:
 * ...
 * [ 4536.796574] +kp_handler_pre+
 * [ 4536.796577] pwq = 0xffffff8800e3f300, wq = 0xffffff8806718c00, pool = 0xffffff8800015000
 * [ 4536.796614] +kp_handler_pre+
 * [ 4536.796617] pwq = 0xffffff8800b80800, wq = 0xffffff8806718400, pool = 0xffffff8800015000
 * ...
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

#define x86_64

struct workqueue_struct *wq0, *wq1;

static struct kprobe kp = {
        .symbol_name = "init_pwq",
};

static int kp_handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	struct pool_workqueue *pwq;
	struct workqueue_struct *wq;
        struct worker_pool *pool;

#ifdef x86_64
	/* 
	 * According to the x86_64 ABI spec:
         * the 1st arg: %rdi, the 2nd arg: %rsi, the 3rd arg: %rdx, ...
         */
	pwq = (struct pool_workqueue *)regs->di;
	wq = (struct workqueue_struct *)regs->si;
        pool = (struct worker_pool *)regs->dx;
#endif
#ifdef arm64
	/*
	 * According to the arm64 ABI spec:
	 * the 1st arg: %x0, the 2nd arg: %x1, the 3rd arg: %x2, ...
	 */
	pwq = (struct pool_workqueue *)regs->regs[0];
	wq = (struct workqueue_struct *)regs->regs[1];
	pool = (struct worker_pool *)regs->regs[2];	
#endif
        pr_info("+%s+\n", __func__);

        pr_info("pwq = 0x%px, wq = 0x%px, pool = 0x%px\n", pwq, wq, pool);
        return 0;
}

bool register_ok = false;
static int tap_kpro_init(void)
{
        int ret;

        pr_info("+%s+\n", __func__);
        kp.pre_handler = kp_handler_pre;
        ret = register_kprobe(&kp);
        if (ret < 0) {
                pr_err("register kp failed, ret = %d\n", ret);
                return -1;
        }

        pr_info("register kprob ok\n");
        register_ok = true;

	/* to trigger the init_pwq(...) */
	wq0 = alloc_workqueue("unbound_wq0", WQ_UNBOUND, WQ_UNBOUND_MAX_ACTIVE);
	wq1 = alloc_workqueue("unbound_wq1", WQ_UNBOUND, WQ_UNBOUND_MAX_ACTIVE);
	if (!wq0 || !wq1) {
		pr_err("alloc_workqueue failed\n");
		return -1;
	}

        return 0;
}

static void tap_kpro_exit(void)
{
        pr_info("+%s+\n", __func__);

	destroy_workqueue(wq1);
	destroy_workqueue(wq0);

        if (register_ok)
                unregister_kprobe(&kp);
}

module_init(tap_kpro_init);
module_exit(tap_kpro_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
