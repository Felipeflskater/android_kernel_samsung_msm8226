/*
 * arch/blackfin/kernel/bfin_ksyms.c - exports for random symbols
 *
 * Copyright 2004-2008 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#include <linux/module.h>
#include <linux/uaccess.h>

#include <asm/cacheflush.h>
#include <asm/io.h>
#include <asm/irq_handler.h>

/* Allow people to have their own Blackfin exception handler in a module */
/* DISABLED: EXPORT_SYMBOL(bfin_return_from_exception); */

/* All the Blackfin cache functions: mach-common/cache.S */
/* DISABLED: EXPORT_SYMBOL(blackfin_dcache_invalidate_range); */
/* DISABLED: EXPORT_SYMBOL(blackfin_icache_flush_range); */
/* DISABLED: EXPORT_SYMBOL(blackfin_dcache_flush_range); */
/* DISABLED: EXPORT_SYMBOL(blackfin_dflush_page); */

/* The following are special because they're not called
 * explicitly (the C compiler generates them).  Fortunately,
 * their interface isn't gonna change any time soon now, so
 * it's OK to leave it out of version control.
 */
/* DISABLED: EXPORT_SYMBOL(memcpy); */
/* DISABLED: EXPORT_SYMBOL(memset); */
/* DISABLED: EXPORT_SYMBOL(memcmp); */
/* DISABLED: EXPORT_SYMBOL(memmove); */
/* DISABLED: EXPORT_SYMBOL(memchr); */

/*
 * Because string functions are both inline and exported functions and
 * folder arch/blackfin/lib is configured as a library path in Makefile,
 * symbols exported in folder lib  is not linked into built-in.o but
 * inlined only. In order to export string symbols to kernel module
 * properly, they should be exported here.
 */
/* DISABLED: EXPORT_SYMBOL(strcpy); */
/* DISABLED: EXPORT_SYMBOL(strncpy); */
/* DISABLED: EXPORT_SYMBOL(strcmp); */
/* DISABLED: EXPORT_SYMBOL(strncmp); */

/*
 * libgcc functions - functions that are used internally by the
 * compiler...  (prototypes are not correct though, but that
 * doesn't really matter since they're not versioned).
 */
extern void __ashldi3(void);
extern void __ashrdi3(void);
extern void __smulsi3_highpart(void);
extern void __umulsi3_highpart(void);
extern void __divsi3(void);
extern void __lshrdi3(void);
extern void __modsi3(void);
extern void __muldi3(void);
extern void __udivsi3(void);
extern void __umodsi3(void);
/* DISABLED: EXPORT_SYMBOL(__ashldi3); */
/* DISABLED: EXPORT_SYMBOL(__ashrdi3); */
/* DISABLED: EXPORT_SYMBOL(__umulsi3_highpart); */
/* DISABLED: EXPORT_SYMBOL(__smulsi3_highpart); */
/* DISABLED: EXPORT_SYMBOL(__divsi3); */
/* DISABLED: EXPORT_SYMBOL(__lshrdi3); */
/* DISABLED: EXPORT_SYMBOL(__modsi3); */
/* DISABLED: EXPORT_SYMBOL(__muldi3); */
/* DISABLED: EXPORT_SYMBOL(__udivsi3); */
/* DISABLED: EXPORT_SYMBOL(__umodsi3); */

/* Input/output symbols: lib/{in,out}s.S */
/* DISABLED: EXPORT_SYMBOL(outsb); */
/* DISABLED: EXPORT_SYMBOL(insb); */
/* DISABLED: EXPORT_SYMBOL(outsw); */
/* DISABLED: EXPORT_SYMBOL(outsw_8); */
/* DISABLED: EXPORT_SYMBOL(insw); */
/* DISABLED: EXPORT_SYMBOL(insw_8); */
/* DISABLED: EXPORT_SYMBOL(outsl); */
/* DISABLED: EXPORT_SYMBOL(insl); */
/* DISABLED: EXPORT_SYMBOL(insl_16); */

#ifdef CONFIG_SMP
/* DISABLED: EXPORT_SYMBOL(__raw_atomic_update_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_atomic_clear_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_atomic_set_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_atomic_xor_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_atomic_test_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_xchg_1_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_xchg_2_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_xchg_4_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_cmpxchg_1_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_cmpxchg_2_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_cmpxchg_4_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_spin_is_locked_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_spin_lock_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_spin_trylock_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_spin_unlock_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_read_lock_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_read_trylock_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_read_unlock_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_write_lock_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_write_trylock_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_write_unlock_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_bit_set_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_bit_clear_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_bit_toggle_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_bit_test_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_bit_test_set_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_bit_test_clear_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_bit_test_toggle_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_uncached_fetch_asm); */
#ifdef __ARCH_SYNC_CORE_DCACHE
/* DISABLED: EXPORT_SYMBOL(__raw_smp_mark_barrier_asm); */
/* DISABLED: EXPORT_SYMBOL(__raw_smp_check_barrier_asm); */
#endif
#endif

#ifdef CONFIG_FUNCTION_TRACER
extern void _mcount(void);
/* DISABLED: EXPORT_SYMBOL(_mcount); */
#endif
