#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include <uapi/asm/mce.h>

typedef void (*p_fn)(struct mce *);
static int tap_ksyms_init(void)
{
	void *p;
	p_fn call_fun;
	struct mce m = {0};

	pr_info("++%s++\n", __func__);
	p = (void *)kallsyms_lookup_name("print_mce");
	if (!p)
		pr_err("kallsyms_lookup_name(...) failed\n");
	else {
		pr_info("p = 0x%px\n", p);
		call_fun = p;
		call_fun(&m);
	}

	return 0;
}

static void tap_ksyms_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(tap_ksyms_init);
module_exit(tap_ksyms_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
