#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

KSYMTAB_FUNC(get_ramhd_base, "_gpl", "");

SYMBOL_CRC(get_ramhd_base, 0x9c8074d6, "_gpl");

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x53569707, "this_cpu_off" },
	{ 0xad5f0017, "perf_trace_buf_alloc" },
	{ 0x90c13d6e, "perf_trace_run_bpf_submit" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x1835bdce, "trace_event_buffer_reserve" },
	{ 0x2795daca, "trace_event_buffer_commit" },
	{ 0xd9d3eb1f, "__trace_trigger_soft_disabled" },
	{ 0xc97aff63, "trace_raw_output_prep" },
	{ 0x53b64e19, "trace_event_printf" },
	{ 0x8b3494ff, "trace_handle_return" },
	{ 0xc04466d8, "bpf_trace_run3" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x122c3a7e, "_printk" },
	{ 0x61beffa4, "blk_mq_start_request" },
	{ 0x4b750f53, "_raw_spin_unlock_irq" },
	{ 0x97651e6c, "vmemmap_base" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x8427cc7b, "_raw_spin_lock_irq" },
	{ 0x27e87d73, "pcpu_hot" },
	{ 0x5a5a2271, "__cpu_online_mask" },
	{ 0x688e72e1, "__SCT__preempt_schedule_notrace" },
	{ 0xe6739acd, "blk_mq_end_request" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0xfb578fc5, "memset" },
	{ 0x40f30ee1, "kmalloc_caches" },
	{ 0x5a764647, "kmalloc_trace" },
	{ 0x720a27a7, "__register_blkdev" },
	{ 0x8e5ce972, "blk_mq_alloc_tag_set" },
	{ 0x52fd0a52, "__blk_mq_alloc_disk" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x1a1fa66a, "set_capacity" },
	{ 0xcf75b64f, "device_add_disk" },
	{ 0x2413a0ba, "put_disk" },
	{ 0x999e8297, "vfree" },
	{ 0x4a30dee2, "del_gendisk" },
	{ 0xce767870, "blk_mq_free_tag_set" },
	{ 0xb5a459dc, "unregister_blkdev" },
	{ 0x37a0cba, "kfree" },
	{ 0xb2fa093e, "blk_mq_map_queues" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0xebdb5c47, "trace_event_reg" },
	{ 0x2baf5fa7, "trace_event_raw_init" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x65487097, "__x86_indirect_thunk_rax" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x8fef3d1a, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "CC8D288C5B18B1A8461FE6F");
