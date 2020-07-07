#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/slab.h>

/*
 * echo 4 for oops: #echo 4 > bomb
 * echo 5 for workqueue stall (need 'CONFIG_WQ_WATCHDOG=y' to enable wq watchdog)
 * echo 6 for spin_lock deadlock
 */

static struct kobject *parent = NULL;
static struct kobject *child = NULL;
static struct kset *c_kset = NULL;

static unsigned long g_oops_val = 1;

/* soft lockup */
atomic_t g_flag = ATOMIC_INIT(0);
struct workqueue_struct *g_my_wq = NULL;

/* spin_lock lockup */
spinlock_t g_spinlck;


struct work_struct work_a;
/* 
 * work_a waits for the g_flag becomes 1 to exit, but
 * g_flag can only be changed by work_b which can be
 * executed only when the work_a succeeds to exit, so
 * it's an infinite loop... The WQ WDG can be used
 * to detect this condition
 */
void work_a_func(struct work_struct *work)
{
        printk("+%s\n", __func__);
        do {
                cpu_relax();
        } while(!atomic_read(&g_flag));
        printk("-%s\n", __func__);
}

struct work_struct work_b;
void work_b_func(struct work_struct *work)
{
        printk("+%s\n", __func__);
        atomic_cmpxchg(&g_flag, 0, 1);
        printk("-%s\n", __func__);
}


static void do_oops(void)
{
	int *p = (int *)0x123456;
	*p = 0xdeadbeef;
}

/* workqueue stall */
static void do_workqueue_stall(void)
{
	queue_work(g_my_wq, &work_a);
        queue_work(g_my_wq, &work_b);
}

/* spinlock softlockup */
void do_spinlck_deadlock(void)
{
	printk("+%s\n", __func__);

	spin_lock(&g_spinlck);
        spin_lock(&g_spinlck);

	printk("-%s\n", __func__);
}

static ssize_t att_show(struct kobject *kobj, struct attribute *attr, char *buf)
{
	size_t count = 0;
    	count += sprintf(&buf[count], "%lu\n", g_oops_val);

	return count;  
}

static ssize_t att_store(struct kobject *kobj, struct attribute *attr, 
                                        const char *buf, size_t count)
{
    	g_oops_val = buf[0] - '0';
   	switch(g_oops_val){
    	case 0:
        	kobject_uevent(kobj, KOBJ_ADD);
        	break;  
    	case 1:
        	kobject_uevent(kobj, KOBJ_REMOVE);
        	break; 
    	case 2:
        	kobject_uevent(kobj, KOBJ_CHANGE);
        	break;
    	case 3:
        	kobject_uevent(kobj, KOBJ_MOVE);
        	break;
    	case 4:
		do_oops();
        	break;
    	case 5:
		do_workqueue_stall();
        	break;
    	case 6:
		do_spinlck_deadlock();
        	break;
    	case 7:
        	kobj->uevent_suppress = 0;
        	break;
    	}

    	return count;
}

static struct attribute cld_att = {
	.name = "bomb",
	.mode = S_IRUGO | S_IWUSR,
};

static const struct sysfs_ops att_ops = {
 	.show = att_show,
	.store = att_store,
};

static void oops_kobj_release(struct kobject *kobj)
{
	kfree(kobj);
}

static struct kobj_type cld_ktype = {
	.release = oops_kobj_release,
	.sysfs_ops = &att_ops,
};

static int kobj_demo_init(void)
{
 	int err;

	spin_lock_init(&g_spinlck);

	g_my_wq = alloc_workqueue("wq_softlockup_test", 0, 0);
        INIT_WORK(&work_a, work_a_func);
        INIT_WORK(&work_b, work_b_func);

 	parent = kobject_create_and_add("oops", NULL);
	if (!parent)
		return -ENOMEM;

    	child = kzalloc(sizeof(*child), GFP_KERNEL);
    	if(!child) {
		err = -ENOMEM;
		goto err_out;
	}

    	c_kset = kset_create_and_add("c_kset", NULL, parent);
    	if(!c_kset) {
		err = -ENOMEM;
        	goto err_out;
	}

    	child->kset = c_kset;

    	err = kobject_init_and_add(child, &cld_ktype, parent, "trigger");
    	if(err)
        	goto err_out;

    	err = sysfs_create_file(child, &cld_att);
	if (err)
		goto err_out;

	return 0;	
err_out:
	kset_unregister(c_kset);
	kobject_put(child);
    	kobject_put(parent);

    return err;
}

static void kobj_demo_exit(void)
{
    	sysfs_remove_file(child, &cld_att);

    	kset_unregister(c_kset);
	kobject_put(child);
    	kobject_put(parent);

	destroy_workqueue(g_my_wq);
}

module_init(kobj_demo_init);
module_exit(kobj_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
MODULE_DESCRIPTION("A simple kernel module to demo the kinds of kdump");
