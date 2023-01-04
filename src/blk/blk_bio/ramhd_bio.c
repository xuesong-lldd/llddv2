/*
 * A simple bio-based block device, RAM as the underlying storage
 * device.
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

/* uncomment below line to use bio_for_each_bvec() instead */
/* #define PER_BVEC */

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

static dev_t ramhd_bio_major;

static void __ramhd_bio_make_request(struct bio *bio);

static int ramhd_bio_space_init(void)
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

static void ramhd_bio_space_clean(void)
{
	int i;
	for(i = 0; i < RAMHD_MAX_DEVICE; i++){
		vfree(sdisk[i]);
	}
}

static int ramhd_bio_open(struct block_device *bdev, fmode_t mode)
{
	return 0;
}

static int ramhd_bio_ioctl(struct block_device *bdev, fmode_t mode, unsigned cmd, unsigned long arg)
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

static void ramhd_bio_submit_bio(struct bio *bio)
{
	__ramhd_bio_make_request(bio);
}

static struct block_device_operations ramhd_bio_fops =
{
	.owner = THIS_MODULE,
	.open = ramhd_bio_open,
	.submit_bio = ramhd_bio_submit_bio,
	.ioctl = ramhd_bio_ioctl,
};

static void __ramhd_bio_make_request(struct bio *bio)
{
	char *pRHdata;
	void *pBuffer;
	struct bio_vec bvec;
	struct bvec_iter iter;

	RAMHD_DEV *pdev = bio->bi_bdev->bd_disk->private_data;
	if (bio_end_sector(bio) > get_capacity(bio->bi_bdev->bd_disk))
		goto io_error;

	pRHdata = pdev->data + (bio->bi_iter.bi_sector * RAMHD_SECTOR_SIZE);
#if defined(PER_BVEC)
	bio_for_each_bvec(bvec, bio, iter) {
#else
	bio_for_each_segment(bvec, bio, iter) {
#endif
		pBuffer = kmap_atomic(bvec.bv_page) + bvec.bv_offset;
		switch(bio_data_dir(bio))
		{
			case READ:
				memcpy_flushcache(pBuffer, pRHdata, bvec.bv_len);
				flush_dcache_page(bvec.bv_page);
				break;
			case WRITE:
				flush_dcache_page(bvec.bv_page);
				memcpy_flushcache(pRHdata, pBuffer, bvec.bv_len);
				break;
			default:
				kunmap_atomic(pBuffer);
				goto io_error;
		}
		kunmap_atomic(pBuffer);
		pRHdata += bvec.bv_len;
	}
	bio_endio(bio);
	return;
io_error:
	bio_io_error(bio);
	return;
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

static int __init ramhd_bio_init(void)
{
	int i;
	int err;
	struct request_queue *rq;

	err = ramhd_bio_space_init();
	if(err)
		return err;

	alloc_ramdev();

	ramhd_bio_major = register_blkdev(0, RAMHD_NAME);

	for(i = 0; i < RAMHD_MAX_DEVICE; i++) {  
		rdev[i]->data = sdisk[i];
		rdev[i]->gd = blk_alloc_disk(NUMA_NO_NODE);
		BUG_ON(!rdev[i]->gd);
		rq = rdev[i]->gd->queue;
		rq->nr_requests = 64;
		rdev[i]->gd->fops = &ramhd_bio_fops;
		rdev[i]->gd->private_data = rdev[i];
		sprintf(rdev[i]->gd->disk_name, "ramhd%c", 'a'+i);
		set_capacity(rdev[i]->gd, RAMHD_SECTOR_TOTAL);
		blk_queue_flag_set(QUEUE_FLAG_NONROT, rdev[i]->gd->queue);
		blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, rdev[i]->gd->queue);
		err = add_disk(rdev[i]->gd);
		if (err) {
			pr_err("[%d] device_add_disk() failed: %d\n", i, err);
			return err;
		}
	}
	return 0;
}

static void __exit ramhd_bio_exit(void)
{
	int i;

	for(i = 0; i < RAMHD_MAX_DEVICE; i++) {
		del_gendisk(rdev[i]->gd);
		put_disk(rdev[i]->gd);
	} 
	unregister_blkdev(ramhd_bio_major,RAMHD_NAME);
	clean_ramdev();
	ramhd_bio_space_clean();   
}

module_init(ramhd_bio_init);
module_exit(ramhd_bio_exit);

MODULE_AUTHOR("xuesong.cxs@outlook.com");
MODULE_DESCRIPTION("The bio-based ramdisk driver");
MODULE_LICENSE("GPL");

