#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xd4733cff, "module_layout" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x62c1ade7, "malloc_sizes" },
	{ 0x48eb0c0d, "__init_waitqueue_head" },
	{ 0x95435001, "current_task" },
	{ 0x50eedeb8, "printk" },
	{ 0x4292364c, "schedule" },
	{ 0xb0cbe4cb, "kfree_skb" },
	{ 0x6fe340df, "kmem_cache_alloc_trace" },
	{ 0x67f7403e, "_raw_spin_lock" },
	{ 0xefdd5a63, "ktime_get_ts" },
	{ 0x37a0cba, "kfree" },
	{ 0x622fa02a, "prepare_to_wait" },
	{ 0x75bb675a, "finish_wait" },
	{ 0xdf4c8767, "ns_to_timeval" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

