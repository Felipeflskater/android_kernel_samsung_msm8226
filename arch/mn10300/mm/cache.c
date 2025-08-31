/* MN10300 Cache flushing routines
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version
 * 2 of the Licence, or (at your option) any later version.
 */
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/threads.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/processor.h>
#include <asm/cacheflush.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/smp.h>
#include "cache-smp.h"

/* DISABLED: EXPORT_SYMBOL(mn10300_icache_inv); */
/* DISABLED: EXPORT_SYMBOL(mn10300_icache_inv_range); */
/* DISABLED: EXPORT_SYMBOL(mn10300_icache_inv_range2); */
/* DISABLED: EXPORT_SYMBOL(mn10300_icache_inv_page); */
/* DISABLED: EXPORT_SYMBOL(mn10300_dcache_inv); */
/* DISABLED: EXPORT_SYMBOL(mn10300_dcache_inv_range); */
/* DISABLED: EXPORT_SYMBOL(mn10300_dcache_inv_range2); */
/* DISABLED: EXPORT_SYMBOL(mn10300_dcache_inv_page); */

#ifdef CONFIG_MN10300_CACHE_WBACK
/* DISABLED: EXPORT_SYMBOL(mn10300_dcache_flush); */
/* DISABLED: EXPORT_SYMBOL(mn10300_dcache_flush_inv); */
/* DISABLED: EXPORT_SYMBOL(mn10300_dcache_flush_inv_range); */
/* DISABLED: EXPORT_SYMBOL(mn10300_dcache_flush_inv_range2); */
/* DISABLED: EXPORT_SYMBOL(mn10300_dcache_flush_inv_page); */
/* DISABLED: EXPORT_SYMBOL(mn10300_dcache_flush_range); */
/* DISABLED: EXPORT_SYMBOL(mn10300_dcache_flush_range2); */
/* DISABLED: EXPORT_SYMBOL(mn10300_dcache_flush_page); */
#endif

/*
 * allow userspace to flush the instruction cache
 */
asmlinkage long sys_cacheflush(unsigned long start, unsigned long end)
{
	if (end < start)
		return -EINVAL;

	flush_icache_range(start, end);
	return 0;
}
