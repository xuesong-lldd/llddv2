#include <linux/module.h>
#include <linux/delay.h>
#include <asm/io.h>

#define GPIO_BASE 0xfe200000 
static int led_demo_init(void)
{
	void __iomem *gpio_base_va;
	u32 *gpfsel1, *gpfsel2, *gpset0, *gpclr0, *gplev0;
	u32 *gplen0, *gpeds0;
	u32 val;

	gpio_base_va = ioremap(GPIO_BASE, 0x100);
	if (!gpio_base_va) {
	    pr_err("ioremap failed\n");
	    return -1;
	}

	pr_info("rasp: gpio_base_va = %p\n", gpio_base_va);

	/* LED1: GPIO19 */
	gpfsel1 = gpio_base_va + 0x04;
	val = *(u32 *)gpfsel1;
	/* set output */
	val |= (1 << 27);
	*(u32 *)gpfsel1 = val;
	/* turn off: gpio output high level */
	gpset0 = gpio_base_va + 0x1C;
	*(u32 *)gpset0 = (1 << 19);
	mdelay(3000);
	/* turn on: gpio output low level */
	gpclr0 = gpio_base_va + 0x28;
	*(u32 *)gpclr0 = (1 << 19);

	mdelay(1000);

	/* LED2: GPIO16 */
	gpfsel1 = gpio_base_va + 0x04;
	val = *(u32 *)gpfsel1;
	/* set output */
	val |= (1 << 18);
	*(u32 *)gpfsel1 = val;
	/* turn off: gpio output high level */
	gpset0 = gpio_base_va + 0x1C;
	*(u32 *)gpset0 = (1 << 16);
	mdelay(3000);
	/* turn on: gpio output low level */
	gpclr0 = gpio_base_va + 0x28;
	*(u32 *)gpclr0 = (1 << 16);

	mdelay(1000);

	/* BUZZER: GPIO13 */
	gpfsel1 = gpio_base_va + 0x04;
	/* set output */
	val = *(u32 *)gpfsel1;
	val |= (1 << 9);
	*(u32 *)gpfsel1 = val;

	/* buzzer on: high level */
	*(u32 *)gpset0 = (1 << 13);
	mdelay(3000);
	/* buzzer off: low level */
	*(u32 *)gpclr0 = (1 << 13);

	/* key2: GPIO18 */
	gpfsel2 = gpio_base_va + 0x08;
	/* set input */
	val = *gpfsel1;
	val &= ~(7 << 24);
	*gpfsel1 = val;

	gplev0 = gpio_base_va + 0x34;
	gpeds0 = gpio_base_va + 0x40;
	val = *gplev0;
	if (val & (1 << 18))
		pr_info("GPIO18 High Level\n");
	else 
		pr_info("GPIO18 Low Level\n");

	while(1) {
		val = *gplev0;
		if (!(val & (1 << 18))) {
			pr_info("key#2 pressed...\n");
			break;
		}
		mdelay(500);
	}

	iounmap(gpio_base_va);

	return 0;
}


static void led_demo_exit(void)
{
	printk("--%s--\n", __func__);

	return;
}

module_init(led_demo_init);
module_exit(led_demo_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
