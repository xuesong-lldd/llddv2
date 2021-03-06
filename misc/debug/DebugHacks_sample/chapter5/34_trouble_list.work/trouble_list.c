#include <linux/module.h>
#include <linux/kthread.h> // for kthread_run()
#include <linux/delay.h>   // for msleep()
#include <linux/list.h>    // for list
#include <linux/slab.h>    // for kmalloc()
#include <linux/spinlock_types.h>

/*
 * How to use this TP.
 * make -C <kernel source path> M=`pwd` modules
 * insmod trouble_list.ko
 * rmmod trouble_list
 */

struct k_trouble_list {
        struct list_head list;
        spinlock_t lock;
};

static struct k_trouble_list trouble = {
	.list = LIST_HEAD_INIT(trouble.list),
	.lock = __SPIN_LOCK_UNLOCKED(trouble.lock),
};

struct k_entry {
	struct list_head list;
};

static int list_add_thread(void *data)
{
	int i;

	do {
		spin_lock(&trouble.lock);
		for (i = 0; i < 100000; i++) {
			struct k_entry *entry;

			entry = kmalloc(sizeof(struct k_entry),GFP_ATOMIC);
			INIT_LIST_HEAD(&entry->list);
			list_add(&entry->list, &trouble.list);
		}
		spin_unlock(&trouble.lock);
		msleep(200);
	} while (!kthread_should_stop());

	return 0;
}

static int list_release_thread(void *data)
{
	do {
		spin_lock(&trouble.lock);
		while (!list_empty(&trouble.list)){
			struct k_entry *entry;

			entry = list_entry(trouble.list.next, struct k_entry, list);
			list_del(&entry->list);
			kfree(entry);
		}
		spin_unlock(&trouble.lock);
		msleep(100);
	} while (!kthread_should_stop());

	return 0;
}

static int list_del_thread(void *data)
{
	do {
		if (!list_empty(&trouble.list)){
			struct k_entry *entry;

			spin_lock(&trouble.lock);
			entry = list_entry(trouble.list.next, struct k_entry, list);
			list_del(&entry->list);
			kfree(entry);
			spin_unlock(&trouble.lock);
		}
		msleep(1);
	} while (!kthread_should_stop());

	return 0;
}

struct task_struct *kthread1;
struct task_struct *kthread2;
struct task_struct *kthread3;

static int __init trouble_list_init(void)
{
	kthread1 = kthread_run(list_add_thread, NULL, "list_add");
	kthread2 = kthread_run(list_release_thread, NULL, "list_release");
	kthread3 = kthread_run(list_del_thread, NULL, "list_del");

	return 0;
}

static void __exit trouble_list_exit(void)
{
	kthread_stop(kthread1);
	kthread_stop(kthread3);
	kthread_stop(kthread2);

        return;
}

module_init(trouble_list_init);
module_exit(trouble_list_exit);

MODULE_AUTHOR("Naohiro Ooiwa <nooiwa@miraclelinux.com>");
MODULE_DESCRIPTION("The test program for list corruption.");
MODULE_LICENSE("GPL");
