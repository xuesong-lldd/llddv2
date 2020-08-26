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
#include <linux/of_device.h>

#define RAMHD_NAME              "ramsd"
#define RAMHD_MAX_DEVICE        1
#define RAMHD_MAX_PARTITIONS    2

typedef struct{
	char   *data;
	struct request_queue *queue;
	spinlock_t      lock;
	struct gendisk  *gd;
	u32	sector_sz;
}RAMHD_DEV;

typedef struct ramdisk_paras {
	u32 sector_sz;
	u32 heads;
	u32 sectors;
	u32 cylinders;
} ramdisk_paras_t;

static char *sdisk[RAMHD_MAX_DEVICE];
static RAMHD_DEV *rdev[RAMHD_MAX_DEVICE];

static dev_t ramhd_major;
static void ramhd_space_clean(void);

struct ramhd_of_plt_data {
	u32 model;
	u32 capacity;
};

static const struct ramhd_of_plt_data bcm2711_ramdisk_data = {
	.model = 0xdeadbeef,
	.capacity = 134217728 /* 128-MB */
};

static const struct of_device_id bcm2711_ramdisk_of_match[] = {
	{ .compatible = "brcm,fake-ramdisk-dev", .data = &bcm2711_ramdisk_data },
	{ .compatible = "arm, armv8-ramdisk" },
	{ }
};
MODULE_DEVICE_TABLE(of, bcm2711_ramdisk_of_match);

static int ramhd_space_init(ramdisk_paras_t *rp)
{
	int i;
	int err = 0;
	u32 ramhd_sz = rp->sector_sz * rp->sectors * rp->heads * rp->cylinders;

	for(i = 0; i < RAMHD_MAX_DEVICE; i++){
		sdisk[i] = vmalloc(ramhd_sz);
		if(!sdisk[i]){
			err = -ENOMEM;
			goto err_out;
		}
		memset(sdisk[i], 0, ramhd_sz);
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

static struct block_device_operations ramhd_fops =
{   
	.owner = THIS_MODULE,
	.open = ramhd_open,
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
	u32 sector_sz;
	struct request *req = bd->rq;
	unsigned long start = blk_rq_pos(req); /* The start sector of the current request */
	unsigned int size;
	
	pdev = (RAMHD_DEV *)req->rq_disk->private_data;
	pData = pdev->data;
	sector_sz = pdev->sector_sz;

	addr = pData + start * sector_sz;
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
		if ((unsigned long)buffer % sector_sz) {
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

static int ramhd_init(ramdisk_paras_t *rp)
{
	int i;
	ramhd_space_init(rp);
	alloc_ramdev();

	ramhd_major = register_blkdev(0, RAMHD_NAME);

	for(i = 0; i < RAMHD_MAX_DEVICE; i++)
	{
		rdev[i]->data = sdisk[i];
		rdev[i]->sector_sz = rp->sector_sz;
		rdev[i]->gd = alloc_disk(RAMHD_MAX_PARTITIONS);
		spin_lock_init(&rdev[i]->lock);
		rdev[i]->queue = blk_mq_init_sq_queue(&tag_set[i], &rdev_mq_ops, 2,
					BLK_MQ_F_SHOULD_MERGE);;
		rdev[i]->gd->major = ramhd_major;
		rdev[i]->gd->first_minor = i * RAMHD_MAX_PARTITIONS;
		rdev[i]->gd->fops = &ramhd_fops;
		rdev[i]->gd->queue = rdev[i]->queue;
		rdev[i]->gd->private_data = rdev[i];
		sprintf(rdev[i]->gd->disk_name, "ramsd%c", 'a' + i);
		set_capacity(rdev[i]->gd, rp->sectors * rp->heads * rp->cylinders);
		add_disk(rdev[i]->gd);
	}

	return 0;
}

static int parse_ramdisk_paras(struct device *dev, ramdisk_paras_t *rp)
{
	if (!dev || !dev_fwnode(dev)) {
		pr_err("invalid device tree blob\n");
		return -1;
	}

	if (device_property_read_u32(dev, "sector_sz", &rp->sector_sz) < 0) {
		dev_dbg(dev, "\"sector_sz\" property is missing...\n");
		return -1;
	}

	if (device_property_read_u32(dev, "heads", &rp->heads) < 0) {
		dev_dbg(dev, "\"heads\" property is missing...\n");
		return -1;
	}

	if (device_property_read_u32(dev, "sectors", &rp->sectors) < 0) {
		dev_dbg(dev, "\"sectors\" property is missing...\n");
		return -1;
	}

	if (device_property_read_u32(dev, "cylinders", &rp->cylinders) < 0) {
		dev_dbg(dev, "\"cylinders\" property is missing...\n");
		return -1;
	}

	pr_info("sector_sz = %d, H = %d, S = %d, C = %d\n", rp->sector_sz, rp->heads, rp->sectors, rp->cylinders);

	return 0;
}

static int ramhd_probe(struct platform_device *pdev)
{
	ramdisk_paras_t rp;
	struct device *dev = &pdev->dev;
	const struct ramhd_of_plt_data *rd_plt_data = NULL;

	rd_plt_data = device_get_match_data(dev);
	if (rd_plt_data->model != 0xdeadbeef) {
		pr_err("wrong mode detected by the driver, probe failed\n");
		return -1;
	}
	pr_info("+%s+: rd_plt_data = 0x%x\n", __func__, rd_plt_data->model);

	if (parse_ramdisk_paras(dev, &rp)) {
		pr_err("parse ramdisk parameters from DT failed\n");
		return -1;
	}

	return ramhd_init(&rp);
}

int ramhd_drv_unregister(struct platform_device *pdev)
{
	int i;
	pr_info("+%s+\n", __func__);
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

	return 0;
}

static struct platform_driver ramhd_of_driver = {
	.driver = {
		.name = "ramsda",
		.of_match_table = bcm2711_ramdisk_of_match,
	},
	.probe = ramhd_probe,
	.remove = ramhd_drv_unregister,
};

module_platform_driver(ramhd_of_driver);

MODULE_AUTHOR("dennis chen @ AMDLinuxFGL");
MODULE_DESCRIPTION("update the driver to be compatible with dt-base one");
MODULE_LICENSE("GPL");

