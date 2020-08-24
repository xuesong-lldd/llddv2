#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/kasan.h>

static noinline void kasan_stack_oob(void)
{
	char stack_array[10];
	volatile int i = 0;
	char *p = &stack_array[ARRAY_SIZE(stack_array) + i];

	pr_info("out-of-bounds on stack\n");
	/* volatile is critical to trigger a memory access, else the gcc
  	 * will try the best to optimize the code with regs access
	 */
	*(volatile char *)p = 10;
}

static int __init kasan_test_init(void)
{
	bool multishot;
	printk("++%s++\n", __func__);
	multishot = kasan_save_enable_multi_shot();
	kasan_stack_oob();
	kasan_restore_multi_shot(multishot);

	return 0;
}

static void __exit kasan_test_exit(void)
{
	printk("--%s--\n", __func__);
	return; 
}

MODULE_LICENSE("GPL");
module_init(kasan_test_init);
module_exit(kasan_test_exit);
