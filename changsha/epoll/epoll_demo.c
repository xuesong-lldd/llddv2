#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/poll.h>

static struct cdev *g_cdev;
static dev_t ndev;
static struct class *fa_cls;
static struct device *fa_dev;

static unsigned long g_flag = 0;

DECLARE_WAIT_QUEUE_HEAD(fa_poll_waitq);

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
	
	if (g_flag > 0) {
		/* data for read is ready, so we wake up the task waitting on poll() */
		printk("data is ready for read for the device...\n");
		wake_up_all(&fa_poll_waitq);
	}

	return count;
}

static struct device_attribute flag_attr = 
	__ATTR(g_flag, S_IRUGO|S_IWUSR, read_flag, write_flag);

static int fa_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static __poll_t fa_poll(struct file *filp, struct poll_table_struct *pt)
{
	__poll_t mask = 0;
	
	poll_wait(filp, &fa_poll_waitq, pt);

	/* 
	 * g_flag = 0: no data available for read 
	 * g_flag > 0: data is available for read
	 */
	if (g_flag > 0) {
		mask |= EPOLLIN;
	}

	return mask;	
}

static struct file_operations ops = {
	.owner = THIS_MODULE,
	.open = fa_open,
	.poll = fa_poll,
};

static int poll_demo_init(void)
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

static void poll_demo_exit(void)
{
	printk("--%s--\n", __func__);

	device_remove_file(fa_dev, &flag_attr);
	device_destroy(fa_cls, ndev);
	class_destroy(fa_cls);
	cdev_del(g_cdev);
	unregister_chrdev_region(ndev, 1);
	
	return;
}

module_init(poll_demo_init);
module_exit(poll_demo_exit);

MODULE_LICENSE("GPL");

