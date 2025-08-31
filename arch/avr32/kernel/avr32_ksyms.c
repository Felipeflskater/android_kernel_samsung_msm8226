/*
 * Export AVR32-specific functions for loadable modules.
 *
 * Copyright (C) 2004-2006 Atmel Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/module.h>

#include <asm/checksum.h>
#include <asm/uaccess.h>

/*
 * GCC functions
 */
extern unsigned long long __avr32_lsl64(unsigned long long u, unsigned long b);
extern unsigned long long __avr32_lsr64(unsigned long long u, unsigned long b);
extern unsigned long long __avr32_asr64(unsigned long long u, unsigned long b);
/* DISABLED: EXPORT_SYMBOL(__avr32_lsl64); */
/* DISABLED: EXPORT_SYMBOL(__avr32_lsr64); */
/* DISABLED: EXPORT_SYMBOL(__avr32_asr64); */

/*
 * String functions
 */
/* DISABLED: EXPORT_SYMBOL(memset); */
/* DISABLED: EXPORT_SYMBOL(memcpy); */

/* DISABLED: EXPORT_SYMBOL(clear_page); */
/* DISABLED: EXPORT_SYMBOL(copy_page); */

/*
 * Userspace access stuff.
 */
/* DISABLED: EXPORT_SYMBOL(copy_from_user); */
/* DISABLED: EXPORT_SYMBOL(copy_to_user); */
/* DISABLED: EXPORT_SYMBOL(__copy_user); */
/* DISABLED: EXPORT_SYMBOL(strncpy_from_user); */
/* DISABLED: EXPORT_SYMBOL(__strncpy_from_user); */
/* DISABLED: EXPORT_SYMBOL(clear_user); */
/* DISABLED: EXPORT_SYMBOL(__clear_user); */
/* DISABLED: EXPORT_SYMBOL(strnlen_user); */

/* DISABLED: EXPORT_SYMBOL(csum_partial); */
/* DISABLED: EXPORT_SYMBOL(csum_partial_copy_generic); */

/* Delay loops (lib/delay.S) */
/* DISABLED: EXPORT_SYMBOL(__ndelay); */
/* DISABLED: EXPORT_SYMBOL(__udelay); */
/* DISABLED: EXPORT_SYMBOL(__const_udelay); */

/* Bit operations (lib/findbit.S) */
/* DISABLED: EXPORT_SYMBOL(find_first_zero_bit); */
/* DISABLED: EXPORT_SYMBOL(find_next_zero_bit); */
/* DISABLED: EXPORT_SYMBOL(find_first_bit); */
/* DISABLED: EXPORT_SYMBOL(find_next_bit); */
/* DISABLED: EXPORT_SYMBOL(find_next_bit_le); */
/* DISABLED: EXPORT_SYMBOL(find_next_zero_bit_le); */

/* I/O primitives (lib/io-*.S) */
/* DISABLED: EXPORT_SYMBOL(__raw_readsb); */
/* DISABLED: EXPORT_SYMBOL(__raw_readsw); */
/* DISABLED: EXPORT_SYMBOL(__raw_readsl); */
/* DISABLED: EXPORT_SYMBOL(__raw_writesb); */
/* DISABLED: EXPORT_SYMBOL(__raw_writesw); */
/* DISABLED: EXPORT_SYMBOL(__raw_writesl); */
