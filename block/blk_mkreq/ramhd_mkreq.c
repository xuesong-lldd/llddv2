/*
 * A very simple ram-based block device:
 * Usage:
 * 1. fdisk /dev/ramhda
 * 2. mkfs.ext4 /dev/ramhda1
 * 3. mount /dev/ramhda1 /mnt
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
#include <linux/blk_types.h>

#define RAMHD_NAME              "ramhd"
#define RAMHD_MAX_DEVICE        2
#define RAMHD_MAX_PARTITIONS    4

#define RAMHD_SECTOR_SIZE       512
#define RAMHD_SECTORS           64
#define RAMHD_HEADS             16
#define RAMHD_CYLINDERS         512

#define RAMHD_SECTOR_TOTAL      (RAMHD_SECTORS * RAMHD_HEADS * RAMHD_CYLINDERS)
#define RAMHD_SIZE              (RAMHD_SECTOR_SIZE * RAMHD_SECTOR_TOTAL) /* 32MB */

typedef struct{
	unsigned char *data;
	struct request_queue *queue;
	struct gendisk  *gd;
}RAMHD_DEV;

static char *sdisk[RAMHD_MAX_DEVICE] = {NULL,};
static RAMHD_DEV *rdev[RAMHD_MAX_DEVICE] = {NULL,};

static dev_t ramhd_major;

static int ramhd_space_init(void)
{
	int i;
	int err = 0;
	for(i = 0; i < RAMHD_MAX_DEVICE; i++){
		sdisk[i] = vmalloc(RAMHD_SIZE);
		if(!sdisk[i]){
			printk("vmalloc failed!");
			err = -ENOMEM;
			return err;
		}
		memset(sdisk[i], 0, RAMHD_SIZE);
	}

	return err;
}

static void ramhd_space_clean(void)
{
	int i;
	for(i = 0; i < RAMHD_MAX_DEVICE; i++){
		vfree(sdisk[i]);
	}
}

static int ramhd_open(struct block_device *bdev, fmode_t mode)
{
	return 0;
}

static int ramhd_ioctl(struct block_device *bdev, fmode_t mode, unsigned cmd, unsigned long arg)
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

static blk_qc_t ramhd_make_request(struct request_queue *q, struct bio *bio)
{
	char *pRHdata;
	void *pBuffer;
	struct bio_vec bvec;
	struct bvec_iter iter;

	RAMHD_DEV *pdev = bio->bi_disk->private_data;
	if (bio_end_sector(bio) > get_capacity(bio->bi_disk))
		goto io_error;

	pRHdata = pdev->data + (bio->bi_iter.bi_sector * RAMHD_SECTOR_SIZE);

	bio_for_each_segment(bvec, bio, iter) {
		pBuffer = kmap_atomic(bvec.bv_page) + bvec.bv_offset;
		switch(bio_data_dir(bio))
		{
			case READ:
				memcpy(pBuffer, pRHdata, bvec.bv_len);
				flush_dcache_page(bvec.bv_page);
				break;
			case WRITE:
				flush_dcache_page(bvec.bv_page);
				memcpy(pRHdata, pBuffer, bvec.bv_len);
				break;
			default:
				kunmap_atomic(pBuffer);
				goto io_error;
		}
		kunmap_atomic(pBuffer);
		pRHdata += bvec.bv_len;
	}

	bio_endio(bio);
	return BLK_QC_T_NONE;
io_error:
	bio_io_error(bio);
	return BLK_QC_T_NONE;
}

static int alloc_ramdev(void)
{
	int i;
	for(i = 0; i < RAMHD_MAX_DEVICE; i++){
		rdev[i] = kzalloc(sizeof(RAMHD_DEV), GFP_KERNEL);
		if(!rdev[i])
			return -ENOMEM;
	}
	return 0;
}

static void clean_ramdev(void)
{
	int i;
	for(i = 0; i < RAMHD_MAX_DEVICE; i++){
		if(rdev[i])
			kfree(rdev[i]);
	}   
}       

static int __init ramhd_init(void)
{
	int i;
	int err;

	err = ramhd_space_init();
	if(err)
		return err;
	alloc_ramdev();

	ramhd_major = register_blkdev(0, RAMHD_NAME);

	for(i = 0; i < RAMHD_MAX_DEVICE; i++)
	{  
		rdev[i]->data = sdisk[i];
		rdev[i]->queue = blk_alloc_queue(GFP_KERNEL);
		blk_queue_make_request(rdev[i]->queue, ramhd_make_request);
		rdev[i]->gd = alloc_disk(RAMHD_MAX_PARTITIONS);
		rdev[i]->gd->major = ramhd_major;
		rdev[i]->gd->first_minor = i * RAMHD_MAX_PARTITIONS;
		rdev[i]->gd->fops = &ramhd_fops;
		rdev[i]->gd->queue = rdev[i]->queue;
		rdev[i]->gd->private_data = rdev[i];
		sprintf(rdev[i]->gd->disk_name, "ramhd%c", 'a'+i);
		rdev[i]->gd->flags |= GENHD_FL_SUPPRESS_PARTITION_INFO;
		set_capacity(rdev[i]->gd, RAMHD_SECTOR_TOTAL);
		add_disk(rdev[i]->gd);
	}
	return 0;
}

static void __exit ramhd_exit(void)
{
	int i;

	for(i = 0; i < RAMHD_MAX_DEVICE; i++)
	{
		del_gendisk(rdev[i]->gd);
		put_disk(rdev[i]->gd);
		blk_cleanup_queue(rdev[i]->queue);  
	} 
	clean_ramdev();
	ramhd_space_clean();
	unregister_blkdev(ramhd_major,RAMHD_NAME);    
}

module_init(ramhd_init);
module_exit(ramhd_exit);

MODULE_AUTHOR("dennis chen @AMDLinuxFGL");
MODULE_DESCRIPTION("The ramdisk implementation with request function");
MODULE_LICENSE("GPL");

