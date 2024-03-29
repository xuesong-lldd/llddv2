/*
 * #insmod ramhd_mq_mq.ko
 * #fdisk /dev/ramsda
 * #mkfs.ext4 /dev/ramsda1
 * #mount /dev/ramsda1 /mnt
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/fs.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/vmalloc.h>
#include <linux/blkdev.h>
#include <linux/hdreg.h>
#include <linux/blk-mq.h>
#include <asm/uaccess.h>
#include <linux/sbitmap.h>

#define CREATE_TRACE_POINTS
#include "ramhd_mq.h"

#define RAMHD_NAME              "ramsd"
#define RAMHD_MAX_DEVICE        1
#define RAMHD_MAX_PARTITIONS    2

#define RAMHD_SECTOR_SIZE       512

#define RAMHD_SECTORS           64
#define RAMHD_HEADS             16
#define RAMHD_CYLINDERS         128

#define RAMHD_SECTOR_TOTAL      (RAMHD_SECTORS * RAMHD_HEADS * RAMHD_CYLINDERS)
#define RAMHD_SIZE              (RAMHD_SECTOR_SIZE * RAMHD_SECTOR_TOTAL) /* 64-MB */

typedef struct{
	char   *data;
	struct request_queue *queue;
	spinlock_t      lock;
	struct gendisk  *gd;
}RAMHD_DEV;

char *sdisk[RAMHD_MAX_DEVICE];

/* export the ramhd base block for use of ext4tap kmodule */
char *get_ramhd_mq_base(void)
{
	return sdisk[0];
}
EXPORT_SYMBOL_GPL(get_ramhd_mq_base);

static RAMHD_DEV *rdev[RAMHD_MAX_DEVICE];

static dev_t ramhd_mq_major;
static void ramhd_mq_space_clean(void);

/* allocate the memory space as the disk backend storage */
static int ramhd_mq_space_init(void)
{
	int i;
	int err = 0;
	for(i = 0; i < RAMHD_MAX_DEVICE; i++){
		sdisk[i] = vmalloc(RAMHD_SIZE);
		if(!sdisk[i]){
			pr_err("%s vmalloc[%d] failed\n", __func__, i);
			err = -ENOMEM;
			goto err_out;
		}
		pr_info("sdisk[%d] = 0x%px\n", i, sdisk[i]);
		memset(sdisk[i], 0, RAMHD_SIZE);
	}

	return err;

err_out:
	ramhd_mq_space_clean();
	return err;
}

static void ramhd_mq_space_clean(void)
{
	int i;
	for(i = 0; i < RAMHD_MAX_DEVICE; i++){
		if (sdisk[i])
			vfree(sdisk[i]);
	}
}

static void clean_ramdev(void)
{
	int i;
	for(i = 0; i < RAMHD_MAX_DEVICE; i++){
		if(rdev[i])
			kfree(rdev[i]);
	}
}


static int alloc_ramdev(void)
{
	int i;
	for(i = 0; i < RAMHD_MAX_DEVICE; i++){
		rdev[i] = kzalloc(sizeof(RAMHD_DEV), GFP_KERNEL);
		if(!rdev[i])
			goto err_out;
	}
	return 0;

err_out:
	clean_ramdev();
	return -ENOMEM;
}

int ramhd_mq_open(struct block_device *bdev, fmode_t mode)
{
	return 0;
}

static int ramhd_mq_ioctl(struct block_device *bdev, fmode_t mode, unsigned int cmd, unsigned long arg)
{
	struct hd_geometry geo;

	switch(cmd) {
	case HDIO_GETGEO:
		geo.cylinders = RAMHD_CYLINDERS;
		geo.heads = RAMHD_HEADS;
		geo.sectors = RAMHD_SECTORS;
		geo.start = get_start_sect(bdev);
		if(copy_to_user((void *)arg, &geo, sizeof(geo)))
			return -EFAULT;

		return 0;
	}

	return -ENOTTY;
}

static struct block_device_operations ramhd_mq_fops =
{   
	.owner = THIS_MODULE,
	.open = ramhd_mq_open,
	.ioctl = ramhd_mq_ioctl,
};

