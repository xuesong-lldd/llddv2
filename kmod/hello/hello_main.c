#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

void demofunc(int a, int b)
{
	printk("from the exported function: %d/%d\n", a, b);

	return;
}

EXPORT_SYMBOL_GPL(demofunc);
int major[BLKDEV_MAJOR_MAX];
static int hello_init(void)
{
	int v, i, idx = 0;
	char name[16];
	printk("++%s++\n", __func__);
	printk("hello world!\n");

	printk("BLKDEV_MAJOR_MAX = %d\n", BLKDEV_MAJOR_MAX);
	for (i = 0; i < BLKDEV_MAJOR_MAX; i++) {
		printk("i = %d\n", i);
		sprintf(name, "myblock%d", i);
		v = register_blkdev(0, name);
		if (v < 0) {
			printk("register_blkdev failed: %d\n", v);
			continue;
		}
		printk("major = %d\n", v);
		major[idx++] = v;
	}
	printk("idx = %d\n", idx);
	for (i = 0; i < idx; i++) {
		sprintf(name, "myblock%d", i);
		printk("unregister %s, major = %d\n", name, major[i]);
		unregister_blkdev(major[i], name);
	}
	return 0;
}

static void hello_exit(void)
{
	printk("--%s--\n", __func__);
	return;
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
MODULE_INFO(intree, "Y");
