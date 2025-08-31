#include <linux/module.h>
#include <linux/linkage.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/user.h>
#include <linux/elfcore.h>
#include <linux/in6.h>
#include <linux/interrupt.h>

#include <asm/setup.h>
#include <asm/pgalloc.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/checksum.h>
#include <asm/hardirq.h>
#include <asm/cacheflush.h>

extern long __memcpy_user(void *dst, const void *src, size_t count);
extern long __memset_user(void *dst, const void *src, size_t count);

/* platform dependent support */

/* DISABLED: EXPORT_SYMBOL(__ioremap); */
/* DISABLED: EXPORT_SYMBOL(iounmap); */

/* DISABLED: EXPORT_SYMBOL(ip_fast_csum); */

#if 0
/* DISABLED: EXPORT_SYMBOL(local_irq_count); */
/* DISABLED: EXPORT_SYMBOL(local_bh_count); */
#endif
/* DISABLED: EXPORT_SYMBOL(kernel_thread); */

/* DISABLED: EXPORT_SYMBOL(__res_bus_clock_speed_HZ); */
/* DISABLED: EXPORT_SYMBOL(__page_offset); */
/* DISABLED: EXPORT_SYMBOL(__memcpy_user); */
/* DISABLED: EXPORT_SYMBOL(__memset_user); */
/* DISABLED: EXPORT_SYMBOL(frv_dcache_writeback); */
/* DISABLED: EXPORT_SYMBOL(frv_cache_invalidate); */
/* DISABLED: EXPORT_SYMBOL(frv_icache_invalidate); */
/* DISABLED: EXPORT_SYMBOL(frv_cache_wback_inv); */

#ifndef CONFIG_MMU
/* DISABLED: EXPORT_SYMBOL(memory_start); */
/* DISABLED: EXPORT_SYMBOL(memory_end); */
#endif

/* DISABLED: EXPORT_SYMBOL(__debug_bug_trap); */

/* The following are special because they're not called
   explicitly (the C compiler generates them).  Fortunately,
   their interface isn't gonna change any time soon now, so
   it's OK to leave it out of version control.  */
/* DISABLED: EXPORT_SYMBOL(memcpy); */
/* DISABLED: EXPORT_SYMBOL(memset); */

/* DISABLED: EXPORT_SYMBOL(__outsl_ns); */
/* DISABLED: EXPORT_SYMBOL(__insl_ns); */

#ifdef CONFIG_FRV_OUTOFLINE_ATOMIC_OPS
/* DISABLED: EXPORT_SYMBOL(atomic_test_and_ANDNOT_mask); */
/* DISABLED: EXPORT_SYMBOL(atomic_test_and_OR_mask); */
/* DISABLED: EXPORT_SYMBOL(atomic_test_and_XOR_mask); */
/* DISABLED: EXPORT_SYMBOL(atomic_add_return); */
/* DISABLED: EXPORT_SYMBOL(atomic_sub_return); */
/* DISABLED: EXPORT_SYMBOL(__xchg_32); */
/* DISABLED: EXPORT_SYMBOL(__cmpxchg_32); */
#endif
/* DISABLED: EXPORT_SYMBOL(atomic64_add_return); */
/* DISABLED: EXPORT_SYMBOL(atomic64_sub_return); */
/* DISABLED: EXPORT_SYMBOL(__xchg_64); */
/* DISABLED: EXPORT_SYMBOL(__cmpxchg_64); */

/* DISABLED: EXPORT_SYMBOL(__debug_bug_printk); */
/* DISABLED: EXPORT_SYMBOL(__delay_loops_MHz); */

/*
 * libgcc functions - functions that are used internally by the
 * compiler...  (prototypes are not correct though, but that
 * doesn't really matter since they're not versioned).
 */
extern void __gcc_bcmp(void);
extern void __ashldi3(void);
extern void __ashrdi3(void);
extern void __cmpdi2(void);
extern void __divdi3(void);
extern void __lshrdi3(void);
extern void __moddi3(void);
extern void __muldi3(void);
extern void __mulll(void);
extern void __umulll(void);
extern void __negdi2(void);
extern void __ucmpdi2(void);
extern void __udivdi3(void);
extern void __udivmoddi4(void);
extern void __umoddi3(void);

        /* gcc lib functions */
//EXPORT_SYMBOL(__gcc_bcmp);
/* DISABLED: EXPORT_SYMBOL(__ashldi3); */
/* DISABLED: EXPORT_SYMBOL(__ashrdi3); */
//EXPORT_SYMBOL(__cmpdi2);
//EXPORT_SYMBOL(__divdi3);
/* DISABLED: EXPORT_SYMBOL(__lshrdi3); */
//EXPORT_SYMBOL(__moddi3);
/* DISABLED: EXPORT_SYMBOL(__muldi3); */
/* DISABLED: EXPORT_SYMBOL(__mulll); */
/* DISABLED: EXPORT_SYMBOL(__umulll); */
/* DISABLED: EXPORT_SYMBOL(__negdi2); */
/* DISABLED: EXPORT_SYMBOL(__ucmpdi2); */
//EXPORT_SYMBOL(__udivdi3);
//EXPORT_SYMBOL(__udivmoddi4);
//EXPORT_SYMBOL(__umoddi3);
