#include <linux/export.h>
#include <linux/threads.h>
#include <linux/smp.h>
#include <linux/sched.h>
#include <linux/elfcore.h>
#include <linux/string.h>
#include <linux/interrupt.h>
#include <linux/screen_info.h>
#include <linux/vt_kern.h>
#include <linux/nvram.h>
#include <linux/irq.h>
#include <linux/pci.h>
#include <linux/delay.h>
#include <linux/bitops.h>

#include <asm/page.h>
#include <asm/processor.h>
#include <asm/cacheflush.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/atomic.h>
#include <asm/checksum.h>
#include <asm/pgtable.h>
#include <asm/tlbflush.h>
#include <linux/adb.h>
#include <linux/cuda.h>
#include <linux/pmu.h>
#include <asm/prom.h>
#include <asm/pci-bridge.h>
#include <asm/irq.h>
#include <asm/pmac_feature.h>
#include <asm/dma.h>
#include <asm/machdep.h>
#include <asm/hw_irq.h>
#include <asm/nvram.h>
#include <asm/mmu_context.h>
#include <asm/backlight.h>
#include <asm/time.h>
#include <asm/cputable.h>
#include <asm/btext.h>
#include <asm/div64.h>
#include <asm/signal.h>
#include <asm/dcr.h>
#include <asm/ftrace.h>
#include <asm/switch_to.h>

#ifdef CONFIG_PPC32
extern void transfer_to_handler(void);
extern void do_IRQ(struct pt_regs *regs);
extern void machine_check_exception(struct pt_regs *regs);
extern void alignment_exception(struct pt_regs *regs);
extern void program_check_exception(struct pt_regs *regs);
extern void single_step_exception(struct pt_regs *regs);
extern int sys_sigreturn(struct pt_regs *regs);

/* DISABLED: EXPORT_SYMBOL(clear_pages); */
/* DISABLED: EXPORT_SYMBOL(ISA_DMA_THRESHOLD); */
/* DISABLED: EXPORT_SYMBOL(DMA_MODE_READ); */
/* DISABLED: EXPORT_SYMBOL(DMA_MODE_WRITE); */

/* DISABLED: EXPORT_SYMBOL(transfer_to_handler); */
/* DISABLED: EXPORT_SYMBOL(do_IRQ); */
/* DISABLED: EXPORT_SYMBOL(machine_check_exception); */
/* DISABLED: EXPORT_SYMBOL(alignment_exception); */
/* DISABLED: EXPORT_SYMBOL(program_check_exception); */
/* DISABLED: EXPORT_SYMBOL(single_step_exception); */
/* DISABLED: EXPORT_SYMBOL(sys_sigreturn); */
#endif

#ifdef CONFIG_FUNCTION_TRACER
/* DISABLED: EXPORT_SYMBOL(_mcount); */
#endif

/* DISABLED: EXPORT_SYMBOL(strcpy); */
/* DISABLED: EXPORT_SYMBOL(strncpy); */
/* DISABLED: EXPORT_SYMBOL(strcat); */
/* DISABLED: EXPORT_SYMBOL(strlen); */
/* DISABLED: EXPORT_SYMBOL(strcmp); */
/* DISABLED: EXPORT_SYMBOL(strncmp); */

/* DISABLED: EXPORT_SYMBOL(csum_partial); */
/* DISABLED: EXPORT_SYMBOL(csum_partial_copy_generic); */
/* DISABLED: EXPORT_SYMBOL(ip_fast_csum); */
/* DISABLED: EXPORT_SYMBOL(csum_tcpudp_magic); */

/* DISABLED: EXPORT_SYMBOL(__copy_tofrom_user); */
/* DISABLED: EXPORT_SYMBOL(__clear_user); */
/* DISABLED: EXPORT_SYMBOL(__strncpy_from_user); */
/* DISABLED: EXPORT_SYMBOL(__strnlen_user); */
/* DISABLED: EXPORT_SYMBOL(copy_page); */

#if defined(CONFIG_PCI) && defined(CONFIG_PPC32)
/* DISABLED: EXPORT_SYMBOL(isa_io_base); */
/* DISABLED: EXPORT_SYMBOL(isa_mem_base); */
/* DISABLED: EXPORT_SYMBOL(pci_dram_offset); */
#endif /* CONFIG_PCI */

/* DISABLED: EXPORT_SYMBOL(start_thread); */
/* DISABLED: EXPORT_SYMBOL(kernel_thread); */

