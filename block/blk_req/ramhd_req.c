/*
 * #insmod ramhd_req.ko
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

#define CREATE_TRACE_POINTS
#include "ramhd_req.h"

#define RAMHD_NAME              "ramsd"
#define RAMHD_MAX_DEVICE        1
#define RAMHD_MAX_PARTITIONS    2

#define RAMHD_SECTOR_SIZE       512

#define RAMHD_SECTORS           64
#define RAMHD_HEADS             8
#define RAMHD_CYLINDERS         512

#define RAMHD_SECTOR_TOTAL      (RAMHD_SECTORS * RAMHD_HEADS * RAMHD_CYLINDERS)
#define RAMHD_SIZE              (RAMHD_SECTOR_SIZE * RAMHD_SECTOR_TOTAL) /* 128-MB */


typedef struct{
	char   *data;
	struct request_queue *queue;
	spinlock_t      lock;
	struct gendisk  *gd;
}RAMHD_DEV;

char *sdisk[RAMHD_MAX_DEVICE];

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

	switch(cmd)
	{
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
/*
	struct request *req;
	RAMHD_DEV *pdev;
	char *pData;
	unsigned long addr, size, start;
	req = bd->rq;
	while (req) {
		start = blk_rq_pos(req); // The sector cursor of the current request
		pdev = (RAMHD_DEV *)req->rq_disk->private_data;
		pData = pdev->data;
		addr = (unsigned long)pData + start * RAMHD_SECTOR_SIZE;
		size = blk_rq_cur_bytes(req);
		if (rq_data_dir(req) == READ)
			memcpy(req->buffer, (char *)addr, size);
		else
			memcpy((char *)addr, req->buffer, size);

		if(!__blk_end_request_cur(req, 0))
			req = blk_fetch_request(q);
	}
*/
	RAMHD_DEV *pdev;
	struct bio_vec bv;
	struct req_iterator iter;
	char *addr, *pData, *buffer;
	struct bio *bio;
	struct request *req = bd->rq;
	unsigned long start = blk_rq_pos(req); /* The start sector of the current request */
	unsigned int size;
	
	pdev = (RAMHD_DEV *)req->rq_disk->private_data;
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
		trace_ramhd_req_func(bio, &bv, buffer);
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

int ramhd_init(void)
{
	int i;
	ramhd_space_init();
	alloc_ramdev();

	ramhd_major = register_blkdev(0, RAMHD_NAME);

	for(i = 0; i < RAMHD_MAX_DEVICE; i++)
	{
		rdev[i]->data = sdisk[i]; 
		rdev[i]->gd = alloc_disk(RAMHD_MAX_PARTITIONS);
		spin_lock_init(&rdev[i]->lock);
		/* setup a single hw queue and with queue_depth = 32 */
		rdev[i]->queue = blk_mq_init_sq_queue(&tag_set[i], &rdev_mq_ops, 32,
					BLK_MQ_F_SHOULD_MERGE);;
		rdev[i]->gd->major = ramhd_major;
		rdev[i]->gd->first_minor = i * RAMHD_MAX_PARTITIONS;
		rdev[i]->gd->fops = &ramhd_fops;
		rdev[i]->gd->queue = rdev[i]->queue;
		rdev[i]->gd->private_data = rdev[i];
		sprintf(rdev[i]->gd->disk_name, "ramsd%c", 'a' + i);
		set_capacity(rdev[i]->gd, RAMHD_SECTOR_TOTAL);
		add_disk(rdev[i]->gd);
	}

	return 0;
}

void ramhd_exit(void)
{
	int i;
	for(i = 0; i < RAMHD_MAX_DEVICE; i++)
	{
		del_gendisk(rdev[i]->gd);
		put_disk(rdev[i]->gd);     
		blk_cleanup_queue(rdev[i]->queue);  
		blk_mq_free_tag_set(&tag_set[i]);
	}
	unregister_blkdev(ramhd_major,RAMHD_NAME);  
	clean_ramdev();
	ramhd_space_clean();  
}

module_init(ramhd_init);
module_exit(ramhd_exit);

MODULE_AUTHOR("dennis chen @ AMDLinuxFGL");
MODULE_DESCRIPTION("The ramdisk implementation with request function; Adapt to the new mq framework on Aug.12, 2020");
MODULE_LICENSE("GPL");

