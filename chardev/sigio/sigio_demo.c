#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/mm.h>

static struct cdev *g_cdev;
static dev_t ndev;
static struct class *fa_cls;
static struct device *fa_dev;

static unsigned long g_flag = 0;
static struct fasync_struct *sigio_list;

/* mmap */
struct page *g_buff_page;
unsigned long *g_vbuff;

static ssize_t read_flag(struct device *dev, struct device_attribute *attr, char *buf)
{
	size_t count = 0;
	count += sprintf(&buf[count], "%lu\n", g_flag);

	return count;
}

static ssize_t write_flag(struct device *dev, struct device_attribute *attr, 
		const char *buf, size_t count)
{
	g_flag = buf[0] - '0';

	if (g_vbuff)
		*g_vbuff = 0xdeadbeef;

	/* send SIGIO to all the processes with FASYNC bit */
	kill_fasync(&sigio_list, SIGIO, POLL_IN);

	return count;
}

static struct device_attribute flag_attr = 
	__ATTR(g_flag, S_IRUGO|S_IWUSR, read_flag, write_flag);

static int fa_open(struct inode *inode, struct file *filp)
{
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

static int fa_async(int fd, struct file *filp, int onflag)
{
	return fasync_helper(fd, filp, onflag, &sigio_list);
}

static struct file_operations ops = {
	.owner = THIS_MODULE,
	.open = fa_open,
	.mmap = fa_map,
	.fasync = fa_async,
};

static int sigio_demo_init(void)
{
	int ret = 0;

	printk("++%s++\n", __func__);
	/* init the mmap memory space */
	g_buff_page = alloc_page(GFP_KERNEL);
	if (!g_buff_page) {
		pr_err("alloc_page failed\n");
		return PTR_ERR(g_buff_page);
	}
	g_vbuff = page_address(g_buff_page);

	ret = alloc_chrdev_region(&ndev, 0, 1, "fa_dev");
	if (ret < 0) {
		printk("alloc_chrdev_region() failed: %d\n", ret);
		return ret;
	}

	printk("{major, minor} = {%d, %d}\n", MAJOR(ndev), MINOR(ndev));

	g_cdev = cdev_alloc();
	cdev_init(g_cdev, &ops);
	g_cdev->owner = THIS_MODULE;
	cdev_add(g_cdev, ndev, 1);

	fa_cls = class_create(THIS_MODULE, "fa_dev");
	if (IS_ERR(fa_cls)) {
		printk("class_create() failed\n");
		/* skip the teardown process just as a demo */
		return PTR_ERR(fa_cls);
	}

	fa_dev = device_create(fa_cls, NULL, ndev, NULL, "fa_dev");
	if (IS_ERR(fa_dev)) {
		printk("device_create() failed\n");
		return PTR_ERR(fa_dev);
	}

	/* create a sys file named as 'flag' */
	ret = device_create_file(fa_dev, &flag_attr);

	return 0;
}

static void sigio_demo_exit(void)
{
	printk("--%s--\n", __func__);

	device_remove_file(fa_dev, &flag_attr);
	device_destroy(fa_cls, ndev);
	class_destroy(fa_cls);
	cdev_del(g_cdev);
	unregister_chrdev_region(ndev, 1);

	if (g_buff_page) {
		__free_page(g_buff_page);
		g_buff_page = NULL;
	}

	return;
}

module_init(sigio_demo_init);
module_exit(sigio_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
