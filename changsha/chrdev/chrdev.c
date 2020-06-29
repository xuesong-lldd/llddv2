#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/poll.h>

static struct cdev *g_cdev;

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

static dev_t ndev;

static struct file_operations ops = {
	.owner = THIS_MODULE,
	.open = fa_open,
	.read = fa_read,
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
	/* potential kmem leak
	 * should comment out the 'cdev_init(...)', then uses below:
	 * g_cdev->ops = &ops;
	 * g_cdev->owner = THIS_MODULE;
	 */
	cdev_init(g_cdev, &ops);
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

