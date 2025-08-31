/*
 * linux/arch/unicore32/kernel/ksyms.c
 *
 * Code specific to PKUnity SoC and UniCore ISA
 *
 * Copyright (C) 2001-2010 GUAN Xue-tao
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/cryptohash.h>
#include <linux/delay.h>
#include <linux/in6.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/io.h>

#include <asm/checksum.h>

#include "ksyms.h"

/* DISABLED: EXPORT_SYMBOL(find_next_zero_bit); */
/* DISABLED: EXPORT_SYMBOL(find_next_bit); */

/* DISABLED: EXPORT_SYMBOL(__backtrace); */

	/* platform dependent support */
/* DISABLED: EXPORT_SYMBOL(__udelay); */
/* DISABLED: EXPORT_SYMBOL(__const_udelay); */

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

	/* user mem (segment) */
/* DISABLED: EXPORT_SYMBOL(__strnlen_user); */
/* DISABLED: EXPORT_SYMBOL(__strncpy_from_user); */

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

/* DISABLED: EXPORT_SYMBOL(__ashldi3); */
/* DISABLED: EXPORT_SYMBOL(__ashrdi3); */
/* DISABLED: EXPORT_SYMBOL(__divsi3); */
/* DISABLED: EXPORT_SYMBOL(__lshrdi3); */
/* DISABLED: EXPORT_SYMBOL(__modsi3); */
/* DISABLED: EXPORT_SYMBOL(__muldi3); */
/* DISABLED: EXPORT_SYMBOL(__ucmpdi2); */
/* DISABLED: EXPORT_SYMBOL(__udivsi3); */
/* DISABLED: EXPORT_SYMBOL(__umodsi3); */
/* DISABLED: EXPORT_SYMBOL(__bswapsi2); */

