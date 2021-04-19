#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/mm.h>

static struct cdev *g_cdev;

struct page *g_buff_page;

static int fa_open(struct inode *nod, struct file *filp)
{
	pr_info("+fa_open()\n");

	return 0;
}

ssize_t fa_read(struct file *filp, char *buf, size_t len, loff_t *lof)
{
	pr_info("+fa_read\n");

	return 0;
}

static int fa_map(struct file *file, struct vm_area_struct *vma)
{
	unsigned long user_sz;

	pr_info("+fa_map\n");
	user_sz = vma->vm_end - vma->vm_start;
	return remap_pfn_range(vma, vma->vm_start, page_to_pfn(g_buff_page),
				user_sz, vma->vm_page_prot);
}

static long fa_ioctl(struct file *filp,
		unsigned int ioctl, unsigned long arg)
{
	pr_info("+fa_ioctl\n");
	pr_info("ioctl = 0x%x, arg = 0x%lx\n", ioctl, arg);

	return 0;
}

static dev_t ndev;

static struct file_operations ops = {
	.owner = THIS_MODULE,
	.open = fa_open,
	.read = fa_read,
	.unlocked_ioctl = fa_ioctl,
	.mmap = fa_map,
};

static int chrdev_demo_init(void)
{
	int ret = 0;
	unsigned long *v_buff;

	printk("++%s++\n", __func__);
	/* init the mmap memory space */
	g_buff_page = alloc_page(GFP_KERNEL);
	if (!g_buff_page) {
		pr_err("alloc_page failed\n");
		return PTR_ERR(g_buff_page);
	}
	v_buff = page_address(g_buff_page);
	*v_buff = 0xdeadbeef; /* magic number */

	ret = alloc_chrdev_region(&ndev, 0, 1, "fa_dev");
	if (ret < 0) {
		printk("alloc_chrdev_region() failed: %d\n", ret);
		return ret;
	}

	printk("{major, minor} = {%d, %d}\n", MAJOR(ndev), MINOR(ndev));
	g_cdev = cdev_alloc();
	//cdev_init(g_cdev, &ops); /* kmem leak */
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
	if (g_buff_page) {
		__free_page(g_buff_page);
		g_buff_page = NULL;
	}

	return;
}

module_init(chrdev_demo_init);
module_exit(chrdev_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
