#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

static char *buf;

/* use-after-free(uaf) issue */
void create_uaf_error(void)
{
	int i;
	buf = kmalloc(32, GFP_KERNEL);
	for(i = 0; i < 32; i++) 
		printk("0x%x ", *(buf+i));
	printk("\n");
	if(buf) {
		kfree(buf);
		printk("uaf: Access after free\n");
		memset(buf, 0x55, 32);
		for(i = 0; i < 32; i++) 
			printk("0x%x ", *(buf+i));
	}
}

static int __init uaf_test_init(void)
{
	printk("++%s++\n", __func__);
	create_uaf_error();
	return 0;
}

static void __exit uaf_test_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

MODULE_LICENSE("GPL");
module_init(uaf_test_init);
module_exit(uaf_test_exit);
