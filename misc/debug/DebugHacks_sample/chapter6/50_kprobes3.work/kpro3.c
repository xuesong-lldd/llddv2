#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/binfmts.h>
#include <linux/security.h>
#include <linux/err.h>
#include <linux/kallsyms.h>
#include <linux/acct.h>
#include <linux/file.h>
#include <asm/mmu_context.h>
#include <asm/percpu.h>

#define free_arg_pages(bprm) do { } while (0)
int count(char __user * __user * argv, int max);
int copy_strings(int argc, char __user * __user * argv, struct linux_binprm *bprm);

struct kprobe kp;

int my_do_execve(char * filename,
        char __user *__user *argv,
        char __user *__user *envp,
        struct pt_regs * regs)
{
        struct linux_binprm *bprm;
        struct file *file;
        int retval;
        int i;

        retval = -ENOMEM;
        bprm = kzalloc(sizeof(*bprm), GFP_KERNEL);
        if (!bprm)
                goto out_ret;
        printk("bprm: %p, filename: %s\n", bprm, filename);

        file = open_exec(filename);
        retval = PTR_ERR(file);
        if (IS_ERR(file))
                goto out_kfree;

        sched_exec();

        bprm->p = PAGE_SIZE*MAX_ARG_PAGES-sizeof(void *);

        bprm->file = file;
        bprm->filename = filename;
        bprm->interp = filename;
        bprm->mm = mm_alloc();
        retval = -ENOMEM;
        if (!bprm->mm)
                goto out_file;

        retval = init_new_context(current, bprm->mm);
        if (retval < 0)
                goto out_mm;

        bprm->argc = count(argv, bprm->p / sizeof(void *));
        if ((retval = bprm->argc) < 0)
                goto out_mm;

        bprm->envc = count(envp, bprm->p / sizeof(void *));
        if ((retval = bprm->envc) < 0)
                goto out_mm;

        retval = security_bprm_alloc(bprm);
        if (retval)
                goto out;

        retval = prepare_binprm(bprm);
        if (retval < 0)
                goto out;

        retval = copy_strings_kernel(1, &bprm->filename, bprm);
        if (retval < 0)
                goto out;

        bprm->exec = bprm->p;
        retval = copy_strings(bprm->envc, envp, bprm);
        if (retval < 0)
                goto out;

        retval = copy_strings(bprm->argc, argv, bprm);
        if (retval < 0)
                goto out;

        retval = search_binary_handler(bprm,regs);
        if (retval >= 0) {
                free_arg_pages(bprm);

               /* execve success */
                security_bprm_free(bprm);
                acct_update_integrals(current);
                kfree(bprm);
                return retval;
        }

out:
        /* Something went wrong, return the inode and free the argument pages*/
        for (i = 0 ; i < MAX_ARG_PAGES ; i++) {
                struct page * page = bprm->page[i];
                if (page)
                        __free_page(page);
        }

        if (bprm->security)
                security_bprm_free(bprm);

out_mm:
        if (bprm->mm)
                mmdrop(bprm->mm);

out_file:
        if (bprm->file) {
                allow_write_access(bprm->file);
                fput(bprm->file);
        }

out_kfree:
        kfree(bprm);

out_ret:
        return retval;
}

int handler(struct kprobe *p, struct pt_regs *regs) {
    reset_current_kprobe();
    regs->rip = (unsigned long)my_do_execve;
    preempt_enable_no_resched();
    return 1;
}

static __init int init_kprobe_sample(void)
{
    kp.symbol_name = "do_execve";
    /* kernel version が2.6.18以下なら */
    /* kp.addr = (kprobe_opcode_t *)kallsyms_lookup_name("do_execve"); */

   kp.pre_handler = handler;
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
