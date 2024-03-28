savedcmd_/home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/ramhd_mq.o := gcc -Wp,-MMD,/home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/.ramhd_mq.o.d -nostdinc -I/home/xuesong/linux/rt/linux-stable/arch/x86/include -I./arch/x86/include/generated -I/home/xuesong/linux/rt/linux-stable/include -I./include -I/home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi -I./arch/x86/include/generated/uapi -I/home/xuesong/linux/rt/linux-stable/include/uapi -I./include/generated/uapi -include /home/xuesong/linux/rt/linux-stable/include/linux/compiler-version.h -include /home/xuesong/linux/rt/linux-stable/include/linux/kconfig.h -include /home/xuesong/linux/rt/linux-stable/include/linux/compiler_types.h -D__KERNEL__ -fmacro-prefix-map=/home/xuesong/linux/rt/linux-stable/= -std=gnu11 -fshort-wchar -funsigned-char -fno-common -fno-PIE -fno-strict-aliasing -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -fcf-protection=none -m64 -falign-jumps=1 -falign-loops=1 -mno-80387 -mno-fp-ret-in-387 -mpreferred-stack-boundary=3 -mskip-rax-setup -mtune=generic -mno-red-zone -mcmodel=kernel -Wno-sign-compare -fno-asynchronous-unwind-tables -mindirect-branch=thunk-extern -mindirect-branch-register -mindirect-branch-cs-prefix -mfunction-return=thunk-extern -fno-jump-tables -mharden-sls=all -fpatchable-function-entry=16,16 -fno-delete-null-pointer-checks -O2 -fno-allow-store-data-races -fstack-protector-strong -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-stack-clash-protection -fzero-call-used-regs=used-gpr -pg -mrecord-mcount -mfentry -DCC_USING_FENTRY -falign-functions=16 -fno-strict-overflow -fno-stack-check -fconserve-stack -Wall -Wundef -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Werror=strict-prototypes -Wno-format-security -Wno-trigraphs -Wno-frame-address -Wno-address-of-packed-member -Wframe-larger-than=1024 -Wno-main -Wno-unused-but-set-variable -Wno-unused-const-variable -Wvla -Wno-pointer-sign -Wcast-function-type -Wno-array-bounds -Wno-alloc-size-larger-than -Wimplicit-fallthrough=5 -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -Wenum-conversion -Wno-unused-but-set-variable -Wno-unused-const-variable -Wno-restrict -Wno-packed-not-aligned -Wno-format-overflow -Wno-format-truncation -Wno-stringop-overflow -Wno-stringop-truncation -Wno-missing-field-initializers -Wno-type-limits -Wno-shift-negative-value -Wno-maybe-uninitialized -Wno-sign-compare -g -gdwarf-5 -I/home/xuesong/linux/trainings/llddv2/block/blk_mq_ram  -fsanitize=bounds-strict -fsanitize=shift -fsanitize=bool -fsanitize=enum  -DMODULE  -DKBUILD_BASENAME='"ramhd_mq"' -DKBUILD_MODNAME='"ramhd_mq"' -D__KBUILD_MODNAME=kmod_ramhd_mq -c -o /home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/ramhd_mq.o /home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/ramhd_mq.c   ; ./tools/objtool/objtool --hacks=jump_label --hacks=noinstr --hacks=skylake --retpoline --rethunk --sls --stackval --static-call --uaccess --prefix=16   --module /home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/ramhd_mq.o

source_/home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/ramhd_mq.o := /home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/ramhd_mq.c