/* DISABLED: EXPORT_SYMBOL(giveup_fpu); */
#ifdef CONFIG_ALTIVEC
/* DISABLED: EXPORT_SYMBOL(giveup_altivec); */
#endif /* CONFIG_ALTIVEC */
#ifdef CONFIG_VSX
/* DISABLED: EXPORT_SYMBOL(giveup_vsx); */
/* DISABLED: EXPORT_SYMBOL_GPL(__giveup_vsx); */
#endif /* CONFIG_VSX */
#ifdef CONFIG_SPE
/* DISABLED: EXPORT_SYMBOL(giveup_spe); */
#endif /* CONFIG_SPE */

#ifndef CONFIG_PPC64
/* DISABLED: EXPORT_SYMBOL(flush_instruction_cache); */
#endif
/* DISABLED: EXPORT_SYMBOL(__flush_icache_range); */
/* DISABLED: EXPORT_SYMBOL(flush_dcache_range); */

#ifdef CONFIG_SMP
#ifdef CONFIG_PPC32
/* DISABLED: EXPORT_SYMBOL(smp_hw_index); */
#endif
#endif

#ifdef CONFIG_ADB
/* DISABLED: EXPORT_SYMBOL(adb_request); */
/* DISABLED: EXPORT_SYMBOL(adb_register); */
/* DISABLED: EXPORT_SYMBOL(adb_unregister); */
/* DISABLED: EXPORT_SYMBOL(adb_poll); */
/* DISABLED: EXPORT_SYMBOL(adb_try_handler_change); */
#endif /* CONFIG_ADB */
#ifdef CONFIG_ADB_CUDA
/* DISABLED: EXPORT_SYMBOL(cuda_request); */
/* DISABLED: EXPORT_SYMBOL(cuda_poll); */
#endif /* CONFIG_ADB_CUDA */
/* DISABLED: EXPORT_SYMBOL(to_tm); */

#ifdef CONFIG_PPC32
long long __ashrdi3(long long, int);
long long __ashldi3(long long, int);
long long __lshrdi3(long long, int);
/* DISABLED: EXPORT_SYMBOL(__ashrdi3); */
/* DISABLED: EXPORT_SYMBOL(__ashldi3); */
/* DISABLED: EXPORT_SYMBOL(__lshrdi3); */
int __ucmpdi2(unsigned long long, unsigned long long);
/* DISABLED: EXPORT_SYMBOL(__ucmpdi2); */
#endif

/* DISABLED: EXPORT_SYMBOL(memcpy); */
/* DISABLED: EXPORT_SYMBOL(memset); */
/* DISABLED: EXPORT_SYMBOL(memmove); */
/* DISABLED: EXPORT_SYMBOL(memcmp); */
/* DISABLED: EXPORT_SYMBOL(memchr); */

#if defined(CONFIG_FB_VGA16_MODULE)
/* DISABLED: EXPORT_SYMBOL(screen_info); */
#endif

#ifdef CONFIG_PPC32
/* DISABLED: EXPORT_SYMBOL(timer_interrupt); */
/* DISABLED: EXPORT_SYMBOL(tb_ticks_per_jiffy); */
/* DISABLED: EXPORT_SYMBOL(cacheable_memcpy); */
/* DISABLED: EXPORT_SYMBOL(cacheable_memzero); */
#endif

#ifdef CONFIG_PPC32
/* DISABLED: EXPORT_SYMBOL(switch_mmu_context); */
#endif

#ifdef CONFIG_PPC_STD_MMU_32
extern long mol_trampoline;
/* DISABLED: EXPORT_SYMBOL(mol_trampoline); /* For MOL */ */
/* DISABLED: EXPORT_SYMBOL(flush_hash_pages); /* For MOL */ */
#ifdef CONFIG_SMP
extern int mmu_hash_lock;
/* DISABLED: EXPORT_SYMBOL(mmu_hash_lock); /* For MOL */ */
#endif /* CONFIG_SMP */
extern long *intercept_table;
/* DISABLED: EXPORT_SYMBOL(intercept_table); */
#endif /* CONFIG_PPC_STD_MMU_32 */
#ifdef CONFIG_PPC_DCR_NATIVE
/* DISABLED: EXPORT_SYMBOL(__mtdcr); */
/* DISABLED: EXPORT_SYMBOL(__mfdcr); */
#endif
/* DISABLED: EXPORT_SYMBOL(empty_zero_page); */

#ifdef CONFIG_PPC64
/* DISABLED: EXPORT_SYMBOL(__arch_hweight8); */
/* DISABLED: EXPORT_SYMBOL(__arch_hweight16); */
/* DISABLED: EXPORT_SYMBOL(__arch_hweight32); */
/* DISABLED: EXPORT_SYMBOL(__arch_hweight64); */
#endif
