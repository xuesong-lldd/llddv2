#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/ptrace.h>
#include <linux/device.h>
#include <linux/device/driver.h>
#include <linux/platform_device.h>

static struct kprobe kp0 = {
        .symbol_name = "driver_attach",
};

static int kp0_handler_pre(struct kprobe *p, struct pt_regs *regs)
{
        struct device_driver *drv;
        drv = (struct device_driver *)regs_get_register(regs, 0);
        pr_info("+%s+\n", __func__);

        pr_info("drv->name = %s\n", drv->name);
        pr_info("drv = 0x%px\n", drv);
        return 0;
}

bool register_ok = false;
static int tap_kpro_init(void)
{
        int ret;

        pr_info("+%s+\n", __func__);
        kp0.pre_handler = kp0_handler_pre;
        ret = register_kprobe(&kp0);
        if (ret < 0) {
                pr_err("register kp0 failed, ret = %d\n", ret);
                return -1;
        }

        pr_info("register kprob ok\n");
        register_ok = true;

        return 0;
}

static void tap_kpro_exit(void)
{
        pr_info("+%s+\n", __func__);
        if (register_ok)
                unregister_kprobe(&kp0);
}

module_init(tap_kpro_init);
module_exit(tap_kpro_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
