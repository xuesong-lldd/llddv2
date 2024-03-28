/*
 * #insmod ramhd_mq.ko
 * #fdisk /dev/ramsda
 * #mkfs.ext4 /dev/ramsda1
 * #mount /dev/ramsda1 /mnt
 *
 * Adapt the raw kernel module into a platform device driver on Dec.12, 2023
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
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <asm/uaccess.h>

//#define CREATE_TRACE_POINTS
//#include "pf_ramdisk.h"

#define RAMHD_NAME              "ramsd"
#define RAMHD_MAX_DEVICE        1
#define RAMHD_MAX_PARTITIONS    2

#define RAMHD_SECTOR_SIZE       512

#define RAMHD_SECTORS           64
#define RAMHD_HEADS             8
#define RAMHD_CYLINDERS         128

#define RAMHD_SECTOR_TOTAL      (RAMHD_SECTORS * RAMHD_HEADS * RAMHD_CYLINDERS)
#define RAMHD_SIZE              (RAMHD_SECTOR_SIZE * RAMHD_SECTOR_TOTAL) /* 32-MB */

typedef struct{
	char   *data;
	struct request_queue *queue;
	spinlock_t      lock;
	struct gendisk  *gd;
}RAMHD_DEV;

char *sdisk[RAMHD_MAX_DEVICE];

static const struct of_device_id pf_ramdisk_dt_match[] = {
    { .compatible = "brcm,bcm2711-ramdisk", NULL },
    { .compatible = "arm,armv8-ramdisk", NULL },
    {}
};

/* export the ramhd base block for use of ext4tap kmodule */
char *get_ramhd_base(void)
{
	return sdisk[0];
}
EXPORT_SYMBOL_GPL(get_ramhd_base);

static RAMHD_DEV *rdev[RAMHD_MAX_DEVICE];

static dev_t ramhd_major;
static void ramhd_space_clean(void);

/* allocate the memory space as the disk backend storage */
static int ramhd_space_init(void)
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
	ramhd_space_clean();
	return err;
}

static void ramhd_space_clean(void)
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

int ramhd_open(struct block_device *bdev, fmode_t mode)
{
	return 0;
}

static int ramhd_ioctl(struct block_device *bdev, fmode_t mode, unsigned int cmd, unsigned long arg)
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

static struct block_device_operations ramhd_fops =
{   
	.owner = THIS_MODULE,
	.open = ramhd_open,
	.ioctl = ramhd_ioctl,
};

static blk_status_t ramhd_req_func (struct blk_mq_hw_ctx *hctx,
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
	printk("Total sectors of current req:%d\n", blk_rq_sectors(req));
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
		printk("current seg[sector:%lld] buffer: 0x%px, size = %u@offset %u\n", bio->bi_iter.bi_sector, buffer, size, bv.bv_offset);
		/* insert a TP here, pass the pointer of the data struct instead of the object (like 'bv') */
		//trace_ramhd_req_func(bio, &bv, buffer);
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

static struct blk_mq_tag_set tag_set[RAMHD_MAX_DEVICE];
static const struct blk_mq_ops rdev_mq_ops = {
	.queue_rq = ramhd_req_func,
};

static int pf_ramdisk_probe(struct platform_device *pdev)
{
	int i, error = 0;

    dev_info(&pdev->dev, "+pf_ramdisk_probe+\n");
	error = ramhd_space_init();
	if (error)
		goto err_out;

	error = alloc_ramdev();
	if (error)
		goto err_out;

	ramhd_major = register_blkdev(0, RAMHD_NAME);
	if (ramhd_major < 0) {
		pr_err("register_blkdev failed: %d\n", error);
		goto err_out;
	}

	for(i = 0; i < RAMHD_MAX_DEVICE; i++)
	{
		rdev[i]->data = sdisk[i]; 

		spin_lock_init(&rdev[i]->lock);
		/* setup a single hw queue and with queue_depth = 32 */
		tag_set[i].ops = &rdev_mq_ops;
		tag_set[i].nr_hw_queues = 1;
		tag_set[i].nr_maps = 1;
		tag_set[i].queue_depth = 32;
		tag_set[i].numa_node = NUMA_NO_NODE;
		tag_set[i].flags = BLK_MQ_F_SHOULD_MERGE;
		error = blk_mq_alloc_tag_set(&tag_set[i]);
		if (error) {
			pr_err("blk_mq_alloc_sq_tag_set failed: %d\n", error);
			goto err_out;
		}

		rdev[i]->gd = blk_mq_alloc_disk(&tag_set[i], NULL);
		if (!rdev[i]->gd) {
			pr_err("blk_mq_alloc_disk failed\n");
			error = -1;
			goto err_out;
		}
		rdev[i]->gd->fops = &ramhd_fops;
		rdev[i]->gd->private_data = rdev[i];
		sprintf(rdev[i]->gd->disk_name, "ramsd%c", 'a' + i);
		set_capacity(rdev[i]->gd, RAMHD_SECTOR_TOTAL);
		error = add_disk(rdev[i]->gd);
		if (error)
			put_disk(rdev[i]->gd);
	}

	return error;

err_out:
	return error;
}

static int pf_ramdisk_remove(struct platform_device *pdev)
{
	int i;

    dev_info(&pdev->dev, "+pf_ramdisk_remove+\n");
	for(i = 0; i < RAMHD_MAX_DEVICE; i++) {
		del_gendisk(rdev[i]->gd);
		put_disk(rdev[i]->gd);     
		blk_mq_free_tag_set(&tag_set[i]);
	}
	unregister_blkdev(ramhd_major,RAMHD_NAME);  
	clean_ramdev();
	ramhd_space_clean();  
    return 0;
}

static struct platform_driver pf_ramdisk_driver = {
    .driver = {
        .name = "pf-ramdisk",
        .probe_type = PROBE_PREFER_ASYNCHRONOUS,
        .of_match_table = pf_ramdisk_dt_match,
    },
    .probe = pf_ramdisk_probe,
    .remove = pf_ramdisk_remove,
};

module_platform_driver(pf_ramdisk_driver);

MODULE_AUTHOR("xuesong.cxs@outlook.com");
MODULE_DESCRIPTION("Re-impl it in form of platform driver on Dec.12, 2023; Adapt to the new mq framework on Aug.12, 2020");
MODULE_LICENSE("GPL");
