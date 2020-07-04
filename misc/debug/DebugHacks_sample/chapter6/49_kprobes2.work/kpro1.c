#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>

struct kprobe kp;

int handler(struct kprobe *p, struct pt_regs *regs) {
    printk(KERN_INFO "rax: %016lx, eflags: %08x, %rip: %016lx\n",
                     regs->rax, regs->eflags, regs->rip);
    return 0;
}

static __init int init_kprobe_sample(void)
{
    kp.symbol_name = "do_execve";
    kp.offset = 50;
    /* kernel version が2.6.18以下なら */
    /* kp.addr = (kprobe_opcode_t *)kallsyms_lookup_name("do_execve") + 56; */

   kp.pre_handler = handler;
   kp.post_handler = handler;
   register_kprobe(&kp);

    return 0;
}
module_init(init_kprobe_sample);

static __exit void cleanup_kprobe_sample(void)
{
    unregister_kprobe(&kp);
}
module_exit(cleanup_kprobe_sample);

MODULE_LICENSE("GPL");
