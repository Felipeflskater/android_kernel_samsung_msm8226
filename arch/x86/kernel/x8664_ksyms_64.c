/* Exports for assembly files.
   All C exports should go in the respective C files. */

#include <linux/module.h>
#include <linux/smp.h>

#include <net/checksum.h>

#include <asm/processor.h>
#include <asm/pgtable.h>
#include <asm/uaccess.h>
#include <asm/desc.h>
#include <asm/ftrace.h>

#ifdef CONFIG_FUNCTION_TRACER
/* mcount is defined in assembly */
/* DISABLED: EXPORT_SYMBOL(mcount); */
#endif

/* DISABLED: EXPORT_SYMBOL(__get_user_1); */
/* DISABLED: EXPORT_SYMBOL(__get_user_2); */
/* DISABLED: EXPORT_SYMBOL(__get_user_4); */
/* DISABLED: EXPORT_SYMBOL(__get_user_8); */
/* DISABLED: EXPORT_SYMBOL(__put_user_1); */
/* DISABLED: EXPORT_SYMBOL(__put_user_2); */
/* DISABLED: EXPORT_SYMBOL(__put_user_4); */
/* DISABLED: EXPORT_SYMBOL(__put_user_8); */

/* DISABLED: EXPORT_SYMBOL(copy_user_generic_string); */
/* DISABLED: EXPORT_SYMBOL(copy_user_generic_unrolled); */
/* DISABLED: EXPORT_SYMBOL(__copy_user_nocache); */
/* DISABLED: EXPORT_SYMBOL(_copy_from_user); */
/* DISABLED: EXPORT_SYMBOL(_copy_to_user); */

/* DISABLED: EXPORT_SYMBOL(copy_page); */
/* DISABLED: EXPORT_SYMBOL(clear_page); */

/* DISABLED: EXPORT_SYMBOL(csum_partial); */

/*
 * Export string functions. We normally rely on gcc builtin for most of these,
 * but gcc sometimes decides not to inline them.
 */
#undef memcpy
#undef memset
#undef memmove

extern void *memset(void *, int, __kernel_size_t);
extern void *memcpy(void *, const void *, __kernel_size_t);
extern void *__memcpy(void *, const void *, __kernel_size_t);

/* DISABLED: EXPORT_SYMBOL(memset); */
/* DISABLED: EXPORT_SYMBOL(memcpy); */
/* DISABLED: EXPORT_SYMBOL(__memcpy); */
/* DISABLED: EXPORT_SYMBOL(memmove); */

/* DISABLED: EXPORT_SYMBOL(empty_zero_page); */
#ifndef CONFIG_PARAVIRT
/* DISABLED: EXPORT_SYMBOL(native_load_gs_index); */
#endif
