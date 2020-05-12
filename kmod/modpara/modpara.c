#include <linux/module.h>
#include <linux/kernel.h>

/* 
 * demo of kernel module parameters: 
 * $sudo insmod modpara cat=0xdeadbeef is_true=N
 * (valid bool value is 0/1, y/n, Y/N)
 */
static unsigned long cat = 1;
static bool is_true = true;

module_param(cat, ulong, 0);
module_param(is_true, bool, 0);

static int modpara_init(void)
{
	printk("++%s++\n", __func__);
	printk("cat = 0x%lx, bool = %s\n", cat, is_true ? "Yes" : "No");

	return 0;
}

static void modpara_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(modpara_init);
module_exit(modpara_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");

