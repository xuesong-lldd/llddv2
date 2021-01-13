#include <linux/module.h>
#include <linux/kernel.h>
#include <uapi/linux/magic.h>

#include "ext4tap.h"

extern char *get_ramhd_base(void);

static void dump_ext4_sb(void)
{
	char *ext4_base;
	struct ext4_super_block *e4sb;
	struct ext4_group_desc *egd;

	char *p = get_ramhd_base();
	if (!p) {
		pr_err("get_ramhd_base() return NULL\n");
		return;
	}
	/* the first sector# of the ext4 partition is 2048 */
	ext4_base = p + 2048 * 512;
	e4sb = (struct ext4_super_block *)(ext4_base + 1024); /* Skip the group 0 padding bytes(1024) */
	if (EXT4_SUPER_MAGIC == le16_to_cpu(e4sb->s_magic)) {
		pr_info("Get the ext4 super block OK...size of SB = %ld\n", sizeof(struct ext4_super_block));
	} else {
		pr_info("Get the ext4 super block failed...\n");
		return;
	}
	pr_info("block size = %d\n", 1 << (le32_to_cpu(e4sb->s_log_block_size) + 10));
	pr_info("inode count = %d, blocks count = %d\n", le32_to_cpu(e4sb->s_inodes_count),
						le32_to_cpu(e4sb->s_blocks_count_lo));	
	pr_info("blocks per group = %d\n", le32_to_cpu(e4sb->s_blocks_per_group));
	pr_info("inodes per gorup = %d\n", le32_to_cpu(e4sb->s_inodes_per_group));
	pr_info("creator os: %s\n", le32_to_cpu(e4sb->s_creator_os) == 0 ? "Linux" : "others");
	pr_info("first non-reserved inode = %d\n", le32_to_cpu(e4sb->s_first_ino));	
	pr_info("block group # of this sb = %d\n", le16_to_cpu(e4sb->s_block_group_nr));
	pr_info("size of group descrptor = %d\n", le16_to_cpu(e4sb->s_desc_size));

	egd = (struct ext4_group_desc *)(ext4_base + 1024 + 1024); /* Skip the SB */
	pr_info("Inodes bitmap block = %d\n", le32_to_cpu(egd->bg_inode_bitmap_lo));
	pr_info("map[8] = 0x%x\n", *(ext4_base + le32_to_cpu(egd->bg_inode_bitmap_lo)));
	pr_info("Block group flag = 0x%x\n", le16_to_cpu(egd->bg_flags));
	return;
}

static int ext4tap_init(void)
{
	pr_info("--%s--\n", __func__);
	pr_info("sdisk = 0x%px\n", get_ramhd_base());
	dump_ext4_sb();
	return 0;
}

static void ext4tap_exit(void)
{
	printk("--%s--\n", __func__);
	
	return;
}

module_init(ext4tap_init);
module_exit(ext4tap_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuesong.cxs@outlook.com");