static blk_status_t ramhd_mq_req_func (struct blk_mq_hw_ctx *hctx,
				const struct blk_mq_queue_data *bd)
{
	RAMHD_DEV *pdev;
	struct bio_vec bv;
	struct req_iterator iter;
	char *addr, *pData, *buffer;
	struct bio *bio;
	struct request *req = bd->rq;
	unsigned long start = blk_rq_pos(req); /* The start sector of the current request */
	unsigned int size;
	
	pdev = (RAMHD_DEV *)req->q->disk->private_data;
	pData = pdev->data;

	addr = pData + start * RAMHD_SECTOR_SIZE;
#ifdef BLK_DEBUG
	printk("Total sectors of current req:%d\n", blk_rq_sectors(req));
#endif
	blk_mq_start_request(req);
	/*
	 * Iterates each segment of the current request. the bios maybe merged by the I/O
	 * scheduler for the perf purpose, so the sectors are contiguous for the req after
	 * merged, but the backing pages of the bios is unnecessary contiguous, so we need
	 * to take care of each segment within the bio from current req...
         */
	rq_for_each_segment(bv, req, iter) {
		bio = iter.bio;
		size = bv.bv_len;
		buffer = page_address(bv.bv_page) + bv.bv_offset;
#ifdef BLK_DEBUG
		printk("current seg[sector:%lld] buffer: 0x%px, size = %u@offset %u\n", bio->bi_iter.bi_sector, buffer, size, bv.bv_offset);
#endif
		/* insert a TP here, pass the pointer of the data struct instead of the object (like 'bv') */
		trace_ramhd_mq_func(bio, &bv, buffer);
		if ((unsigned long)buffer % RAMHD_SECTOR_SIZE) {
			pr_err(RAMHD_NAME ": buffer %p not aligned\n", buffer);
			return BLK_STS_IOERR;
		}
		spin_lock_irq(&pdev->lock);
		if (rq_data_dir(req) == READ)
			memcpy(buffer, addr, size);
		else
			memcpy(addr, buffer, size);
		spin_unlock_irq(&pdev->lock);
		addr += size;
	}
	blk_mq_end_request(req, BLK_STS_OK);
	
	return BLK_STS_OK;
}

static void ramhd_mq_map_queues(struct blk_mq_tag_set *set)
{
	int type;

	for (type = 0; type < set->nr_maps; type++) {
		struct blk_mq_queue_map *map = &set->map[type];
		switch(type) {
		case HCTX_TYPE_DEFAULT:
			map->nr_queues = 3;
			map->queue_offset = 0;
			blk_mq_map_queues(map);
			break;
		case HCTX_TYPE_READ:
			map->nr_queues = 2;
			map->queue_offset = 3;
			blk_mq_map_queues(map);
			break;
		case HCTX_TYPE_POLL:
			map->nr_queues = 1;
			map->queue_offset = 5;
			blk_mq_map_queues(map);
			break;
		default:
			BUG();
		}
	}
}

static struct blk_mq_tag_set tag_set[RAMHD_MAX_DEVICE];
static const struct blk_mq_ops rdev_mq_ops = {
	.queue_rq = ramhd_mq_req_func,
	//.map_queues = ramhd_mq_map_queues,
};

static void check_hctxs(struct request_queue *q)
{
	int i, j, type;
	unsigned long index, m_cpu;
	unsigned int nr_queues, queue_offset;
	struct blk_mq_hw_ctx *hctx, *tmp;
	struct blk_mq_tag_set *set;

	pr_info("+%s+\n", __func__);
	spin_lock(&q->unused_hctx_lock);
	list_for_each_entry(tmp, &q->unused_hctx_list, hctx_list) {
		pr_info("tmp = 0x%px\n", tmp);
	}
	spin_unlock(&q->unused_hctx_lock);

	xa_for_each(&q->hctx_table, index, hctx) {
		pr_info("index = %lu, hctx->queue_num = %u\n", index, hctx->queue_num);
		for (i = 0; i < nr_cpu_ids; i++) {
			if (sbitmap_test_bit(&hctx->ctx_map, i))
				pr_info("cpu#%d set\n", i);
		}
	}
	pr_info("index = %lu, hctx = 0x%px\n", index, hctx);

	for (type = 0; type < q->tag_set->nr_maps; type++) {
		struct blk_mq_queue_map *map = &q->tag_set->map[type];
		for_each_possible_cpu(i) {
			m_cpu = map->mq_map[i];
			nr_queues = map->nr_queues;
			queue_offset = map->queue_offset;
			pr_info("cpu#%d --> hw_queue#%lu, nr_queues = %u, queue_offset = %u\n",
				i, m_cpu, nr_queues, queue_offset);
		}
	}

	set = q->tag_set;
	if (!set) {
		pr_err("tag set is NULL\n");
		return;
	}
	for (i = 0; i < set->nr_hw_queues; i++) {
		struct sbitmap_queue *bt;
		struct blk_mq_tags *tags;
		tags = set->tags[i];
		bt = &tags->bitmap_tags;
		pr_info("hwctx[%d], nr_tags = %u, nr_resv_tags = %u\n", i, tags->nr_tags, tags->nr_reserved_tags); 
		//pr_info("bitmap policy is %s\n", bt->sb.round_robin ? "round_robin" : "!round_robin");
		for (j = 0; j < set->queue_depth; j++)
			pr_info("tags->static_rqs[%2d] = 0x%px, tags->rqs[%2d] = 0x%px\n",
				j, tags->static_rqs[j], j, tags->rqs[j]);
	}
}

