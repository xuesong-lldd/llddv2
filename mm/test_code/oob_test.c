#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

static char *buf;

/* oob issue */
void create_oob_error(void)
{
	int i;

	buf = kmalloc(8, GFP_KERNEL);
	if(buf) {
		memset(buf, 0x55, 12);
		for(i = 0; i < 12; i++) 
			printk("%x ", *(buf+i));
		printk("\n");
	}
}

static int __init oob_test_init(void)
{
	printk("++%s++\n", __func__);
	create_oob_error();
	return 0;
}

static void __exit oob_test_exit(void)
{
	printk("--%s--\n", __func__);
	/* trigger the oob check */
	kfree(buf);
	return; 
}

MODULE_LICENSE("GPL");
module_init(oob_test_init);
module_exit(oob_test_exit);
