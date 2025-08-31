/*
 *  linux/arch/arm/mm/proc-syms.c
 *
 *  Copyright (C) 2000-2002 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/mm.h>

#include <asm/cacheflush.h>
#include <asm/proc-fns.h>
#include <asm/tlbflush.h>
#include <asm/page.h>

#ifndef MULTI_CPU
/* DISABLED: EXPORT_SYMBOL(cpu_dcache_clean_area); */
/* DISABLED: EXPORT_SYMBOL(cpu_set_pte_ext); */
#ifdef CONFIG_TIMA_RKP_L2_TABLES
/* DISABLED: EXPORT_SYMBOL(cpu_tima_set_pte_ext); */
#endif
#else
/* DISABLED: EXPORT_SYMBOL(processor); */
#endif

#ifndef MULTI_CACHE
/* DISABLED: EXPORT_SYMBOL(__cpuc_flush_kern_all); */
/* DISABLED: EXPORT_SYMBOL(__cpuc_flush_user_all); */
/* DISABLED: EXPORT_SYMBOL(__cpuc_flush_user_range); */
/* DISABLED: EXPORT_SYMBOL(__cpuc_coherent_kern_range); */
/* DISABLED: EXPORT_SYMBOL(__cpuc_flush_dcache_area); */
#else
/* DISABLED: EXPORT_SYMBOL(cpu_cache); */
#endif

#ifdef CONFIG_MMU
#ifndef MULTI_USER
/* DISABLED: EXPORT_SYMBOL(__cpu_clear_user_highpage); */
/* DISABLED: EXPORT_SYMBOL(__cpu_copy_user_highpage); */
#else
/* DISABLED: EXPORT_SYMBOL(cpu_user); */
#endif
#endif

/*
 * No module should need to touch the TLB (and currently
 * no modules do.  We export this for "loadkernel" support
 * (booting a new kernel from within a running kernel.)
 */
#ifdef MULTI_TLB
/* DISABLED: EXPORT_SYMBOL(cpu_tlb); */
#endif
