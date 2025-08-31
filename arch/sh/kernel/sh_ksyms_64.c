/*
 * arch/sh/kernel/sh_ksyms_64.c
 *
 * Copyright (C) 2000, 2001  Paolo Alberelli
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */
#include <linux/rwsem.h>
#include <linux/module.h>
#include <linux/smp.h>
#include <linux/user.h>
#include <linux/elfcore.h>
#include <linux/sched.h>
#include <linux/in6.h>
#include <linux/interrupt.h>
#include <linux/screen_info.h>
#include <asm/cacheflush.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <asm/checksum.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <asm/irq.h>

/* DISABLED: EXPORT_SYMBOL(__put_user_asm_b); */
/* DISABLED: EXPORT_SYMBOL(__put_user_asm_w); */
/* DISABLED: EXPORT_SYMBOL(__put_user_asm_l); */
/* DISABLED: EXPORT_SYMBOL(__put_user_asm_q); */
/* DISABLED: EXPORT_SYMBOL(__get_user_asm_b); */
/* DISABLED: EXPORT_SYMBOL(__get_user_asm_w); */
/* DISABLED: EXPORT_SYMBOL(__get_user_asm_l); */
/* DISABLED: EXPORT_SYMBOL(__get_user_asm_q); */
/* DISABLED: EXPORT_SYMBOL(__strnlen_user); */
/* DISABLED: EXPORT_SYMBOL(__strncpy_from_user); */
/* DISABLED: EXPORT_SYMBOL(__clear_user); */
/* DISABLED: EXPORT_SYMBOL(copy_page); */
/* DISABLED: EXPORT_SYMBOL(__copy_user); */
/* DISABLED: EXPORT_SYMBOL(empty_zero_page); */
/* DISABLED: EXPORT_SYMBOL(memcpy); */
/* DISABLED: EXPORT_SYMBOL(memset); */
/* DISABLED: EXPORT_SYMBOL(__udelay); */
/* DISABLED: EXPORT_SYMBOL(__ndelay); */
/* DISABLED: EXPORT_SYMBOL(__const_udelay); */
/* DISABLED: EXPORT_SYMBOL(strlen); */
/* DISABLED: EXPORT_SYMBOL(strcpy); */

/* Ugh.  These come in from libgcc.a at link time. */
#define DECLARE_EXPORT(name) extern void name(void);EXPORT_SYMBOL(name)

DECLARE_EXPORT(__sdivsi3);
DECLARE_EXPORT(__sdivsi3_1);
DECLARE_EXPORT(__sdivsi3_2);
DECLARE_EXPORT(__udivsi3);
DECLARE_EXPORT(__div_table);