static int __init ramhd_mq_init(void)
{
	int i, error = 0;
	struct request_queue *q;
	
	ramhd_mq_space_init();
	alloc_ramdev();

	ramhd_mq_major = register_blkdev(0, RAMHD_NAME);
	if (ramhd_mq_major < 0) {
		pr_err("register_blkdev failed: %d\n", error);
		return ramhd_mq_major;
	}

	for(i = 0; i < RAMHD_MAX_DEVICE; i++)
	{
		rdev[i]->data = sdisk[i]; 

		spin_lock_init(&rdev[i]->lock);
		/* setup a single hw queue and with queue_depth = 32 */
		tag_set[i].ops = &rdev_mq_ops;
		tag_set[i].nr_hw_queues = 1;
		tag_set[i].nr_maps = 1;
		tag_set[i].queue_depth = 4;
		tag_set[i].numa_node = NUMA_NO_NODE;
		tag_set[i].flags = BLK_MQ_F_SHOULD_MERGE;
		error = blk_mq_alloc_tag_set(&tag_set[i]);
		if (error) {
			pr_err("blk_mq_alloc_sq_tag_set failed: %d\n", error);
			goto unregister_blk_out;
		}
		rdev[i]->gd = blk_mq_alloc_disk(&tag_set[i], NULL);
		if (!rdev[i]->gd) {
			pr_err("blk_mq_alloc_disk failed\n");
			error = -1;
			goto free_tag_out;
		}
		q = rdev[i]->gd->queue;
		BUG_ON(!q);
		check_hctxs(q);
#if defined(Q_NOMERGES)
		blk_queue_flag_set(QUEUE_FLAG_NOMERGES, rdev[i]->gd->queue);
#endif
		rdev[i]->gd->fops = &ramhd_mq_fops;
		rdev[i]->gd->private_data = rdev[i];
		sprintf(rdev[i]->gd->disk_name, "ramsd%c", 'a' + i);
		set_capacity(rdev[i]->gd, RAMHD_SECTOR_TOTAL);
		error = add_disk(rdev[i]->gd);
		if (error)
			put_disk(rdev[i]->gd);
	}

	return error;

free_tag_out:
	blk_mq_free_tag_set(&tag_set[i]);
unregister_blk_out:
	unregister_blkdev(ramhd_mq_major,RAMHD_NAME);

	return error;
}

static void __exit ramhd_mq_exit(void)
{
	int i;
	for(i = 0; i < RAMHD_MAX_DEVICE; i++)
	{
		del_gendisk(rdev[i]->gd);
		put_disk(rdev[i]->gd);     
		blk_mq_free_tag_set(&tag_set[i]);
	}
	unregister_blkdev(ramhd_mq_major,RAMHD_NAME);  
	clean_ramdev();
	ramhd_mq_space_clean();  
}

module_init(ramhd_mq_init);
module_exit(ramhd_mq_exit);

MODULE_AUTHOR("xuesong.cxs@outlook.com");
MODULE_DESCRIPTION("Adapt to the new mq framework on Aug.12, 2020;Re-adapt on Dec.21, 2022");
MODULE_LICENSE("GPL");
