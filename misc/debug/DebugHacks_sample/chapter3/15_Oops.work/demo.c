#include <linux/module.h>

static __init int init_demo(void)
{
    *((int*)0x00) = 0x19760817;

    return 0;
}
module_init(init_demo);

static __exit void cleanup_demo(void)
{
}
module_exit(cleanup_demo);
MODULE_LICENSE("GPL");
