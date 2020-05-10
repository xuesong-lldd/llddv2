#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/mm.h>

/*
 * demo of kmem_cache, see the result when we twist the order of kmem_cache_destroy()
 * and kmem_cache_free() if there's any obj there...
 */

struct tap_kmem_cache {
	unsigned int a; /* 4-byte */
	unsigned long b; /* 8-byte */
};

struct kmem_cache *kcp;
struct tap_kmem_cache *objp;

static int tap_kmem_cache_init(void)
{
	int err = 0;

	printk("++%s++\n", __func__);

#if 0
	kcp = kmem_cache_create(
		"tap_kmem_cache", sizeof(struct tap_kmem_cache), 0,
		SLAB_HWCACHE_ALIGN, NULL);
#endif
	kcp = KMEM_CACHE(tap_kmem_cache, SLAB_PANIC);
	if (!kcp) {
		pr_err("kmem_cache_create failed\n");
		err = -ENOMEM;
		goto err_out;
	}

	objp = kmem_cache_alloc(kcp, GFP_KERNEL);
	if (!objp) {
		pr_err("kmem_cache_alloc failed\n");
		err = -ENOMEM;
		goto err_out;
	}

	objp->a = 0x55aa55aa;
	objp->b = 0xdeadbeefdeadbeef;

#if 0
	pr_info("+kmem_cache_destroy\n");
	kmem_cache_destroy(kcp);

	kmem_cache_free(kcp, objp);
	kmem_cache_destroy(kcp);
	pr_info("-kmem_cache_destroy\n");
#endif
	return err;

err_out:
	if(kcp) {
		kmem_cache_destroy(kcp);
	}
	return err;
}

static void tap_kmem_cache_exit(void)
{
	printk("--%s--\n", __func__);

	pr_info("a = 0x%x, b = 0x%lx\n", objp->a, objp->b);
	if (objp) {
		pr_info("kmem_cache_free kobj\n");
		kmem_cache_free(kcp, objp);
	}
	if (kcp) {
		pr_info("kmem_cache_destroy\n");
		kmem_cache_destroy(kcp);
	}

	return;
}

module_init(tap_kmem_cache_init);
module_exit(tap_kmem_cache_exit);

MODULE_LICENSE("GPL");

