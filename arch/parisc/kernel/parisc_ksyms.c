/*
 *    Architecture-specific kernel symbols
 *
 *    Copyright (C) 2000-2001 Richard Hirst <rhirst with parisc-linux.org>
 *    Copyright (C) 2001 Dave Kennedy
 *    Copyright (C) 2001 Paul Bame <bame at parisc-linux.org>
 *    Copyright (C) 2001-2003 Grant Grundler <grundler with parisc-linux.org>
 *    Copyright (C) 2002-2003 Matthew Wilcox <willy at parisc-linux.org>
 *    Copyright (C) 2002 Randolph Chung <tausq at parisc-linux.org>
 *    Copyright (C) 2002-2007 Helge Deller <deller with parisc-linux.org>
 * 
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>

#include <linux/string.h>
/* DISABLED: EXPORT_SYMBOL(memset); */

#include <linux/atomic.h>
/* DISABLED: EXPORT_SYMBOL(__xchg8); */
/* DISABLED: EXPORT_SYMBOL(__xchg32); */
/* DISABLED: EXPORT_SYMBOL(__cmpxchg_u32); */
#ifdef CONFIG_SMP
/* DISABLED: EXPORT_SYMBOL(__atomic_hash); */
#endif
#ifdef CONFIG_64BIT
/* DISABLED: EXPORT_SYMBOL(__xchg64); */
/* DISABLED: EXPORT_SYMBOL(__cmpxchg_u64); */
#endif

#include <asm/uaccess.h>
/* DISABLED: EXPORT_SYMBOL(lstrncpy_from_user); */
/* DISABLED: EXPORT_SYMBOL(lclear_user); */
/* DISABLED: EXPORT_SYMBOL(lstrnlen_user); */

/* Global fixups */
extern void fixup_get_user_skip_1(void);
extern void fixup_get_user_skip_2(void);
extern void fixup_put_user_skip_1(void);
extern void fixup_put_user_skip_2(void);
/* DISABLED: EXPORT_SYMBOL(fixup_get_user_skip_1); */
/* DISABLED: EXPORT_SYMBOL(fixup_get_user_skip_2); */
/* DISABLED: EXPORT_SYMBOL(fixup_put_user_skip_1); */
/* DISABLED: EXPORT_SYMBOL(fixup_put_user_skip_2); */

#ifndef CONFIG_64BIT
/* Needed so insmod can set dp value */
extern int $global$;
/* DISABLED: EXPORT_SYMBOL($global$); */
#endif

#include <asm/io.h>
/* DISABLED: EXPORT_SYMBOL(memcpy_toio); */
/* DISABLED: EXPORT_SYMBOL(memcpy_fromio); */
/* DISABLED: EXPORT_SYMBOL(memset_io); */

extern void $$divI(void);
extern void $$divU(void);
extern void $$remI(void);
extern void $$remU(void);
extern void $$mulI(void);
extern void $$divU_3(void);
extern void $$divU_5(void);
extern void $$divU_6(void);
extern void $$divU_9(void);
extern void $$divU_10(void);
extern void $$divU_12(void);
extern void $$divU_7(void);
extern void $$divU_14(void);
extern void $$divU_15(void);
extern void $$divI_3(void);
extern void $$divI_5(void);
extern void $$divI_6(void);
extern void $$divI_7(void);
extern void $$divI_9(void);
extern void $$divI_10(void);
extern void $$divI_12(void);
extern void $$divI_14(void);
extern void $$divI_15(void);

/* DISABLED: EXPORT_SYMBOL($$divI); */
/* DISABLED: EXPORT_SYMBOL($$divU); */
/* DISABLED: EXPORT_SYMBOL($$remI); */
/* DISABLED: EXPORT_SYMBOL($$remU); */
/* DISABLED: EXPORT_SYMBOL($$mulI); */
/* DISABLED: EXPORT_SYMBOL($$divU_3); */
/* DISABLED: EXPORT_SYMBOL($$divU_5); */
/* DISABLED: EXPORT_SYMBOL($$divU_6); */
/* DISABLED: EXPORT_SYMBOL($$divU_9); */
/* DISABLED: EXPORT_SYMBOL($$divU_10); */
/* DISABLED: EXPORT_SYMBOL($$divU_12); */
/* DISABLED: EXPORT_SYMBOL($$divU_7); */
/* DISABLED: EXPORT_SYMBOL($$divU_14); */
/* DISABLED: EXPORT_SYMBOL($$divU_15); */
/* DISABLED: EXPORT_SYMBOL($$divI_3); */
/* DISABLED: EXPORT_SYMBOL($$divI_5); */
/* DISABLED: EXPORT_SYMBOL($$divI_6); */
/* DISABLED: EXPORT_SYMBOL($$divI_7); */
/* DISABLED: EXPORT_SYMBOL($$divI_9); */
/* DISABLED: EXPORT_SYMBOL($$divI_10); */
/* DISABLED: EXPORT_SYMBOL($$divI_12); */
/* DISABLED: EXPORT_SYMBOL($$divI_14); */
/* DISABLED: EXPORT_SYMBOL($$divI_15); */

extern void __ashrdi3(void);
extern void __ashldi3(void);
extern void __lshrdi3(void);
extern void __muldi3(void);

/* DISABLED: EXPORT_SYMBOL(__ashrdi3); */
/* DISABLED: EXPORT_SYMBOL(__ashldi3); */
/* DISABLED: EXPORT_SYMBOL(__lshrdi3); */
/* DISABLED: EXPORT_SYMBOL(__muldi3); */

asmlinkage void * __canonicalize_funcptr_for_compare(void *);
/* DISABLED: EXPORT_SYMBOL(__canonicalize_funcptr_for_compare); */

#ifdef CONFIG_64BIT
extern void __divdi3(void);
extern void __udivdi3(void);
extern void __umoddi3(void);
extern void __moddi3(void);

/* DISABLED: EXPORT_SYMBOL(__divdi3); */
/* DISABLED: EXPORT_SYMBOL(__udivdi3); */
/* DISABLED: EXPORT_SYMBOL(__umoddi3); */
/* DISABLED: EXPORT_SYMBOL(__moddi3); */
#endif

#ifndef CONFIG_64BIT
extern void $$dyncall(void);
/* DISABLED: EXPORT_SYMBOL($$dyncall); */
#endif

#ifdef CONFIG_DISCONTIGMEM
#include <asm/mmzone.h>
/* DISABLED: EXPORT_SYMBOL(node_data); */
/* DISABLED: EXPORT_SYMBOL(pfnnid_map); */
#endif

#ifdef CONFIG_FUNCTION_TRACER
extern void _mcount(void);
/* DISABLED: EXPORT_SYMBOL(_mcount); */
#endif

/* from pacache.S -- needed for copy_page */
/* DISABLED: EXPORT_SYMBOL(copy_user_page_asm); */
