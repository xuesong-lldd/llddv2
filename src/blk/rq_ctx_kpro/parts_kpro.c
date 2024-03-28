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
#include <linux/blk_types.h>
#include <linux/blk-mq.h>

struct blk_mq_alloc_data {
	/* input parameter */
	struct request_queue *q;
	blk_mq_req_flags_t flags;
	unsigned int shallow_depth;
	blk_opf_t cmd_flags;
	req_flags_t rq_flags;

	/* allocate multiple requests/tags in one go */
	unsigned int nr_tags;
	struct request **cached_rq;

	/* input & output parameter */
	struct blk_mq_ctx *ctx;
	struct blk_mq_hw_ctx *hctx;
};

#define x86_64

static void dump_rq(struct request *rq, unsigned int tag)
{
	int i = 0;
	struct bio *bio, *next;
	struct bio_vec bvec;
	struct bvec_iter iter;

	if (!rq) {
		pr_err("rq == NULL\n");
		return;
	}

	bio = rq->bio;
	pr_info("rq[%u] = 0x%px\n", tag, rq);
	pr_info("s_sector = %llu\n", rq->__sector);
	while (bio) {
		pr_info("bio[%d].s_sector = %llu, nr_sectors = %u\n",
			i++, bio->bi_iter.bi_sector, bio_sectors(bio));
		next = bio->bi_next;
		bio_for_each_segment(bvec, bio, iter) {
	
		}
		bio = next;
	}
	
}

static void kp_handler_post(struct kprobe *p, struct pt_regs *regs, unsigned long flags);

static struct kprobe kp = {
        .symbol_name = "blk_mq_rq_ctx_init.isra.0",
	.post_handler = kp_handler_post
};

static void kp_handler_post(struct kprobe *p, struct pt_regs *regs, unsigned long flags)
{
	int i;
	struct blk_mq_alloc_data *data;
	struct blk_mq_tags *tags;
	unsigned int tag;
	struct request_queue *q;
	struct request *rq;
#ifdef x86_64
	/*
	 * According to the x86_64 ABI spec:
	 * the 1st arg: %rdi, the 2nd arg: %rsi, the 3rd arg: %rdx,
	 * the 4th: %rcx, the 5th: %r8, the 6th: %r9. The rest are in
	 * the local stack...
	 */
	data = (struct blk_mq_alloc_data *)regs->di;
	tags = (struct blk_mq_tags *)regs->si;
        tag = (unsigned int)regs->dx;
#endif
#ifdef arm64
	/*
	 * According to the arm64 ABI spec:
	 * the 1st arg: %x0, the 2nd arg: %x1, the 3rd arg: %x2, the 4th arg: %x3...
	 */
	data = (struct blk_mq_alloc_data *)regs->regs[0];
	tags = (struct blk_mq_tags *)regs->regs[1];
	tag = (unsigned int)regs->regs[2];
#endif
	q = data->q;
	if (!tags) {
		pr_info("%s: tags == NULL\n", __func__);
		return;
	}
	rq = tags->static_rqs[tag];
	if (!strncmp(q->disk->disk_name, "ramsda", 6)) {
		pr_info("%s: tag = %u\n", q->disk->disk_name, tag);
		dump_rq(rq, tag);
		for (i = 0; i < 32; i++) {
			pr_info("rq[%d] = 0x%px\n", i, tags->static_rqs[i]);
		}
	}

	return;
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
