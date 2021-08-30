#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ioport.h>

static int tap_res_init(void)
{
	struct resource *r;
	pr_info("+%s+\n", __func__);
	
	r = request_mem_region(0xC0100000, 4, "EINJ NAME");
	if (!r) {
		pr_err("request_mem_region() failed\n");
		return -1;
	}
	pr_info("request_mem_region() succeeds: %pR\n", r);

	return 0;
}

static void tap_res_exit(void)
{
	printk("+%s+\n", __func__);
	release_mem_region(0xC0100000, 4);
	return;
}

module_init(tap_res_init);
module_exit(tap_res_exit);

MODULE_LICENSE("GPL");

