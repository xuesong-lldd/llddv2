#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

static char *buf;

/*
 * Those tricky magic number is only effective for slub_debug,
 * it doesn't work for KASAN detector...
 */
#define OOB_HIT         0x55
#define OOB_BYPASS      0xcc

/* oob issue */
void create_oob_error(void)
{
	int i;

	buf = kmalloc(8, GFP_KERNEL);
	if(buf) {
		memset(buf, OOB_HIT, 12);
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
