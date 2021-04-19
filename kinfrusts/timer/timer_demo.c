#include <linux/module.h>
#include <linux/slab.h>

struct timer_container {
	unsigned long demo_val;
	struct timer_list demo_timer;
};


struct timer_container *g_demo_timer;

void demo_timer_callback(struct timer_list *t)
{
	struct timer_container *pcon = from_timer(pcon, t, demo_timer);
	printk("+demo_timer_callback: demo_val = 0x%lx\n", pcon->demo_val);
}

static int demo_timer_init(void)
{
	printk("++%s++\n", __func__);

	g_demo_timer = (struct timer_container *)kzalloc(sizeof(*g_demo_timer), GFP_KERNEL);
	g_demo_timer->demo_val = 0xdeadbeef;

	timer_setup(&g_demo_timer->demo_timer, demo_timer_callback, 0);
	g_demo_timer->demo_timer.expires = jiffies + 10 * HZ;
	add_timer(&g_demo_timer->demo_timer);

	if (timer_pending(&g_demo_timer->demo_timer)) {
		printk("timer is pending...\n");
	}

	return 0;
}

static void demo_timer_exit(void)
{
	printk("--%s--\n", __func__);
	if (timer_pending(&g_demo_timer->demo_timer)) {
                printk("timer is pending...\n");
        } else {
		printk("timer has been deactived after the expires\n");
	}

	del_timer_sync(&g_demo_timer->demo_timer);
	kfree(g_demo_timer);
	return;
}

module_init(demo_timer_init);
module_exit(demo_timer_exit);

MODULE_LICENSE("GPL");

