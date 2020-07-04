#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>

struct jprobe jp;

int jp_do_execve(char *filename, char __user *__user *argv,
                 char __user *__user *envp, struct pt_regs *regs)
{
    int cnt = 0;

    printk(KERN_INFO "filename: %s\n", filename);
    for (; *argv != NULL; argv++, cnt++)
        printk(KERN_INFO "argv[%d]: %s\n", cnt, *argv);

    jprobe_return();
    return 0;
}

static __init int init_jprobe_sample(void)
{
    jp.entry = JPROBE_ENTRY(jp_do_execve);
    jp.kp.symbol_name = "do_execve";
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
