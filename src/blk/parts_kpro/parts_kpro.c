/*
 * Add the kpro to the 'add_partition' to dissect the internals
 * of partition devices.
 * Usage: '# insmod partx_kpro.ko' before 'fdisk /dev/ramhda', then
 * 'dmesg' to see the output and the 'fdisk -l /dev/ramhda'
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/blkdev.h>
#include <linux/types.h>

#define x86_64

static int kp_handler_pre(struct kprobe *p, struct pt_regs *regs);

static struct kprobe kp = {
        .symbol_name = "add_partition",
	.pre_handler = kp_handler_pre
};

static int kp_handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	struct gendisk *disk;
	int partno;
	sector_t start, nr_sectors;
#ifdef x86_64
	/*
	 * According to the x86_64 ABI spec:
	 * the 1st arg: %rdi, the 2nd arg: %rsi, the 3rd arg: %rdx,
	 * the 4th: %rcx, the 5th: %r8, the 6th: %r9. The rest are in
	 * the local stack...
	 */
	disk = (struct gendisk *)regs->di;
	partno = (int)regs->si;
        start = (sector_t)regs->dx;
	nr_sectors = (sector_t)regs->cx;
#endif
#ifdef arm64
	/*
	 * According to the arm64 ABI spec:
	 * the 1st arg: %x0, the 2nd arg: %x1, the 3rd arg: %x2, the 4th arg: %x3...
	 */
	disk = (struct gendisk *)regs->regs[0];
	partno = (int)regs->regs[1];
	start = (sector_t)regs->regs[2];
	nr_sectors = (sector_t)regs->regs[3];
#endif
        pr_info("+%s+\n", __func__);
	pr_info("gendisk = 0x%px, partno = %d, start_sec = %llu, nr_sectors = %llu\n",
		disk, partno, start, nr_sectors);

	return 0;
}

static int parts_kpro_init(void)
{
	int ret;
        pr_info("+%s+\n", __func__);

        ret = register_kprobe(&kp);
        if (ret < 0) {
                pr_err("register kp failed, ret = %d\n", ret);
                return -1;
        }

        pr_info("register kprob ok\n");

	return 0;
}

static void parts_kpro_exit(void)
{
        pr_info("+%s+\n", __func__);

	unregister_kprobe(&kp);
}

module_init(parts_kpro_init);
module_exit(parts_kpro_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
