#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>

struct jprobe jp;

int jp_do_execve(char *filename, char __user *__user *argv,
                 char __user *__user *envp, struct pt_regs *regs)
{
    dump_stack();
    jprobe_return();
    return 0;
}

static __init int init_jprobe_sample(void)
{
    jp.entry = JPROBE_ENTRY(jp_do_execve);
    //jp.kp.symbol_name = "do_execve";
    jp.kp.addr = 0xffffffff8003e1b4;
    register_jprobe(&jp);

    return 0;
}
module_init(init_jprobe_sample);

static __exit void cleanup_jprobe_sample(void)
{
    unregister_jprobe(&jp);
}
module_exit(cleanup_jprobe_sample);

MODULE_LICENSE("GPL");
