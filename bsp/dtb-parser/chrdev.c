#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/ctype.h>
#include <linux/string.h>
#include <linux/of.h>

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


/*
 * dump_blob() is borrowed from fdtdump.c which is a usrland stuff, so
 * update a little bit to make it to fit the kernel space
 */
typedef __be16 fdt16_t;
typedef __be32 fdt32_t;
typedef __be64 fdt64_t;

struct fdt_reserve_entry {
	fdt64_t address;
	fdt64_t size;
};

struct fdt_node_header {
	fdt32_t tag;
	char name[0];
};

struct fdt_property {
	fdt32_t tag;
	fdt32_t len;
	fdt32_t nameoff;
	char data[0];
};

#define FDT_MAGIC	0xd00dfeed	/* 4: version, 4: total size */
#define FDT_TAGSIZE	sizeof(fdt32_t)

#define FDT_BEGIN_NODE	0x1		/* Start node: full name */
#define FDT_END_NODE	0x2		/* End node */
#define FDT_PROP	0x3		/* Property: name off,
					   size, content */
#define FDT_NOP		0x4		/* nop */
#define FDT_END		0x9

//#define ALIGN(x, a)	(((x) + ((a) - 1)) & ~((a) - 1))
#define PALIGN(p, a)	((void *)(ALIGN((unsigned long)(p), (a))))
#define GET_CELL(p)	(p += 4, *((const u32 *)(p-4)))

static bool util_is_printable_string(const void *data, int len)
{
	const char *s = data;
	const char *ss, *se;

	/* zero length is not */
	if (len == 0)
		return 0;

	/* must terminate with zero */
	if (s[len - 1] != '\0')
		return 0;

	se = s + len;

	while (s < se) {
		ss = s;
		while (s < se && *s && isprint((unsigned char)*s))
			s++;

		/* not zero, or not done yet */
		if (*s != '\0' || s == ss)
			return 0;

		s++;
	}

	return 1;
}

static void print_data(const char *data, int len)
{
	int i;
	const char *p = data;

	/* no data, don't print */
	if (len == 0)
		return;

	if (util_is_printable_string(data, len)) {
		printk(" = \"%s\"", (const char *)data);
	} else if ((len % 4) == 0) {
		printk(" = <");
		for (i = 0; i < len; i += 4)
			printk("0x%08x%s", be32_to_cpu(GET_CELL(p)),
			       i < (len - 4) ? " " : "");
		printk(">");
	} else {
		printk(" = [");
		for (i = 0; i < len; i++)
			printk("%02x%s", *p++, i < len - 1 ? " " : "");
		printk("]");
	}
}

static void dump_blob(void *blob)
{
	struct fdt_header *bph = blob;
	u32 off_mem_rsvmap = be32_to_cpu(bph->off_mem_rsvmap);
	u32 off_dt = be32_to_cpu(bph->off_dt_struct);
	u32 off_str = be32_to_cpu(bph->off_dt_strings);
	struct fdt_reserve_entry *p_rsvmap =
		(struct fdt_reserve_entry *)((char *)blob + off_mem_rsvmap);
	const char *p_struct = (const char *)blob + off_dt;
	const char *p_strings = (const char *)blob + off_str;
	u32 version = be32_to_cpu(bph->version);
	u32 totalsize = be32_to_cpu(bph->totalsize);
	u32 tag;
	const char *p, *s, *t;
	int depth, sz, shift;
	int i;
	u64 addr, size;

	depth = 0;
	shift = 4;

	printk("/dts-v1/;\n");
	printk("// magic:\t\t0x%x\n", be32_to_cpu(bph->magic));
	printk("// totalsize:\t\t0x%x (%d)\n", totalsize, totalsize);
	printk("// off_dt_struct:\t0x%x\n", off_dt);
	printk("// off_dt_strings:\t0x%x\n", off_str);
	printk("// off_mem_rsvmap:\t0x%x\n", off_mem_rsvmap);
	printk("// version:\t\t%d\n", version);
	printk("// last_comp_version:\t%d\n",
	       be32_to_cpu(bph->last_comp_version));
	if (version >= 2)
		printk("// boot_cpuid_phys:\t0x%x\n",
		       be32_to_cpu(bph->boot_cpuid_phys));

	if (version >= 3)
		printk("// size_dt_strings:\t0x%x\n",
		       be32_to_cpu(bph->size_dt_strings));
	if (version >= 17)
		printk("// size_dt_struct:\t0x%x\n",
		       be32_to_cpu(bph->size_dt_struct));
	printk("\n");

	for (i = 0; ; i++) {
		addr = be64_to_cpu(p_rsvmap[i].address);
		size = be64_to_cpu(p_rsvmap[i].size);
		if (addr == 0 && size == 0)
			break;

		printk("/memreserve/ %llx %llx;\n",
		       (unsigned long long)addr, (unsigned long long)size);
	}

	p = p_struct;
	while ((tag = be32_to_cpu(GET_CELL(p))) != FDT_END) {

		/* printk("tag: 0x%08x (%d)\n", tag, p - p_struct); */

		if (tag == FDT_BEGIN_NODE) {
			s = p;
			p = PALIGN(p + strlen(s) + 1, 4);

			if (*s == '\0')
				s = "/";

			printk("%*s%s {\n", depth * shift, "", s);

			depth++;
			continue;
		}

		if (tag == FDT_END_NODE) {
			depth--;

			printk("%*s};\n", depth * shift, "");
			continue;
		}

		if (tag == FDT_NOP) {
			printk("%*s// [NOP]\n", depth * shift, "");
			continue;
		}

		if (tag != FDT_PROP) {
			pr_err("%*s ** Unknown tag 0x%08x\n", depth * shift, "", tag);
			break;
		}
		sz = be32_to_cpu(GET_CELL(p));
		s = p_strings + be32_to_cpu(GET_CELL(p));
		if (version < 16 && sz >= 8)
			p = PALIGN(p, 8);
		t = p;

		p = PALIGN(p + sz, 4);

		printk("%*s%s", depth * shift, "", s);
		print_data(t, sz);
		printk(";\n");
	}
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
	pr_info("of_root = 0x%px\n", of_root);
#if 1
	fh = (struct fdt_header *)hdr;
	pr_info("magic = 0x%x\n", be32_to_cpu(fh->magic));
	pr_info("total size = %d\n", be32_to_cpu(fh->totalsize));
#endif
	//dump_blob(hdr);

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