deps_/home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/ramhd_mq.o := \
  /home/xuesong/linux/rt/linux-stable/include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  /home/xuesong/linux/rt/linux-stable/include/linux/compiler_types.h \
    $(wildcard include/config/DEBUG_INFO_BTF) \
    $(wildcard include/config/PAHOLE_HAS_BTF_TAG) \
    $(wildcard include/config/FUNCTION_ALIGNMENT) \
    $(wildcard include/config/CC_IS_GCC) \
    $(wildcard include/config/X86_64) \
    $(wildcard include/config/ARM64) \
    $(wildcard include/config/HAVE_ARCH_COMPILER_H) \
    $(wildcard include/config/CC_HAS_ASM_INLINE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/compiler_attributes.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/compiler-gcc.h \
    $(wildcard include/config/RETPOLINE) \
    $(wildcard include/config/ARCH_USE_BUILTIN_BSWAP) \
    $(wildcard include/config/SHADOW_CALL_STACK) \
    $(wildcard include/config/KCOV) \
  /home/xuesong/linux/rt/linux-stable/include/linux/module.h \
    $(wildcard include/config/MODULES) \
    $(wildcard include/config/SYSFS) \
    $(wildcard include/config/MODULES_TREE_LOOKUP) \
    $(wildcard include/config/LIVEPATCH) \
    $(wildcard include/config/STACKTRACE_BUILD_ID) \
    $(wildcard include/config/ARCH_USES_CFI_TRAPS) \
    $(wildcard include/config/MODULE_SIG) \
    $(wildcard include/config/GENERIC_BUG) \
    $(wildcard include/config/KALLSYMS) \
    $(wildcard include/config/SMP) \
    $(wildcard include/config/TRACEPOINTS) \
    $(wildcard include/config/TREE_SRCU) \
    $(wildcard include/config/BPF_EVENTS) \
    $(wildcard include/config/DEBUG_INFO_BTF_MODULES) \
    $(wildcard include/config/JUMP_LABEL) \
    $(wildcard include/config/TRACING) \
    $(wildcard include/config/EVENT_TRACING) \
    $(wildcard include/config/FTRACE_MCOUNT_RECORD) \
    $(wildcard include/config/KPROBES) \
    $(wildcard include/config/HAVE_STATIC_CALL_INLINE) \
    $(wildcard include/config/KUNIT) \
    $(wildcard include/config/PRINTK_INDEX) \
    $(wildcard include/config/MODULE_UNLOAD) \
    $(wildcard include/config/CONSTRUCTORS) \
    $(wildcard include/config/FUNCTION_ERROR_INJECTION) \
    $(wildcard include/config/DYNAMIC_DEBUG_CORE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/list.h \
    $(wildcard include/config/LIST_HARDENED) \
    $(wildcard include/config/DEBUG_LIST) \
  /home/xuesong/linux/rt/linux-stable/include/linux/container_of.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/build_bug.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/compiler.h \
    $(wildcard include/config/TRACE_BRANCH_PROFILING) \
    $(wildcard include/config/PROFILE_ALL_BRANCHES) \
    $(wildcard include/config/OBJTOOL) \
  arch/x86/include/generated/asm/rwonce.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/rwonce.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kasan-checks.h \
    $(wildcard include/config/KASAN_GENERIC) \
    $(wildcard include/config/KASAN_SW_TAGS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/types.h \
    $(wildcard include/config/HAVE_UID16) \
    $(wildcard include/config/UID16) \
    $(wildcard include/config/ARCH_DMA_ADDR_T_64BIT) \
    $(wildcard include/config/PHYS_ADDR_T_64BIT) \
    $(wildcard include/config/64BIT) \
    $(wildcard include/config/ARCH_32BIT_USTAT_F_TINODE) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/types.h \
  arch/x86/include/generated/uapi/asm/types.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/types.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/int-ll64.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/int-ll64.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/bitsperlong.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/bitsperlong.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/bitsperlong.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/posix_types.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/stddef.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/stddef.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/posix_types.h \
    $(wildcard include/config/X86_32) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/posix_types_64.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/posix_types.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kcsan-checks.h \
    $(wildcard include/config/KCSAN) \
    $(wildcard include/config/KCSAN_WEAK_MEMORY) \
    $(wildcard include/config/KCSAN_IGNORE_ATOMICS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/poison.h \
    $(wildcard include/config/ILLEGAL_POINTER_VALUE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/const.h \
  /home/xuesong/linux/rt/linux-stable/include/vdso/const.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/const.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/barrier.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/alternative.h \
    $(wildcard include/config/CALL_THUNKS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/stringify.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/asm.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/extable_fixup_types.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/nops.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/barrier.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/stat.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/stat.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/stat.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/time.h \
    $(wildcard include/config/POSIX_TIMERS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/cache.h \
    $(wildcard include/config/ARCH_HAS_CACHE_LINE_SIZE) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/kernel.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/sysinfo.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/cache.h \
    $(wildcard include/config/X86_L1_CACHE_SHIFT) \
    $(wildcard include/config/X86_INTERNODE_CACHE_SHIFT) \
    $(wildcard include/config/X86_VSMP) \
  /home/xuesong/linux/rt/linux-stable/include/linux/linkage.h \
    $(wildcard include/config/ARCH_USE_SYM_ANNOTATIONS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/export.h \
    $(wildcard include/config/MODVERSIONS) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/linkage.h \
    $(wildcard include/config/CALL_PADDING) \
    $(wildcard include/config/RETHUNK) \
    $(wildcard include/config/SLS) \
    $(wildcard include/config/FUNCTION_PADDING_BYTES) \
    $(wildcard include/config/UML) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/ibt.h \
    $(wildcard include/config/X86_KERNEL_IBT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/math64.h \
    $(wildcard include/config/ARCH_SUPPORTS_INT128) \
  /home/xuesong/linux/rt/linux-stable/include/linux/math.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/div64.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/div64.h \
  /home/xuesong/linux/rt/linux-stable/include/vdso/math64.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/time64.h \
  /home/xuesong/linux/rt/linux-stable/include/vdso/time64.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/time.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/time_types.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/time32.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/timex.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/timex.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/param.h \
  arch/x86/include/generated/uapi/asm/param.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/param.h \
    $(wildcard include/config/HZ) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/param.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/timex.h \
    $(wildcard include/config/X86_TSC) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/processor.h \
    $(wildcard include/config/X86_VMX_FEATURE_NAMES) \
    $(wildcard include/config/X86_IOPL_IOPERM) \
    $(wildcard include/config/STACKPROTECTOR) \
    $(wildcard include/config/VM86) \
    $(wildcard include/config/X86_USER_SHADOW_STACK) \
    $(wildcard include/config/PARAVIRT_XXL) \
    $(wildcard include/config/X86_DEBUGCTLMSR) \
    $(wildcard include/config/CPU_SUP_AMD) \
    $(wildcard include/config/XEN) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/processor-flags.h \
    $(wildcard include/config/PAGE_TABLE_ISOLATION) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/processor-flags.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/mem_encrypt.h \
    $(wildcard include/config/ARCH_HAS_MEM_ENCRYPT) \
    $(wildcard include/config/AMD_MEM_ENCRYPT) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/mem_encrypt.h \
    $(wildcard include/config/X86_MEM_ENCRYPT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/init.h \
    $(wildcard include/config/HAVE_ARCH_PREL32_RELOCATIONS) \
    $(wildcard include/config/STRICT_KERNEL_RWX) \
    $(wildcard include/config/STRICT_MODULE_RWX) \
    $(wildcard include/config/LTO_CLANG) \
  /home/xuesong/linux/rt/linux-stable/include/linux/cc_platform.h \
    $(wildcard include/config/ARCH_HAS_CC_PLATFORM) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/bootparam.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/screen_info.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/screen_info.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/apm_bios.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/apm_bios.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/ioctl.h \
  arch/x86/include/generated/uapi/asm/ioctl.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/ioctl.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/ioctl.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/edd.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/edd.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/ist.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/ist.h \
  /home/xuesong/linux/rt/linux-stable/include/video/edid.h \
    $(wildcard include/config/X86) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/video/edid.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/math_emu.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/ptrace.h \
    $(wildcard include/config/PARAVIRT) \
    $(wildcard include/config/IA32_EMULATION) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/segment.h \
    $(wildcard include/config/XEN_PV) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/page_types.h \
    $(wildcard include/config/PHYSICAL_START) \
    $(wildcard include/config/PHYSICAL_ALIGN) \
    $(wildcard include/config/DYNAMIC_PHYSICAL_MASK) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/page_64_types.h \
    $(wildcard include/config/KASAN) \
    $(wildcard include/config/DYNAMIC_MEMORY_LAYOUT) \
    $(wildcard include/config/X86_5LEVEL) \
    $(wildcard include/config/RANDOMIZE_BASE) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/kaslr.h \
    $(wildcard include/config/RANDOMIZE_MEMORY) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/ptrace.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/ptrace-abi.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/paravirt_types.h \
    $(wildcard include/config/PGTABLE_LEVELS) \
    $(wildcard include/config/ZERO_CALL_USED_REGS) \
    $(wildcard include/config/PARAVIRT_DEBUG) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/desc_defs.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/pgtable_types.h \
    $(wildcard include/config/X86_INTEL_MEMORY_PROTECTION_KEYS) \
    $(wildcard include/config/X86_PAE) \
    $(wildcard include/config/MEM_SOFT_DIRTY) \
    $(wildcard include/config/HAVE_ARCH_USERFAULTFD_WP) \
    $(wildcard include/config/PROC_FS) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/pgtable_64_types.h \
    $(wildcard include/config/KMSAN) \
    $(wildcard include/config/DEBUG_KMAP_LOCAL_FORCE_MAP) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/sparsemem.h \
    $(wildcard include/config/SPARSEMEM) \
    $(wildcard include/config/NUMA_KEEP_MEMINFO) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/nospec-branch.h \
    $(wildcard include/config/CALL_THUNKS_DEBUG) \
    $(wildcard include/config/CALL_DEPTH_TRACKING) \
    $(wildcard include/config/NOINSTR_VALIDATION) \
    $(wildcard include/config/CPU_UNRET_ENTRY) \
    $(wildcard include/config/CPU_SRSO) \
    $(wildcard include/config/CPU_IBPB_ENTRY) \
  /home/xuesong/linux/rt/linux-stable/include/linux/static_key.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/jump_label.h \
    $(wildcard include/config/HAVE_ARCH_JUMP_LABEL_RELATIVE) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/jump_label.h \
    $(wildcard include/config/HAVE_JUMP_LABEL_HACK) \
  /home/xuesong/linux/rt/linux-stable/include/linux/objtool.h \
    $(wildcard include/config/FRAME_POINTER) \
  /home/xuesong/linux/rt/linux-stable/include/linux/objtool_types.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/cpufeatures.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/required-features.h \
    $(wildcard include/config/X86_MINIMUM_CPU_FAMILY) \
    $(wildcard include/config/MATH_EMULATION) \
    $(wildcard include/config/X86_CMPXCHG64) \
    $(wildcard include/config/X86_CMOV) \
    $(wildcard include/config/X86_P6_NOP) \
    $(wildcard include/config/MATOM) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/disabled-features.h \
    $(wildcard include/config/X86_UMIP) \
    $(wildcard include/config/ADDRESS_MASKING) \
    $(wildcard include/config/INTEL_IOMMU_SVM) \
    $(wildcard include/config/X86_SGX) \
    $(wildcard include/config/INTEL_TDX_GUEST) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/msr-index.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/bits.h \
  /home/xuesong/linux/rt/linux-stable/include/vdso/bits.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/unwind_hints.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/orc_types.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/byteorder.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/byteorder/little_endian.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/byteorder/little_endian.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/swab.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/swab.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/swab.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/byteorder/generic.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/percpu.h \
    $(wildcard include/config/X86_64_SMP) \
  /home/xuesong/linux/rt/linux-stable/include/linux/kernel.h \
    $(wildcard include/config/PREEMPT_VOLUNTARY_BUILD) \
    $(wildcard include/config/PREEMPT_DYNAMIC) \
    $(wildcard include/config/HAVE_PREEMPT_DYNAMIC_CALL) \
    $(wildcard include/config/HAVE_PREEMPT_DYNAMIC_KEY) \
    $(wildcard include/config/PREEMPT_) \
    $(wildcard include/config/DEBUG_ATOMIC_SLEEP) \
    $(wildcard include/config/MMU) \
    $(wildcard include/config/PROVE_LOCKING) \
  /home/xuesong/linux/rt/linux-stable/include/linux/stdarg.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/align.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/array_size.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/limits.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/limits.h \
  /home/xuesong/linux/rt/linux-stable/include/vdso/limits.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/bitops.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/typecheck.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/bitops/generic-non-atomic.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/bitops.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/rmwcc.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/args.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/bitops/sched.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/arch_hweight.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/bitops/const_hweight.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/bitops/instrumented-atomic.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/instrumented.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kmsan-checks.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/bitops/instrumented-non-atomic.h \
    $(wildcard include/config/KCSAN_ASSUME_PLAIN_WRITES_ATOMIC) \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/bitops/instrumented-lock.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/bitops/le.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/hex.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kstrtox.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/log2.h \
    $(wildcard include/config/ARCH_HAS_ILOG2_U32) \
    $(wildcard include/config/ARCH_HAS_ILOG2_U64) \
  /home/xuesong/linux/rt/linux-stable/include/linux/minmax.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/panic.h \
    $(wildcard include/config/PANIC_TIMEOUT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/printk.h \
    $(wildcard include/config/MESSAGE_LOGLEVEL_DEFAULT) \
    $(wildcard include/config/CONSOLE_LOGLEVEL_DEFAULT) \
    $(wildcard include/config/CONSOLE_LOGLEVEL_QUIET) \
    $(wildcard include/config/EARLY_PRINTK) \
    $(wildcard include/config/PRINTK) \
    $(wildcard include/config/DYNAMIC_DEBUG) \
  /home/xuesong/linux/rt/linux-stable/include/linux/kern_levels.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/ratelimit_types.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/spinlock_types_raw.h \
    $(wildcard include/config/DEBUG_SPINLOCK) \
    $(wildcard include/config/DEBUG_LOCK_ALLOC) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/spinlock_types.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/qspinlock_types.h \
    $(wildcard include/config/NR_CPUS) \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/qrwlock_types.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/lockdep_types.h \
    $(wildcard include/config/PROVE_RAW_LOCK_NESTING) \
    $(wildcard include/config/LOCKDEP) \
    $(wildcard include/config/LOCK_STAT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/once_lite.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/dynamic_debug.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/sprintf.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/static_call_types.h \
    $(wildcard include/config/HAVE_STATIC_CALL) \
  /home/xuesong/linux/rt/linux-stable/include/linux/instruction_pointer.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/percpu.h \
    $(wildcard include/config/DEBUG_PREEMPT) \
    $(wildcard include/config/HAVE_SETUP_PER_CPU_AREA) \
  /home/xuesong/linux/rt/linux-stable/include/linux/threads.h \
    $(wildcard include/config/BASE_SMALL) \
  /home/xuesong/linux/rt/linux-stable/include/linux/percpu-defs.h \
    $(wildcard include/config/DEBUG_FORCE_WEAK_PER_CPU) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/current.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/GEN-for-each-reg.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/proto.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/ldt.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/sigcontext.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/cpuid.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/string.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/string_64.h \
    $(wildcard include/config/ARCH_HAS_UACCESS_FLUSHCACHE) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/paravirt.h \
    $(wildcard include/config/PARAVIRT_SPINLOCKS) \
    $(wildcard include/config/DEBUG_ENTRY) \
  /home/xuesong/linux/rt/linux-stable/include/linux/bug.h \
    $(wildcard include/config/BUG_ON_DATA_CORRUPTION) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/bug.h \
    $(wildcard include/config/DEBUG_BUGVERBOSE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/instrumentation.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/bug.h \
    $(wildcard include/config/BUG) \
    $(wildcard include/config/GENERIC_BUG_RELATIVE_POINTERS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/cpumask.h \
    $(wildcard include/config/FORCE_NR_CPUS) \
    $(wildcard include/config/HOTPLUG_CPU) \
    $(wildcard include/config/DEBUG_PER_CPU_MAPS) \
    $(wildcard include/config/CPUMASK_OFFSTACK) \
  /home/xuesong/linux/rt/linux-stable/include/linux/bitmap.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/errno.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/errno.h \
  arch/x86/include/generated/uapi/asm/errno.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/errno.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/errno-base.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/find.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/string.h \
    $(wildcard include/config/BINARY_PRINTF) \
    $(wildcard include/config/FORTIFY_SOURCE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/err.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/overflow.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/string.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/fortify-string.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/bitmap-str.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/atomic.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/atomic.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/cmpxchg.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/cmpxchg_64.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/atomic64_64.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/atomic/atomic-arch-fallback.h \
    $(wildcard include/config/GENERIC_ATOMIC64) \
  /home/xuesong/linux/rt/linux-stable/include/linux/atomic/atomic-long.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/atomic/atomic-instrumented.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/gfp_types.h \
    $(wildcard include/config/KASAN_HW_TAGS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/numa.h \
    $(wildcard include/config/NODES_SHIFT) \
    $(wildcard include/config/NUMA) \
    $(wildcard include/config/HAVE_ARCH_NODE_DEV_GROUP) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/frame.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/page.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/page_64.h \
    $(wildcard include/config/DEBUG_VIRTUAL) \
    $(wildcard include/config/X86_VSYSCALL_EMULATION) \
  /home/xuesong/linux/rt/linux-stable/include/linux/range.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/memory_model.h \
    $(wildcard include/config/FLATMEM) \
    $(wildcard include/config/SPARSEMEM_VMEMMAP) \
  /home/xuesong/linux/rt/linux-stable/include/linux/pfn.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/getorder.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/msr.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/cpumask.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/msr.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/shared/msr.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/tracepoint-defs.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/special_insns.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/irqflags.h \
    $(wildcard include/config/TRACE_IRQFLAGS) \
    $(wildcard include/config/PREEMPT_RT) \
    $(wildcard include/config/IRQSOFF_TRACER) \
    $(wildcard include/config/PREEMPT_TRACER) \
    $(wildcard include/config/DEBUG_IRQFLAGS) \
    $(wildcard include/config/TRACE_IRQFLAGS_SUPPORT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/cleanup.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/irqflags.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/fpu/types.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/vmxfeatures.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/vdso/processor.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/shstk.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/personality.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/personality.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/tsc.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/cpufeature.h \
  /home/xuesong/linux/rt/linux-stable/include/vdso/time32.h \
  /home/xuesong/linux/rt/linux-stable/include/vdso/time.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/uidgid.h \
    $(wildcard include/config/MULTIUSER) \
    $(wildcard include/config/USER_NS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/highuid.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/buildid.h \
    $(wildcard include/config/CRASH_CORE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/kmod.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/umh.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/gfp.h \
    $(wildcard include/config/HIGHMEM) \
    $(wildcard include/config/ZONE_DMA) \
    $(wildcard include/config/ZONE_DMA32) \
    $(wildcard include/config/ZONE_DEVICE) \
    $(wildcard include/config/CONTIG_ALLOC) \
  /home/xuesong/linux/rt/linux-stable/include/linux/mmzone.h \
    $(wildcard include/config/ARCH_FORCE_MAX_ORDER) \
    $(wildcard include/config/CMA) \
    $(wildcard include/config/MEMORY_ISOLATION) \
    $(wildcard include/config/ZSMALLOC) \
    $(wildcard include/config/UNACCEPTED_MEMORY) \
    $(wildcard include/config/SWAP) \
    $(wildcard include/config/NUMA_BALANCING) \
    $(wildcard include/config/TRANSPARENT_HUGEPAGE) \
    $(wildcard include/config/LRU_GEN) \
    $(wildcard include/config/LRU_GEN_STATS) \
    $(wildcard include/config/MEMCG) \
    $(wildcard include/config/MEMORY_HOTPLUG) \
    $(wildcard include/config/COMPACTION) \
    $(wildcard include/config/MEMORY_FAILURE) \
    $(wildcard include/config/PAGE_EXTENSION) \
    $(wildcard include/config/DEFERRED_STRUCT_PAGE_INIT) \
    $(wildcard include/config/HAVE_MEMORYLESS_NODES) \
    $(wildcard include/config/SPARSEMEM_EXTREME) \
    $(wildcard include/config/HAVE_ARCH_PFN_VALID) \
  /home/xuesong/linux/rt/linux-stable/include/linux/spinlock.h \
    $(wildcard include/config/PREEMPTION) \
  /home/xuesong/linux/rt/linux-stable/include/linux/preempt.h \
    $(wildcard include/config/PREEMPT_COUNT) \
    $(wildcard include/config/TRACE_PREEMPT_TOGGLE) \
    $(wildcard include/config/PREEMPT_NOTIFIERS) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/preempt.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/thread_info.h \
    $(wildcard include/config/THREAD_INFO_IN_TASK) \
    $(wildcard include/config/GENERIC_ENTRY) \
    $(wildcard include/config/HAVE_ARCH_WITHIN_STACK_FRAMES) \
    $(wildcard include/config/HARDENED_USERCOPY) \
    $(wildcard include/config/SH) \
  /home/xuesong/linux/rt/linux-stable/include/linux/restart_block.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/thread_info.h \
    $(wildcard include/config/COMPAT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/bottom_half.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/lockdep.h \
    $(wildcard include/config/DEBUG_LOCKING_API_SELFTESTS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/smp.h \
    $(wildcard include/config/UP_LATE_INIT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/smp_types.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/llist.h \
    $(wildcard include/config/ARCH_HAVE_NMI_SAFE_CMPXCHG) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/smp.h \
    $(wildcard include/config/DEBUG_NMI_SELFTEST) \
  arch/x86/include/generated/asm/mmiowb.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/mmiowb.h \
    $(wildcard include/config/MMIOWB) \
  /home/xuesong/linux/rt/linux-stable/include/linux/spinlock_types.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/rwlock_types.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/spinlock.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/qspinlock.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/qspinlock.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/qrwlock.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/qrwlock.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/rwlock.h \
    $(wildcard include/config/PREEMPT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/INLINE_SPIN_LOCK) \
    $(wildcard include/config/INLINE_SPIN_LOCK_BH) \
    $(wildcard include/config/INLINE_SPIN_LOCK_IRQ) \
    $(wildcard include/config/INLINE_SPIN_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_SPIN_TRYLOCK) \
    $(wildcard include/config/INLINE_SPIN_TRYLOCK_BH) \
    $(wildcard include/config/UNINLINE_SPIN_UNLOCK) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_BH) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_IRQRESTORE) \
    $(wildcard include/config/GENERIC_LOCKBREAK) \
  /home/xuesong/linux/rt/linux-stable/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/INLINE_READ_LOCK) \
    $(wildcard include/config/INLINE_WRITE_LOCK) \
    $(wildcard include/config/INLINE_READ_LOCK_BH) \
    $(wildcard include/config/INLINE_WRITE_LOCK_BH) \
    $(wildcard include/config/INLINE_READ_LOCK_IRQ) \
    $(wildcard include/config/INLINE_WRITE_LOCK_IRQ) \
    $(wildcard include/config/INLINE_READ_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_WRITE_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_READ_TRYLOCK) \
    $(wildcard include/config/INLINE_WRITE_TRYLOCK) \
    $(wildcard include/config/INLINE_READ_UNLOCK) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK) \
    $(wildcard include/config/INLINE_READ_UNLOCK_BH) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_BH) \
    $(wildcard include/config/INLINE_READ_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_READ_UNLOCK_IRQRESTORE) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_IRQRESTORE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/list_nulls.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/wait.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/wait.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/seqlock.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/mutex.h \
    $(wildcard include/config/MUTEX_SPIN_ON_OWNER) \
    $(wildcard include/config/DEBUG_MUTEXES) \
  /home/xuesong/linux/rt/linux-stable/include/linux/osq_lock.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/debug_locks.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/nodemask.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/random.h \
    $(wildcard include/config/VMGENID) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/random.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/irqnr.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/irqnr.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/prandom.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/once.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/percpu.h \
    $(wildcard include/config/RANDOM_KMALLOC_CACHES) \
    $(wildcard include/config/NEED_PER_CPU_PAGE_FIRST_CHUNK) \
  /home/xuesong/linux/rt/linux-stable/include/linux/mmdebug.h \
    $(wildcard include/config/DEBUG_VM) \
    $(wildcard include/config/DEBUG_VM_IRQSOFF) \
    $(wildcard include/config/DEBUG_VM_PGFLAGS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/pageblock-flags.h \
    $(wildcard include/config/HUGETLB_PAGE) \
    $(wildcard include/config/HUGETLB_PAGE_SIZE_VARIABLE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/page-flags-layout.h \
  include/generated/bounds.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/mm_types.h \
    $(wildcard include/config/HAVE_ALIGNED_STRUCT_PAGE) \
    $(wildcard include/config/USERFAULTFD) \
    $(wildcard include/config/ANON_VMA_NAME) \
    $(wildcard include/config/PER_VMA_LOCK) \
    $(wildcard include/config/SCHED_MM_CID) \
    $(wildcard include/config/HAVE_ARCH_COMPAT_MMAP_BASES) \
    $(wildcard include/config/MEMBARRIER) \
    $(wildcard include/config/AIO) \
    $(wildcard include/config/MMU_NOTIFIER) \
    $(wildcard include/config/ARCH_WANT_BATCHED_UNMAP_TLB_FLUSH) \
    $(wildcard include/config/IOMMU_SVA) \
    $(wildcard include/config/KSM) \
  /home/xuesong/linux/rt/linux-stable/include/linux/mm_types_task.h \
    $(wildcard include/config/SPLIT_PTLOCK_CPUS) \
    $(wildcard include/config/ARCH_ENABLE_SPLIT_PMD_PTLOCK) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/tlbbatch.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/auxvec.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/auxvec.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/auxvec.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kref.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/refcount.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/rbtree.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/rbtree_types.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/rcupdate.h \
    $(wildcard include/config/PREEMPT_RCU) \
    $(wildcard include/config/TINY_RCU) \
    $(wildcard include/config/RCU_STRICT_GRACE_PERIOD) \
    $(wildcard include/config/RCU_LAZY) \
    $(wildcard include/config/TASKS_RCU_GENERIC) \
    $(wildcard include/config/RCU_STALL_COMMON) \
    $(wildcard include/config/NO_HZ_FULL) \
    $(wildcard include/config/KVM_XFER_TO_GUEST_WORK) \
    $(wildcard include/config/RCU_NOCB_CPU) \
    $(wildcard include/config/TASKS_RCU) \
    $(wildcard include/config/TASKS_TRACE_RCU) \
    $(wildcard include/config/TASKS_RUDE_RCU) \
    $(wildcard include/config/TREE_RCU) \
    $(wildcard include/config/DEBUG_OBJECTS_RCU_HEAD) \
    $(wildcard include/config/PROVE_RCU) \
    $(wildcard include/config/ARCH_WEAK_RELEASE_ACQUIRE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/context_tracking_irq.h \
    $(wildcard include/config/CONTEXT_TRACKING_IDLE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/rcutree.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/maple_tree.h \
    $(wildcard include/config/MAPLE_RCU_DISABLED) \
    $(wildcard include/config/DEBUG_MAPLE_TREE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/rwsem.h \
    $(wildcard include/config/RWSEM_SPIN_ON_OWNER) \
    $(wildcard include/config/DEBUG_RWSEMS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/completion.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/swait.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/uprobes.h \
    $(wildcard include/config/UPROBES) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/uprobes.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/notifier.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/srcu.h \
    $(wildcard include/config/TINY_SRCU) \
    $(wildcard include/config/NEED_SRCU_NMI_SAFE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/workqueue.h \
    $(wildcard include/config/DEBUG_OBJECTS_WORK) \
    $(wildcard include/config/FREEZER) \
    $(wildcard include/config/WQ_WATCHDOG) \
  /home/xuesong/linux/rt/linux-stable/include/linux/timer.h \
    $(wildcard include/config/DEBUG_OBJECTS_TIMERS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/ktime.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/jiffies.h \
  /home/xuesong/linux/rt/linux-stable/include/vdso/jiffies.h \
  include/generated/timeconst.h \
  /home/xuesong/linux/rt/linux-stable/include/vdso/ktime.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/timekeeping.h \
    $(wildcard include/config/GENERIC_CMOS_UPDATE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/clocksource_ids.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/debugobjects.h \
    $(wildcard include/config/DEBUG_OBJECTS) \
    $(wildcard include/config/DEBUG_OBJECTS_FREE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/rcu_segcblist.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/srcutree.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/rcu_node_tree.h \
    $(wildcard include/config/RCU_FANOUT) \
    $(wildcard include/config/RCU_FANOUT_LEAF) \
  /home/xuesong/linux/rt/linux-stable/include/linux/percpu_counter.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/mmu.h \
    $(wildcard include/config/MODIFY_LDT_SYSCALL) \
  /home/xuesong/linux/rt/linux-stable/include/linux/page-flags.h \
    $(wildcard include/config/ARCH_USES_PG_UNCACHED) \
    $(wildcard include/config/PAGE_IDLE_FLAG) \
    $(wildcard include/config/ARCH_USES_PG_ARCH_X) \
    $(wildcard include/config/HUGETLB_PAGE_OPTIMIZE_VMEMMAP) \
  /home/xuesong/linux/rt/linux-stable/include/linux/local_lock.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/local_lock_internal.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/memory_hotplug.h \
    $(wildcard include/config/HAVE_ARCH_NODEDATA_EXTENSION) \
    $(wildcard include/config/ARCH_HAS_ADD_PAGES) \
    $(wildcard include/config/MEMORY_HOTREMOVE) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/mmzone.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/mmzone_64.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/topology.h \
    $(wildcard include/config/USE_PERCPU_NUMA_NODE_ID) \
    $(wildcard include/config/SCHED_SMT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/arch_topology.h \
    $(wildcard include/config/ACPI_CPPC_LIB) \
    $(wildcard include/config/GENERIC_ARCH_TOPOLOGY) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/topology.h \
    $(wildcard include/config/SCHED_MC_PRIO) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/mpspec.h \
    $(wildcard include/config/EISA) \
    $(wildcard include/config/X86_LOCAL_APIC) \
    $(wildcard include/config/X86_MPPARSE) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/mpspec_def.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/x86_init.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/apicdef.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/topology.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/cpu_smt.h \
    $(wildcard include/config/HOTPLUG_SMT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/sysctl.h \
    $(wildcard include/config/SYSCTL) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/sysctl.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/elf.h \
    $(wildcard include/config/ARCH_USE_GNU_PROPERTY) \
    $(wildcard include/config/ARCH_HAVE_ELF_PROT) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/elf.h \
    $(wildcard include/config/X86_X32_ABI) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/ia32.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/compat.h \
    $(wildcard include/config/ARCH_HAS_SYSCALL_WRAPPER) \
    $(wildcard include/config/COMPAT_OLD_SIGACTION) \
    $(wildcard include/config/ODD_RT_SIGACTION) \
  /home/xuesong/linux/rt/linux-stable/include/linux/sem.h \
    $(wildcard include/config/SYSVIPC) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/sem.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/ipc.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/rhashtable-types.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/ipc.h \
  arch/x86/include/generated/uapi/asm/ipcbuf.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/ipcbuf.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/sembuf.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/socket.h \
  arch/x86/include/generated/uapi/asm/socket.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/socket.h \
  arch/x86/include/generated/uapi/asm/sockios.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/sockios.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/sockios.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/uio.h \
    $(wildcard include/config/ARCH_HAS_COPY_MC) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/uio.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/socket.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/if.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/libc-compat.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/hdlc/ioctl.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/fs.h \
    $(wildcard include/config/READ_ONLY_THP_FOR_FS) \
    $(wildcard include/config/FS_POSIX_ACL) \
    $(wildcard include/config/SECURITY) \
    $(wildcard include/config/CGROUP_WRITEBACK) \
    $(wildcard include/config/IMA) \
    $(wildcard include/config/FILE_LOCKING) \
    $(wildcard include/config/FSNOTIFY) \
    $(wildcard include/config/FS_ENCRYPTION) \
    $(wildcard include/config/FS_VERITY) \
    $(wildcard include/config/EPOLL) \
    $(wildcard include/config/UNICODE) \
    $(wildcard include/config/QUOTA) \
    $(wildcard include/config/FS_DAX) \
    $(wildcard include/config/BLOCK) \
  /home/xuesong/linux/rt/linux-stable/include/linux/wait_bit.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kdev_t.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/kdev_t.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/dcache.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/rculist.h \
    $(wildcard include/config/PROVE_RCU_LIST) \
  /home/xuesong/linux/rt/linux-stable/include/linux/rculist_bl.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/list_bl.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/bit_spinlock.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/lockref.h \
    $(wildcard include/config/ARCH_USE_CMPXCHG_LOCKREF) \
  /home/xuesong/linux/rt/linux-stable/include/linux/stringhash.h \
    $(wildcard include/config/DCACHE_WORD_ACCESS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/hash.h \
    $(wildcard include/config/HAVE_ARCH_HASH) \
  /home/xuesong/linux/rt/linux-stable/include/linux/path.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/list_lru.h \
    $(wildcard include/config/MEMCG_KMEM) \
  /home/xuesong/linux/rt/linux-stable/include/linux/shrinker.h \
    $(wildcard include/config/SHRINKER_DEBUG) \
  /home/xuesong/linux/rt/linux-stable/include/linux/xarray.h \
    $(wildcard include/config/XARRAY_MULTI) \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/mm.h \
    $(wildcard include/config/MMU_LAZY_TLB_REFCOUNT) \
    $(wildcard include/config/ARCH_HAS_MEMBARRIER_CALLBACKS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched.h \
    $(wildcard include/config/VIRT_CPU_ACCOUNTING_NATIVE) \
    $(wildcard include/config/SCHED_INFO) \
    $(wildcard include/config/SCHEDSTATS) \
    $(wildcard include/config/SCHED_CORE) \
    $(wildcard include/config/FAIR_GROUP_SCHED) \
    $(wildcard include/config/RT_GROUP_SCHED) \
    $(wildcard include/config/RT_MUTEXES) \
    $(wildcard include/config/UCLAMP_TASK) \
    $(wildcard include/config/UCLAMP_BUCKETS_COUNT) \
    $(wildcard include/config/KMAP_LOCAL) \
    $(wildcard include/config/CGROUP_SCHED) \
    $(wildcard include/config/BLK_DEV_IO_TRACE) \
    $(wildcard include/config/COMPAT_BRK) \
    $(wildcard include/config/CGROUPS) \
    $(wildcard include/config/BLK_CGROUP) \
    $(wildcard include/config/PSI) \
    $(wildcard include/config/PAGE_OWNER) \
    $(wildcard include/config/EVENTFD) \
    $(wildcard include/config/CPU_SUP_INTEL) \
    $(wildcard include/config/TASK_DELAY_ACCT) \
    $(wildcard include/config/ARCH_HAS_SCALED_CPUTIME) \
    $(wildcard include/config/VIRT_CPU_ACCOUNTING_GEN) \
    $(wildcard include/config/POSIX_CPUTIMERS) \
    $(wildcard include/config/POSIX_CPU_TIMERS_TASK_WORK) \
    $(wildcard include/config/KEYS) \
    $(wildcard include/config/DETECT_HUNG_TASK) \
    $(wildcard include/config/IO_URING) \
    $(wildcard include/config/AUDIT) \
    $(wildcard include/config/AUDITSYSCALL) \
    $(wildcard include/config/UBSAN) \
    $(wildcard include/config/UBSAN_TRAP) \
    $(wildcard include/config/TASK_XACCT) \
    $(wildcard include/config/CPUSETS) \
    $(wildcard include/config/X86_CPU_RESCTRL) \
    $(wildcard include/config/FUTEX) \
    $(wildcard include/config/PERF_EVENTS) \
    $(wildcard include/config/RSEQ) \
    $(wildcard include/config/FAULT_INJECTION) \
    $(wildcard include/config/LATENCYTOP) \
    $(wildcard include/config/FUNCTION_GRAPH_TRACER) \
    $(wildcard include/config/BCACHE) \
    $(wildcard include/config/VMAP_STACK) \
    $(wildcard include/config/BPF_SYSCALL) \
    $(wildcard include/config/GCC_PLUGIN_STACKLEAK) \
    $(wildcard include/config/X86_MCE) \
    $(wildcard include/config/KRETPROBES) \
    $(wildcard include/config/RETHOOK) \
    $(wildcard include/config/ARCH_HAS_PARANOID_L1D_FLUSH) \
    $(wildcard include/config/RV) \
    $(wildcard include/config/USER_EVENTS) \
    $(wildcard include/config/ARCH_TASK_STRUCT_ON_STACK) \
    $(wildcard include/config/PREEMPT_NONE) \
    $(wildcard include/config/PREEMPT_VOLUNTARY) \
    $(wildcard include/config/DEBUG_RSEQ) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/sched.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/pid.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/shm.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/shm.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/hugetlb_encode.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/shmbuf.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/shmbuf.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/shmparam.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kmsan_types.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/plist.h \
    $(wildcard include/config/DEBUG_PLIST) \
  /home/xuesong/linux/rt/linux-stable/include/linux/hrtimer.h \
    $(wildcard include/config/HIGH_RES_TIMERS) \
    $(wildcard include/config/TIME_LOW_RES) \
    $(wildcard include/config/TIMERFD) \
  /home/xuesong/linux/rt/linux-stable/include/linux/hrtimer_defs.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/timerqueue.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/seccomp.h \
    $(wildcard include/config/SECCOMP) \
    $(wildcard include/config/HAVE_ARCH_SECCOMP_FILTER) \
    $(wildcard include/config/SECCOMP_FILTER) \
    $(wildcard include/config/CHECKPOINT_RESTORE) \
    $(wildcard include/config/SECCOMP_CACHE_DEBUG) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/seccomp.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/seccomp.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/unistd.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/unistd.h \
  arch/x86/include/generated/uapi/asm/unistd_64.h \
  arch/x86/include/generated/asm/unistd_64_x32.h \
  arch/x86/include/generated/asm/unistd_32_ia32.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/ia32_unistd.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/seccomp.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/unistd.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/resource.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/resource.h \
  arch/x86/include/generated/uapi/asm/resource.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/resource.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/resource.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/latencytop.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/prio.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/types.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/signal_types.h \
    $(wildcard include/config/OLD_SIGACTION) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/signal.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/signal.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/signal.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/signal-defs.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/siginfo.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/siginfo.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/syscall_user_dispatch.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/task_io_accounting.h \
    $(wildcard include/config/TASK_IO_ACCOUNTING) \
  /home/xuesong/linux/rt/linux-stable/include/linux/posix-timers.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/alarmtimer.h \
    $(wildcard include/config/RTC_CLASS) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/rseq.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kcsan.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/rv.h \
    $(wildcard include/config/RV_REACTORS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/livepatch_sched.h \
  arch/x86/include/generated/asm/kmap_size.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/kmap_size.h \
    $(wildcard include/config/DEBUG_KMAP_LOCAL) \
  /home/xuesong/linux/rt/linux-stable/include/linux/sync_core.h \
    $(wildcard include/config/ARCH_HAS_SYNC_CORE_BEFORE_USERMODE) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/sync_core.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/radix-tree.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/capability.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/capability.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/semaphore.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/fcntl.h \
    $(wildcard include/config/ARCH_32BIT_OFF_T) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/fcntl.h \
  arch/x86/include/generated/uapi/asm/fcntl.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/fcntl.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/openat2.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/migrate_mode.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/percpu-rwsem.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/rcuwait.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/signal.h \
    $(wildcard include/config/SCHED_AUTOGROUP) \
    $(wildcard include/config/BSD_PROCESS_ACCT) \
    $(wildcard include/config/TASKSTATS) \
    $(wildcard include/config/STACK_GROWSUP) \
  /home/xuesong/linux/rt/linux-stable/include/linux/signal.h \
    $(wildcard include/config/DYNAMIC_SIGFRAME) \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/jobctl.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/task.h \
    $(wildcard include/config/HAVE_EXIT_THREAD) \
    $(wildcard include/config/ARCH_WANTS_DYNAMIC_TASK_STRUCT) \
    $(wildcard include/config/HAVE_ARCH_THREAD_STRUCT_WHITELIST) \
  /home/xuesong/linux/rt/linux-stable/include/linux/uaccess.h \
    $(wildcard include/config/ARCH_HAS_SUBPAGE_FAULTS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/fault-inject-usercopy.h \
    $(wildcard include/config/FAULT_INJECTION_USERCOPY) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/uaccess.h \
    $(wildcard include/config/CC_HAS_ASM_GOTO_OUTPUT) \
    $(wildcard include/config/CC_HAS_ASM_GOTO_TIED_OUTPUT) \
    $(wildcard include/config/X86_INTEL_USERCOPY) \
  /home/xuesong/linux/rt/linux-stable/include/linux/mmap_lock.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/smap.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/extable.h \
    $(wildcard include/config/BPF_JIT) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/tlbflush.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/mmu_notifier.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/interval_tree.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/invpcid.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/pti.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/pgtable.h \
    $(wildcard include/config/DEBUG_WX) \
    $(wildcard include/config/HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD) \
    $(wildcard include/config/ARCH_HAS_PTE_DEVMAP) \
    $(wildcard include/config/HAVE_ARCH_SOFT_DIRTY) \
    $(wildcard include/config/ARCH_ENABLE_THP_MIGRATION) \
    $(wildcard include/config/PAGE_TABLE_CHECK) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/pkru.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/fpu/api.h \
    $(wildcard include/config/X86_DEBUG_FPU) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/coco.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/pgtable_uffd.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/page_table_check.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/pgtable_64.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/fixmap.h \
    $(wildcard include/config/PROVIDE_OHCI1394_DMA_INIT) \
    $(wildcard include/config/X86_IO_APIC) \
    $(wildcard include/config/PCI_MMCONFIG) \
    $(wildcard include/config/ACPI_APEI_GHES) \
    $(wildcard include/config/INTEL_TXT) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/vsyscall.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/fixmap.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/pgtable-invert.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/uaccess_64.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/access_ok.h \
    $(wildcard include/config/ALTERNATE_USER_ADDRESS_SPACE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/cred.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/key.h \
    $(wildcard include/config/KEY_NOTIFICATIONS) \
    $(wildcard include/config/NET) \
  /home/xuesong/linux/rt/linux-stable/include/linux/assoc_array.h \
    $(wildcard include/config/ASSOCIATIVE_ARRAY) \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/user.h \
    $(wildcard include/config/VFIO_PCI_ZDEV_KVM) \
    $(wildcard include/config/IOMMUFD) \
    $(wildcard include/config/WATCH_QUEUE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/ratelimit.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/rcu_sync.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/delayed_call.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/uuid.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/errseq.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/ioprio.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/rt.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/iocontext.h \
    $(wildcard include/config/BLK_ICQ) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/ioprio.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/fs_types.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/mount.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/mnt_idmapping.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/slab.h \
    $(wildcard include/config/DEBUG_SLAB) \
    $(wildcard include/config/SLUB_TINY) \
    $(wildcard include/config/FAILSLAB) \
    $(wildcard include/config/KFENCE) \
    $(wildcard include/config/SLAB) \
    $(wildcard include/config/SLUB) \
  /home/xuesong/linux/rt/linux-stable/include/linux/percpu-refcount.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kasan.h \
    $(wildcard include/config/KASAN_STACK) \
    $(wildcard include/config/KASAN_VMALLOC) \
  /home/xuesong/linux/rt/linux-stable/include/linux/kasan-enabled.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/fs.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/quota.h \
    $(wildcard include/config/QUOTA_NETLINK_INTERFACE) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/dqblk_xfs.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/dqblk_v1.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/dqblk_v2.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/dqblk_qtree.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/projid.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/quota.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/aio_abi.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/compat.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/task_stack.h \
    $(wildcard include/config/DEBUG_STACK_USAGE) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/magic.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/user32.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/compat.h \
    $(wildcard include/config/COMPAT_FOR_U64_ALIGNMENT) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/syscall_wrapper.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/user.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/user_64.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/fsgsbase.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/vdso.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/elf.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/elf-em.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kobject.h \
    $(wildcard include/config/UEVENT_HELPER) \
    $(wildcard include/config/DEBUG_KOBJECT_RELEASE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/sysfs.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kernfs.h \
    $(wildcard include/config/KERNFS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/idr.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kobject_ns.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/moduleparam.h \
    $(wildcard include/config/ALPHA) \
    $(wildcard include/config/PPC64) \
  /home/xuesong/linux/rt/linux-stable/include/linux/rbtree_latch.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/error-injection.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/error-injection.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/module.h \
    $(wildcard include/config/UNWINDER_ORC) \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/module.h \
    $(wildcard include/config/HAVE_MOD_ARCH_SPECIFIC) \
    $(wildcard include/config/MODULES_USE_ELF_REL) \
    $(wildcard include/config/MODULES_USE_ELF_RELA) \
  /home/xuesong/linux/rt/linux-stable/include/linux/vmalloc.h \
    $(wildcard include/config/HAVE_ARCH_HUGE_VMALLOC) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/vmalloc.h \
    $(wildcard include/config/HAVE_ARCH_HUGE_VMAP) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/pgtable_areas.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/blkdev.h \
    $(wildcard include/config/BLOCK_HOLDER_DEPRECATED) \
    $(wildcard include/config/BLK_DEV_ZONED) \
    $(wildcard include/config/CDROM) \
    $(wildcard include/config/BLK_DEV_INTEGRITY) \
    $(wildcard include/config/PM) \
    $(wildcard include/config/BLK_INLINE_ENCRYPTION) \
    $(wildcard include/config/BLK_DEV_THROTTLING) \
    $(wildcard include/config/BLK_RQ_ALLOC_TIME) \
  /home/xuesong/linux/rt/linux-stable/include/linux/blk_types.h \
    $(wildcard include/config/FAIL_MAKE_REQUEST) \
    $(wildcard include/config/BLK_CGROUP_IOCOST) \
  /home/xuesong/linux/rt/linux-stable/include/linux/bvec.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/highmem.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/cacheflush.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/cacheflush.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/mm.h \
    $(wildcard include/config/HAVE_ARCH_MMAP_RND_BITS) \
    $(wildcard include/config/HAVE_ARCH_MMAP_RND_COMPAT_BITS) \
    $(wildcard include/config/ARCH_USES_HIGH_VMA_FLAGS) \
    $(wildcard include/config/ARCH_HAS_PKEYS) \
    $(wildcard include/config/PPC) \
    $(wildcard include/config/PARISC) \
    $(wildcard include/config/SPARC64) \
    $(wildcard include/config/ARM64_MTE) \
    $(wildcard include/config/HAVE_ARCH_USERFAULTFD_MINOR) \
    $(wildcard include/config/SHMEM) \
    $(wildcard include/config/MIGRATION) \
    $(wildcard include/config/ARCH_HAS_PTE_SPECIAL) \
    $(wildcard include/config/DEBUG_VM_RB) \
    $(wildcard include/config/PAGE_POISONING) \
    $(wildcard include/config/INIT_ON_ALLOC_DEFAULT_ON) \
    $(wildcard include/config/INIT_ON_FREE_DEFAULT_ON) \
    $(wildcard include/config/DEBUG_PAGEALLOC) \
    $(wildcard include/config/ARCH_WANT_OPTIMIZE_DAX_VMEMMAP) \
    $(wildcard include/config/HUGETLBFS) \
    $(wildcard include/config/MAPPING_DIRTY_HELPERS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/page_ext.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/stacktrace.h \
    $(wildcard include/config/ARCH_STACKWALK) \
    $(wildcard include/config/STACKTRACE) \
    $(wildcard include/config/HAVE_RELIABLE_STACKTRACE) \
  /home/xuesong/linux/rt/linux-stable/include/linux/stackdepot.h \
    $(wildcard include/config/STACKDEPOT_ALWAYS_INIT) \
    $(wildcard include/config/STACKDEPOT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/page_ref.h \
    $(wildcard include/config/DEBUG_PAGE_REF) \
  /home/xuesong/linux/rt/linux-stable/include/linux/sizes.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/pgtable.h \
    $(wildcard include/config/HIGHPTE) \
    $(wildcard include/config/ARCH_HAS_NONLEAF_PMD_YOUNG) \
    $(wildcard include/config/GUP_GET_PXX_LOW_HIGH) \
    $(wildcard include/config/ARCH_WANT_PMD_MKWRITE) \
    $(wildcard include/config/X86_ESPFIX64) \
  /home/xuesong/linux/rt/linux-stable/include/linux/memremap.h \
    $(wildcard include/config/DEVICE_PRIVATE) \
    $(wildcard include/config/PCI_P2PDMA) \
  /home/xuesong/linux/rt/linux-stable/include/linux/ioport.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/huge_mm.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/coredump.h \
    $(wildcard include/config/CORE_DUMP_DEFAULT_ELF_HEADERS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/vmstat.h \
    $(wildcard include/config/VM_EVENT_COUNTERS) \
    $(wildcard include/config/DEBUG_TLBFLUSH) \
    $(wildcard include/config/PER_VMA_LOCK_STATS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/vm_event_item.h \
    $(wildcard include/config/MEMORY_BALLOON) \
    $(wildcard include/config/BALLOON_COMPACTION) \
    $(wildcard include/config/ZSWAP) \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/cacheflush.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kmsan.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/dma-direction.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/hardirq.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/context_tracking_state.h \
    $(wildcard include/config/CONTEXT_TRACKING_USER) \
    $(wildcard include/config/CONTEXT_TRACKING) \
  /home/xuesong/linux/rt/linux-stable/include/linux/ftrace_irq.h \
    $(wildcard include/config/HWLAT_TRACER) \
    $(wildcard include/config/OSNOISE_TRACER) \
  /home/xuesong/linux/rt/linux-stable/include/linux/vtime.h \
    $(wildcard include/config/VIRT_CPU_ACCOUNTING) \
    $(wildcard include/config/IRQ_TIME_ACCOUNTING) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/hardirq.h \
    $(wildcard include/config/KVM_INTEL) \
    $(wildcard include/config/HAVE_KVM) \
    $(wildcard include/config/X86_THERMAL_VECTOR) \
    $(wildcard include/config/X86_MCE_THRESHOLD) \
    $(wildcard include/config/X86_MCE_AMD) \
    $(wildcard include/config/X86_HV_CALLBACK_VECTOR) \
    $(wildcard include/config/HYPERV) \
  /home/xuesong/linux/rt/linux-stable/include/linux/highmem-internal.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/device.h \
    $(wildcard include/config/HAS_IOMEM) \
    $(wildcard include/config/GENERIC_MSI_IRQ) \
    $(wildcard include/config/ENERGY_MODEL) \
    $(wildcard include/config/PINCTRL) \
    $(wildcard include/config/DMA_OPS) \
    $(wildcard include/config/DMA_DECLARE_COHERENT) \
    $(wildcard include/config/DMA_CMA) \
    $(wildcard include/config/SWIOTLB) \
    $(wildcard include/config/SWIOTLB_DYNAMIC) \
    $(wildcard include/config/ARCH_HAS_SYNC_DMA_FOR_DEVICE) \
    $(wildcard include/config/ARCH_HAS_SYNC_DMA_FOR_CPU) \
    $(wildcard include/config/ARCH_HAS_SYNC_DMA_FOR_CPU_ALL) \
    $(wildcard include/config/DMA_OPS_BYPASS) \
    $(wildcard include/config/PM_SLEEP) \
    $(wildcard include/config/OF) \
    $(wildcard include/config/DEVTMPFS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/dev_printk.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/energy_model.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/cpufreq.h \
    $(wildcard include/config/CPU_FREQ) \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/topology.h \
    $(wildcard include/config/SCHED_DEBUG) \
    $(wildcard include/config/SCHED_CLUSTER) \
    $(wildcard include/config/SCHED_MC) \
    $(wildcard include/config/CPU_FREQ_GOV_SCHEDUTIL) \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/idle.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/sched/sd_flags.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/klist.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/pm.h \
    $(wildcard include/config/VT_CONSOLE_SLEEP) \
    $(wildcard include/config/CXL_SUSPEND) \
    $(wildcard include/config/PM_CLK) \
    $(wildcard include/config/PM_GENERIC_DOMAINS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/device/bus.h \
    $(wildcard include/config/ACPI) \
  /home/xuesong/linux/rt/linux-stable/include/linux/device/class.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/device/driver.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/device.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/pm_wakeup.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/bio.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/mempool.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/blkzoned.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/sbitmap.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/hdreg.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/blk-mq.h \
    $(wildcard include/config/BLK_WBT) \
    $(wildcard include/config/BLK_DEBUG_FS) \
    $(wildcard include/config/FAIL_IO_TIMEOUT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/scatterlist.h \
    $(wildcard include/config/NEED_SG_DMA_LENGTH) \
    $(wildcard include/config/NEED_SG_DMA_FLAGS) \
    $(wildcard include/config/DEBUG_SG) \
    $(wildcard include/config/SGL_ALLOC) \
    $(wildcard include/config/ARCH_NO_SG_CHAIN) \
    $(wildcard include/config/SG_POOL) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/io.h \
    $(wildcard include/config/MTRR) \
    $(wildcard include/config/X86_PAT) \
  arch/x86/include/generated/asm/early_ioremap.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/early_ioremap.h \
    $(wildcard include/config/GENERIC_EARLY_IOREMAP) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/shared/io.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/io.h \
    $(wildcard include/config/GENERIC_IOMAP) \
    $(wildcard include/config/TRACE_MMIO_ACCESS) \
    $(wildcard include/config/GENERIC_IOREMAP) \
    $(wildcard include/config/HAS_IOPORT_MAP) \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/iomap.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/pci_iomap.h \
    $(wildcard include/config/PCI) \
    $(wildcard include/config/NO_GENERIC_PCI_IOPORT_MAP) \
    $(wildcard include/config/GENERIC_PCI_IOMAP) \
  /home/xuesong/linux/rt/linux-stable/include/linux/logic_pio.h \
    $(wildcard include/config/INDIRECT_PIO) \
  /home/xuesong/linux/rt/linux-stable/include/linux/fwnode.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/prefetch.h \
  /home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/ramhd_mq.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/tracepoint.h \
    $(wildcard include/config/HAVE_SYSCALL_TRACEPOINTS) \
    $(wildcard include/config/ARCH_WANTS_NO_INSTR) \
  /home/xuesong/linux/rt/linux-stable/include/linux/static_call.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/cpu.h \
    $(wildcard include/config/PM_SLEEP_SMP) \
    $(wildcard include/config/PM_SLEEP_SMP_NONZERO_CPU) \
    $(wildcard include/config/ARCH_HAS_CPU_FINALIZE_INIT) \
  /home/xuesong/linux/rt/linux-stable/include/linux/node.h \
    $(wildcard include/config/HMEM_REPORTING) \
  /home/xuesong/linux/rt/linux-stable/include/linux/cpuhotplug.h \
    $(wildcard include/config/HOTPLUG_CORE_SYNC_DEAD) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/static_call.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/text-patching.h \
    $(wildcard include/config/UML_X86) \
  /home/xuesong/linux/rt/linux-stable/include/trace/define_trace.h \
  /home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/./ramhd_mq.h \
  /home/xuesong/linux/rt/linux-stable/include/trace/trace_events.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/trace_events.h \
    $(wildcard include/config/DYNAMIC_EVENTS) \
    $(wildcard include/config/KPROBE_EVENTS) \
    $(wildcard include/config/UPROBE_EVENTS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/ring_buffer.h \
    $(wildcard include/config/RING_BUFFER_ALLOW_SWAP) \
    $(wildcard include/config/RING_BUFFER) \
  /home/xuesong/linux/rt/linux-stable/include/linux/seq_file.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/string_helpers.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/ctype.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/string_choices.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/poll.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/poll.h \
  arch/x86/include/generated/uapi/asm/poll.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/poll.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/eventpoll.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/trace_seq.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/seq_buf.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/perf_event.h \
    $(wildcard include/config/HAVE_HW_BREAKPOINT) \
    $(wildcard include/config/FUNCTION_TRACER) \
    $(wildcard include/config/CGROUP_PERF) \
    $(wildcard include/config/GUEST_PERF_EVENTS) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/perf_event.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/bpf_perf_event.h \
  arch/x86/include/generated/uapi/asm/bpf_perf_event.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/asm-generic/bpf_perf_event.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/ptrace.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/pid_namespace.h \
    $(wildcard include/config/MEMFD_CREATE) \
    $(wildcard include/config/PID_NS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/nsproxy.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/ns_common.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/ptrace.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/perf_event.h \
    $(wildcard include/config/PERF_EVENTS_AMD_BRS) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/stacktrace.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/cpu_entry_area.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/intel_ds.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/switch_to.h \
  arch/x86/include/generated/asm/local64.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/local64.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/local.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/hw_breakpoint.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/hw_breakpoint.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kdebug.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/kdebug.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/ftrace.h \
    $(wildcard include/config/HAVE_FUNCTION_GRAPH_RETVAL) \
    $(wildcard include/config/DYNAMIC_FTRACE) \
    $(wildcard include/config/HAVE_DYNAMIC_FTRACE_WITH_ARGS) \
    $(wildcard include/config/DYNAMIC_FTRACE_WITH_REGS) \
    $(wildcard include/config/DYNAMIC_FTRACE_WITH_ARGS) \
    $(wildcard include/config/DYNAMIC_FTRACE_WITH_DIRECT_CALLS) \
    $(wildcard include/config/STACK_TRACER) \
    $(wildcard include/config/DYNAMIC_FTRACE_WITH_CALL_OPS) \
    $(wildcard include/config/FUNCTION_GRAPH_RETVAL) \
    $(wildcard include/config/FUNCTION_PROFILER) \
    $(wildcard include/config/FTRACE_SYSCALLS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/trace_recursion.h \
    $(wildcard include/config/FTRACE_RECORD_RECURSION) \
  /home/xuesong/linux/rt/linux-stable/include/linux/interrupt.h \
    $(wildcard include/config/IRQ_FORCED_THREADING) \
    $(wildcard include/config/GENERIC_IRQ_PROBE) \
    $(wildcard include/config/IRQ_TIMINGS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/irqreturn.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/irq.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/irq_vectors.h \
    $(wildcard include/config/PCI_MSI) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/sections.h \
  /home/xuesong/linux/rt/linux-stable/include/asm-generic/sections.h \
    $(wildcard include/config/HAVE_FUNCTION_DESCRIPTORS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/trace_clock.h \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/trace_clock.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kallsyms.h \
    $(wildcard include/config/KALLSYMS_ALL) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/ftrace.h \
    $(wildcard include/config/HAVE_FENTRY) \
  /home/xuesong/linux/rt/linux-stable/include/linux/irq_work.h \
    $(wildcard include/config/IRQ_WORK) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/asm/irq_work.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/jump_label_ratelimit.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/perf_regs.h \
    $(wildcard include/config/HAVE_PERF_REGS) \
  /home/xuesong/linux/rt/linux-stable/arch/x86/include/uapi/asm/perf_regs.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/cgroup.h \
    $(wildcard include/config/DEBUG_CGROUP_REF) \
    $(wildcard include/config/CGROUP_CPUACCT) \
    $(wildcard include/config/SOCK_CGROUP_DATA) \
    $(wildcard include/config/CGROUP_DATA) \
    $(wildcard include/config/CGROUP_BPF) \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/cgroupstats.h \
  /home/xuesong/linux/rt/linux-stable/include/uapi/linux/taskstats.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/user_namespace.h \
    $(wildcard include/config/INOTIFY_USER) \
    $(wildcard include/config/FANOTIFY) \
    $(wildcard include/config/BINFMT_MISC) \
    $(wildcard include/config/PERSISTENT_KEYRINGS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/kernel_stat.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/cgroup-defs.h \
    $(wildcard include/config/CGROUP_NET_CLASSID) \
    $(wildcard include/config/CGROUP_NET_PRIO) \
  /home/xuesong/linux/rt/linux-stable/include/linux/u64_stats_sync.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/bpf-cgroup-defs.h \
    $(wildcard include/config/BPF_LSM) \
  /home/xuesong/linux/rt/linux-stable/include/linux/psi_types.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/kthread.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/cgroup_subsys.h \
    $(wildcard include/config/CGROUP_DEVICE) \
    $(wildcard include/config/CGROUP_FREEZER) \
    $(wildcard include/config/CGROUP_HUGETLB) \
    $(wildcard include/config/CGROUP_PIDS) \
    $(wildcard include/config/CGROUP_RDMA) \
    $(wildcard include/config/CGROUP_MISC) \
    $(wildcard include/config/CGROUP_DEBUG) \
  /home/xuesong/linux/rt/linux-stable/include/linux/cgroup_refcnt.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/security.h \
    $(wildcard include/config/SECURITY_NETWORK) \
    $(wildcard include/config/SECURITY_INFINIBAND) \
    $(wildcard include/config/SECURITY_NETWORK_XFRM) \
    $(wildcard include/config/SECURITY_PATH) \
    $(wildcard include/config/SECURITYFS) \
  /home/xuesong/linux/rt/linux-stable/include/linux/kernel_read_file.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/file.h \
  /home/xuesong/linux/rt/linux-stable/include/linux/sockptr.h \
  /home/xuesong/linux/rt/linux-stable/include/trace/stages/init.h \
  /home/xuesong/linux/rt/linux-stable/include/trace/stages/stage1_struct_define.h \
  /home/xuesong/linux/rt/linux-stable/include/trace/stages/stage2_data_offsets.h \
  /home/xuesong/linux/rt/linux-stable/include/trace/stages/stage3_trace_output.h \
  /home/xuesong/linux/rt/linux-stable/include/trace/stages/stage4_event_fields.h \
  /home/xuesong/linux/rt/linux-stable/include/trace/stages/stage5_get_offsets.h \
  /home/xuesong/linux/rt/linux-stable/include/trace/stages/stage6_event_callback.h \
  /home/xuesong/linux/rt/linux-stable/include/trace/stages/stage7_class_define.h \
  /home/xuesong/linux/rt/linux-stable/include/trace/perf.h \
  /home/xuesong/linux/rt/linux-stable/include/trace/bpf_probe.h \

/home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/ramhd_mq.o: $(deps_/home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/ramhd_mq.o)

$(deps_/home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/ramhd_mq.o):

/home/xuesong/linux/trainings/llddv2/block/blk_mq_ram/ramhd_mq.o: $(wildcard ./tools/objtool/objtool)
#SYMVER get_ramhd_base 0x9c8074d6
