#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>

typedef struct {
	int cpu_idx;
} tap_percpu_t;

static DEFINE_PER_CPU_SHARED_ALIGNED(tap_percpu_t, cpu_taps);

static int tap_percpu_init(void)
{
	int cpu;
	tap_percpu_t *p;
	printk("++%s++\n", __func__);
	for_each_possible_cpu(cpu) {
		p = &per_cpu(cpu_taps, cpu);
		printk("[%d] p = 0x%lx, next = 0x%lx\n", cpu, (size_t)p, ((size_t)p + sizeof(*p)));
		p->cpu_idx = cpu;
	}	

	return 0;
}

static void tap_percpu_exit(void)
{
	tap_percpu_t *p;
	printk("--%s--\n", __func__);
	p = &per_cpu(cpu_taps, smp_processor_id());
	printk("p->cpu_idx = %d\n", p->cpu_idx);
	return;
}

module_init(tap_percpu_init);
module_exit(tap_percpu_exit);

MODULE_LICENSE("GPL");

