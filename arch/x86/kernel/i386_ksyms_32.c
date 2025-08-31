#include <linux/module.h>

#include <asm/checksum.h>
#include <asm/pgtable.h>
#include <asm/desc.h>
#include <asm/ftrace.h>

#ifdef CONFIG_FUNCTION_TRACER
/* mcount is defined in assembly */
/* DISABLED: EXPORT_SYMBOL(mcount); */
#endif

/*
 * Note, this is a prototype to get at the symbol for
 * the export, but dont use it from C code, it is used
 * by assembly code and is not using C calling convention!
 */
#ifndef CONFIG_X86_CMPXCHG64
extern void cmpxchg8b_emu(void);
/* DISABLED: EXPORT_SYMBOL(cmpxchg8b_emu); */
#endif

/* Networking helper routines. */
/* DISABLED: EXPORT_SYMBOL(csum_partial_copy_generic); */

/* DISABLED: EXPORT_SYMBOL(__get_user_1); */
/* DISABLED: EXPORT_SYMBOL(__get_user_2); */
/* DISABLED: EXPORT_SYMBOL(__get_user_4); */

/* DISABLED: EXPORT_SYMBOL(__put_user_1); */
/* DISABLED: EXPORT_SYMBOL(__put_user_2); */
/* DISABLED: EXPORT_SYMBOL(__put_user_4); */
/* DISABLED: EXPORT_SYMBOL(__put_user_8); */

/* DISABLED: EXPORT_SYMBOL(strstr); */

/* DISABLED: EXPORT_SYMBOL(csum_partial); */
/* DISABLED: EXPORT_SYMBOL(empty_zero_page); */
