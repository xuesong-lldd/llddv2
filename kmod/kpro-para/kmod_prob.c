#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <asm-generic/module.h>
#include <uapi/linux/elf-em.h>

struct load_info {
	const char *name;
	struct module *mod;
	Elf_Ehdr *hdr;
	unsigned long len;
};

static struct kprobe kp = {
	.symbol_name = "load_module",
};

static inline const char *get_machine_type(unsigned int type)
{
	const char *machine;
	switch (type) {
		case 40:
		machine = "arm";
		break;

		case 50:
		machine = "IA64";
		break;

		case 62:
		machine = "ECS AMD x86_64";
		break;

		case 183:
		machine = "arm64";
		break;

		default:
		machine = "unknown";
	};

	return machine;
}
void dump_elf_header(Elf_Ehdr *hdr)
{
	printk("\tDUMP OF ELF HEADER\n");
	printk("\t==================\n");
	printk("\te_id = %s, e_type = %u, e_machine = %s\n", hdr->e_ident, hdr->e_type, get_machine_type(hdr->e_machine));
}

/* kprobe handler_pre: called just before the probed instruction is executed */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	struct load_info *pli;
	unsigned long v;
	char *buf;
	
	printk(KERN_INFO "pre_handler: p->addr = 0x%px, ip = 0x%lx,"
			" flags = 0x%lx, cs = %lu\n",
		p->addr, regs->ip, regs->flags, regs->cs);

	if (user_mode(regs))
		panic("kprobe %s in user mode\n", __func__);
	else
		printk("in kern mode\n");

	pli = (struct load_info *)regs->di;

	printk("length of kmod file: %lu\n", pli->len);
	dump_elf_header(pli->hdr);

	buf = (char *)pli->hdr;
	buf += sizeof(Elf_Ehdr);

	v = *(unsigned long *)buf;

	printk("\nvalue @[offfset:%lu] = 0x%lx\n", sizeof(Elf_Ehdr), v);
	
	return 0;
}

static unsigned long *addr;

static int kpro_init(void)
{
	int ret;
	/* !!!! change this value according to the actual va of func in vmlinux */
	printk("+%s\n", __func__);
	kp.pre_handler = handler_pre;
	addr = (unsigned long*)kallsyms_lookup_name(kp.symbol_name);
	printk("addr = %px\n", addr);
	ret = register_kprobe(&kp);
	if (ret < 0) {
		printk(KERN_INFO "register_kprobe failed:%d\n", ret);
		return ret;
	}
	printk(KERN_INFO "registed kprobe %s:@0x%px\n", kp.symbol_name, kp.addr);

	return 0;
}

static void kpro_exit(void)
{
	printk("+%s\n", __func__);
	unregister_kprobe(&kp);
	printk(KERN_INFO "kprobe@ 0x%px unregistered\n", kp.addr);

	return;
}

module_init(kpro_init);
module_exit(kpro_exit);

MODULE_LICENSE("GPL");

