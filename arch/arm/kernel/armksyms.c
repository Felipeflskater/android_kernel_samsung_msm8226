/*
 *  linux/arch/arm/kernel/armksyms.c
 *
 *  Copyright (C) 2000 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/export.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/cryptohash.h>
#include <linux/delay.h>
#include <linux/in6.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/io.h>

#include <asm/checksum.h>
#include <asm/ftrace.h>

/*
 * libgcc functions - functions that are used internally by the
 * compiler...  (prototypes are not correct though, but that
 * doesn't really matter since they're not versioned).
 */
extern void __ashldi3(void);
extern void __ashrdi3(void);
extern void __divsi3(void);
extern void __lshrdi3(void);
extern void __modsi3(void);
extern void __muldi3(void);
extern void __ucmpdi2(void);
extern void __udivsi3(void);
extern void __umodsi3(void);
extern void __do_div64(void);

extern void __aeabi_idiv(void);
extern void __aeabi_idivmod(void);
extern void __aeabi_lasr(void);
extern void __aeabi_llsl(void);
extern void __aeabi_llsr(void);
extern void __aeabi_lmul(void);
extern void __aeabi_uidiv(void);
extern void __aeabi_uidivmod(void);
extern void __aeabi_ulcmp(void);

extern void fpundefinstr(void);

	/* platform dependent support */
/* DISABLED: EXPORT_SYMBOL(arm_delay_ops); */

	/* networking */
/* DISABLED: EXPORT_SYMBOL(csum_partial); */
/* DISABLED: EXPORT_SYMBOL(csum_partial_copy_from_user); */
/* DISABLED: EXPORT_SYMBOL(csum_partial_copy_nocheck); */
/* DISABLED: EXPORT_SYMBOL(__csum_ipv6_magic); */

	/* io */
#ifndef __raw_readsb
/* DISABLED: EXPORT_SYMBOL(__raw_readsb); */
#endif
#ifndef __raw_readsw
/* DISABLED: EXPORT_SYMBOL(__raw_readsw); */
#endif
#ifndef __raw_readsl
/* DISABLED: EXPORT_SYMBOL(__raw_readsl); */
#endif
#ifndef __raw_writesb
/* DISABLED: EXPORT_SYMBOL(__raw_writesb); */
#endif
#ifndef __raw_writesw
/* DISABLED: EXPORT_SYMBOL(__raw_writesw); */
#endif
#ifndef __raw_writesl
/* DISABLED: EXPORT_SYMBOL(__raw_writesl); */
#endif

	/* string / mem functions */
/* DISABLED: EXPORT_SYMBOL(strchr); */
/* DISABLED: EXPORT_SYMBOL(strrchr); */
/* DISABLED: EXPORT_SYMBOL(memset); */
/* DISABLED: EXPORT_SYMBOL(memcpy); */
/* DISABLED: EXPORT_SYMBOL(memmove); */
/* DISABLED: EXPORT_SYMBOL(memchr); */
/* DISABLED: EXPORT_SYMBOL(__memzero); */

	/* user mem (segment) */
/* DISABLED: EXPORT_SYMBOL(__strnlen_user); */
/* DISABLED: EXPORT_SYMBOL(__strncpy_from_user); */

#ifdef CONFIG_MMU
/* DISABLED: EXPORT_SYMBOL(copy_page); */

/* DISABLED: EXPORT_SYMBOL(__copy_from_user); */
/* DISABLED: EXPORT_SYMBOL(__copy_to_user); */
/* DISABLED: EXPORT_SYMBOL(__clear_user); */

/* DISABLED: EXPORT_SYMBOL(__get_user_1); */
/* DISABLED: EXPORT_SYMBOL(__get_user_2); */
/* DISABLED: EXPORT_SYMBOL(__get_user_4); */

/* DISABLED: EXPORT_SYMBOL(__put_user_1); */
/* DISABLED: EXPORT_SYMBOL(__put_user_2); */
/* DISABLED: EXPORT_SYMBOL(__put_user_4); */
/* DISABLED: EXPORT_SYMBOL(__put_user_8); */
#endif

	/* gcc lib functions */
/* DISABLED: EXPORT_SYMBOL(__ashldi3); */
/* DISABLED: EXPORT_SYMBOL(__ashrdi3); */
/* DISABLED: EXPORT_SYMBOL(__divsi3); */
/* DISABLED: EXPORT_SYMBOL(__lshrdi3); */
/* DISABLED: EXPORT_SYMBOL(__modsi3); */
/* DISABLED: EXPORT_SYMBOL(__muldi3); */
/* DISABLED: EXPORT_SYMBOL(__ucmpdi2); */
/* DISABLED: EXPORT_SYMBOL(__udivsi3); */
/* DISABLED: EXPORT_SYMBOL(__umodsi3); */
/* DISABLED: EXPORT_SYMBOL(__do_div64); */

#ifdef CONFIG_AEABI
/* DISABLED: EXPORT_SYMBOL(__aeabi_idiv); */
/* DISABLED: EXPORT_SYMBOL(__aeabi_idivmod); */
/* DISABLED: EXPORT_SYMBOL(__aeabi_lasr); */
/* DISABLED: EXPORT_SYMBOL(__aeabi_llsl); */
/* DISABLED: EXPORT_SYMBOL(__aeabi_llsr); */
/* DISABLED: EXPORT_SYMBOL(__aeabi_lmul); */
/* DISABLED: EXPORT_SYMBOL(__aeabi_uidiv); */
/* DISABLED: EXPORT_SYMBOL(__aeabi_uidivmod); */
/* DISABLED: EXPORT_SYMBOL(__aeabi_ulcmp); */
#endif

	/* bitops */
/* DISABLED: EXPORT_SYMBOL(_set_bit); */
/* DISABLED: EXPORT_SYMBOL(_test_and_set_bit); */
/* DISABLED: EXPORT_SYMBOL(_clear_bit); */
/* DISABLED: EXPORT_SYMBOL(_test_and_clear_bit); */
/* DISABLED: EXPORT_SYMBOL(_change_bit); */
/* DISABLED: EXPORT_SYMBOL(_test_and_change_bit); */
/* DISABLED: EXPORT_SYMBOL(_find_first_zero_bit_le); */
/* DISABLED: EXPORT_SYMBOL(_find_next_zero_bit_le); */
/* DISABLED: EXPORT_SYMBOL(_find_first_bit_le); */
/* DISABLED: EXPORT_SYMBOL(_find_next_bit_le); */

#ifdef __ARMEB__
/* DISABLED: EXPORT_SYMBOL(_find_first_zero_bit_be); */
/* DISABLED: EXPORT_SYMBOL(_find_next_zero_bit_be); */
/* DISABLED: EXPORT_SYMBOL(_find_first_bit_be); */
/* DISABLED: EXPORT_SYMBOL(_find_next_bit_be); */
#endif

#ifdef CONFIG_FUNCTION_TRACER
#ifdef CONFIG_OLD_MCOUNT
/* DISABLED: EXPORT_SYMBOL(mcount); */
#endif
/* DISABLED: EXPORT_SYMBOL(__gnu_mcount_nc); */
#endif

#ifdef CONFIG_ARM_PATCH_PHYS_VIRT
/* DISABLED: EXPORT_SYMBOL(__pv_phys_offset); */
#endif
