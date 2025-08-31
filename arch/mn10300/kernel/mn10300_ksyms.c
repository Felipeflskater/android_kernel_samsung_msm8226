/* MN10300 Miscellaneous and library kernel exports
 *
 * Copyright (C) 2007 Matsushita Electric Industrial Co., Ltd.
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version
 * 2 of the Licence, or (at your option) any later version.
 */
#include <linux/module.h>
#include <asm/uaccess.h>
#include <asm/pgtable.h>


/* DISABLED: EXPORT_SYMBOL(empty_zero_page); */

/* DISABLED: EXPORT_SYMBOL(change_bit); */
/* DISABLED: EXPORT_SYMBOL(test_and_change_bit); */

/* DISABLED: EXPORT_SYMBOL(memcpy); */
/* DISABLED: EXPORT_SYMBOL(memmove); */
/* DISABLED: EXPORT_SYMBOL(memset); */

/* DISABLED: EXPORT_SYMBOL(strncpy_from_user); */
/* DISABLED: EXPORT_SYMBOL(__strncpy_from_user); */
/* DISABLED: EXPORT_SYMBOL(clear_user); */
/* DISABLED: EXPORT_SYMBOL(__clear_user); */
/* DISABLED: EXPORT_SYMBOL(__generic_copy_from_user); */
/* DISABLED: EXPORT_SYMBOL(__generic_copy_to_user); */
/* DISABLED: EXPORT_SYMBOL(strnlen_user); */

extern u64 __ashrdi3(u64, unsigned);
extern u64 __ashldi3(u64, unsigned);
extern u64 __lshrdi3(u64, unsigned);
extern s64 __negdi2(s64);
extern int __ucmpdi2(u64, u64);
/* DISABLED: EXPORT_SYMBOL(__ashrdi3); */
/* DISABLED: EXPORT_SYMBOL(__ashldi3); */
/* DISABLED: EXPORT_SYMBOL(__lshrdi3); */
/* DISABLED: EXPORT_SYMBOL(__negdi2); */
/* DISABLED: EXPORT_SYMBOL(__ucmpdi2); */
