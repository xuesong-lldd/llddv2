#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/poll.h>

#include "chrdev_ioctl_def.h"

static struct cdev *g_cdev;

struct fdt_header {
	u32 magic;
	u32 totalsize;
	u32 off_dt_struct;
	u32 off_dt_strings;
	u32 off_mem_rsvmap;
	u32 version;
	u32 last_comp_version;
	u32 boot_cpuid_phys;
	u32 size_dt_strings;
	u32 size_dt_struct;
};

static int fa_open(struct inode *nod, struct file *filp)
{
	printk("+fa_open()\n");
	return 0;
}

ssize_t fa_read(struct file *filp, char *buf, size_t len, loff_t *lof)
{
	printk("+fa_read\n");
	return 0;
}

static int parse_dtb_file(unsigned long arg)
{
	int ret = 0;
	int dtb_fd;
	void *hdr;
	loff_t size;
	struct fdt_header *fh;

	copy_from_user(&dtb_fd, (int __user *)arg, sizeof(int));
	pr_info("dtb_fd = %d\n", dtb_fd);
	ret = kernel_read_file_from_fd(dtb_fd, &hdr, &size, INT_MAX, 0);
	if (ret) {
		pr_err("kernel_read_file_from_fd() failed: %d\n", ret);
		return ret;
	}

	fh = (struct fdt_header *)hdr;
	pr_info("magic = 0x%x\n", be32_to_cpu(fh->magic));
	return ret;
}

static long dtb_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
	int ret;

	switch (cmd) {
		case IOCTL_GET_DTB_FD:
			ret = parse_dtb_file(arg);
			break;
		default:
			pr_err("invalid ioctl\n");
			ret = -EFAULT;
			break;
	}

	return ret; 
}

static dev_t ndev;

static struct file_operations ops = {
	.owner = THIS_MODULE,
	.open = fa_open,
	.read = fa_read,
	.unlocked_ioctl = dtb_ioctl,
};

static int chrdev_demo_init(void)
{
	int ret = 0;

	printk("++%s++\n", __func__);
	ret = alloc_chrdev_region(&ndev, 0, 1, "fa_dev");
	if (ret < 0) {
		printk("alloc_chrdev_region() failed: %d\n", ret);
		return ret;
	}

	printk("{major, minor} = {%d, %d}\n", MAJOR(ndev), MINOR(ndev));

	g_cdev = cdev_alloc();
	//cdev_init(g_cdev, &ops);
	g_cdev->ops = &ops;
	g_cdev->owner = THIS_MODULE;
	cdev_add(g_cdev, ndev, 1);

	return 0;
}

static void chrdev_demo_exit(void)
{
	printk("--%s--\n", __func__);

	cdev_del(g_cdev);
	unregister_chrdev_region(ndev, 1);

	return;
}

module_init(chrdev_demo_init);
module_exit(chrdev_demo_exit);

MODULE_LICENSE("GPL");

