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

#define RAMHD_NAME              "ramsd"
#define RAMHD_MAX_DEVICE        2
#define RAMHD_MAX_PARTITIONS    4

#define RAMHD_SECTOR_SIZE       512
#define RAMHD_SECTORS           16
#define RAMHD_HEADS             4
#define RAMHD_CYLINDERS         256

#define RAMHD_SECTOR_TOTAL      (RAMHD_SECTORS * RAMHD_HEADS * RAMHD_CYLINDERS)
#define RAMHD_SIZE              (RAMHD_SECTOR_SIZE * RAMHD_SECTOR_TOTAL) //8MB

typedef struct{
	unsigned char   *data;
	struct request_queue *queue;
	spinlock_t      lock;
	struct gendisk  *gd;
}RAMHD_DEV;

static char *sdisk[RAMHD_MAX_DEVICE];
static RAMHD_DEV *rdev[RAMHD_MAX_DEVICE];

static dev_t ramhd_major;

static int ramhd_space_init(void)
{
	int i;
	int err = 0;
	for(i = 0; i < RAMHD_MAX_DEVICE; i++){
		sdisk[i] = vmalloc(RAMHD_SIZE);
		if(!sdisk[i]){
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

int ramhd_open(struct block_device *bdev, fmode_t mode)
{
	return 0;
}

void ramhd_release(struct gendisk *gd, fmode_t mode)
{   
	return;
}

static int ramhd_ioctl(struct block_device *bdev, fmode_t mode, unsigned int cmd, unsigned long arg)
{
	int err;
	struct hd_geometry geo;

	switch(cmd)
	{
		case HDIO_GETGEO:
			err = !access_ok(arg, sizeof(geo));
			if(err) return -EFAULT;

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
	.release = ramhd_release,
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
	unsigned long addr;
	char *pData;
	void *buffer;
	struct request *req = bd->rq;
	unsigned long start = blk_rq_pos(req); // The sector cursor of the current request
	unsigned long size  = blk_rq_cur_bytes(req);
	
	pdev = (RAMHD_DEV *)req->rq_disk->private_data;
	pData = pdev->data;
	addr = (unsigned long)pData + start * RAMHD_SECTOR_SIZE;
	buffer = bio_data(req->bio);

	/* 
	 * the operaion for the real device is to insert the req into a list,
         * and handle them in a tasklet or sth like that...
	 */  
	blk_mq_start_request(req);

	if (start + size > RAMHD_SIZE) {
		pr_err(RAMHD_NAME ": bad access: block=%llu, "
		       "count=%u\n",
		       (unsigned long long)blk_rq_pos(req),
		       blk_rq_cur_sectors(req));
		return BLK_STS_IOERR;
	}

	spin_lock_irq(&pdev->lock);
	if (rq_data_dir(req) == READ)
		memcpy(buffer, (char *)addr, size);
	else
		memcpy((char *)addr, buffer, size);
	spin_unlock_irq(&pdev->lock);

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
		rdev[i]->queue = blk_mq_init_sq_queue(&tag_set[i], &rdev_mq_ops, 16,
					BLK_MQ_F_SHOULD_MERGE);;
		rdev[i]->gd->major = ramhd_major;
		rdev[i]->gd->first_minor = i * RAMHD_MAX_PARTITIONS;
		rdev[i]->gd->fops = &ramhd_fops;
		rdev[i]->gd->queue = rdev[i]->queue;
		rdev[i]->gd->private_data = rdev[i];
		sprintf(rdev[i]->gd->disk_name, "ramsd%c", 'a'+i);
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
MODULE_DESCRIPTION("The ramdisk implementation with request function");
MODULE_LICENSE("GPL");

