/*
 * linux/arch/alpha/kernel/alpha_ksyms.c
 *
 * Export the alpha-specific functions that are needed for loadable
 * modules.
 */

#include <linux/module.h>
#include <asm/console.h>
#include <asm/uaccess.h>
#include <asm/checksum.h>
#include <asm/fpu.h>
#include <asm/machvec.h>

#include <linux/syscalls.h>

/* these are C runtime functions with special calling conventions: */
extern void __divl (void);
extern void __reml (void);
extern void __divq (void);
extern void __remq (void);
extern void __divlu (void);
extern void __remlu (void);
extern void __divqu (void);
extern void __remqu (void);

/* DISABLED: EXPORT_SYMBOL(alpha_mv); */
/* DISABLED: EXPORT_SYMBOL(callback_getenv); */
/* DISABLED: EXPORT_SYMBOL(callback_setenv); */
/* DISABLED: EXPORT_SYMBOL(callback_save_env); */

/* platform dependent support */
/* DISABLED: EXPORT_SYMBOL(strcat); */
/* DISABLED: EXPORT_SYMBOL(strcpy); */
/* DISABLED: EXPORT_SYMBOL(strlen); */
/* DISABLED: EXPORT_SYMBOL(strncpy); */
/* DISABLED: EXPORT_SYMBOL(strncat); */
/* DISABLED: EXPORT_SYMBOL(strchr); */
/* DISABLED: EXPORT_SYMBOL(strrchr); */
/* DISABLED: EXPORT_SYMBOL(memmove); */
/* DISABLED: EXPORT_SYMBOL(__memcpy); */
/* DISABLED: EXPORT_SYMBOL(__memset); */
/* DISABLED: EXPORT_SYMBOL(__memsetw); */
/* DISABLED: EXPORT_SYMBOL(__constant_c_memset); */
/* DISABLED: EXPORT_SYMBOL(copy_page); */
/* DISABLED: EXPORT_SYMBOL(clear_page); */

/* DISABLED: EXPORT_SYMBOL(alpha_read_fp_reg); */
/* DISABLED: EXPORT_SYMBOL(alpha_read_fp_reg_s); */
/* DISABLED: EXPORT_SYMBOL(alpha_write_fp_reg); */
/* DISABLED: EXPORT_SYMBOL(alpha_write_fp_reg_s); */

/* entry.S */
/* DISABLED: EXPORT_SYMBOL(kernel_thread); */
/* DISABLED: EXPORT_SYMBOL(kernel_execve); */

/* Networking helper routines. */
/* DISABLED: EXPORT_SYMBOL(csum_tcpudp_magic); */
/* DISABLED: EXPORT_SYMBOL(ip_compute_csum); */
/* DISABLED: EXPORT_SYMBOL(ip_fast_csum); */
/* DISABLED: EXPORT_SYMBOL(csum_partial_copy_nocheck); */
/* DISABLED: EXPORT_SYMBOL(csum_partial_copy_from_user); */
/* DISABLED: EXPORT_SYMBOL(csum_ipv6_magic); */

#ifdef CONFIG_MATHEMU_MODULE
extern long (*alpha_fp_emul_imprecise)(struct pt_regs *, unsigned long);
extern long (*alpha_fp_emul) (unsigned long pc);
/* DISABLED: EXPORT_SYMBOL(alpha_fp_emul_imprecise); */
/* DISABLED: EXPORT_SYMBOL(alpha_fp_emul); */
#endif

/*
 * The following are specially called from the uaccess assembly stubs.
 */
/* DISABLED: EXPORT_SYMBOL(__copy_user); */
/* DISABLED: EXPORT_SYMBOL(__do_clear_user); */
/* DISABLED: EXPORT_SYMBOL(__strncpy_from_user); */
/* DISABLED: EXPORT_SYMBOL(__strnlen_user); */

/* 
 * SMP-specific symbols.
 */

#ifdef CONFIG_SMP
/* DISABLED: EXPORT_SYMBOL(_atomic_dec_and_lock); */
#endif /* CONFIG_SMP */

/*
 * The following are special because they're not called
 * explicitly (the C compiler or assembler generates them in
 * response to division operations).  Fortunately, their
 * interface isn't gonna change any time soon now, so it's OK
 * to leave it out of version control.
 */
# undef memcpy
# undef memset
/* DISABLED: EXPORT_SYMBOL(__divl); */
/* DISABLED: EXPORT_SYMBOL(__divlu); */
/* DISABLED: EXPORT_SYMBOL(__divq); */
/* DISABLED: EXPORT_SYMBOL(__divqu); */
/* DISABLED: EXPORT_SYMBOL(__reml); */
/* DISABLED: EXPORT_SYMBOL(__remlu); */
/* DISABLED: EXPORT_SYMBOL(__remq); */
/* DISABLED: EXPORT_SYMBOL(__remqu); */
/* DISABLED: EXPORT_SYMBOL(memcpy); */
/* DISABLED: EXPORT_SYMBOL(memset); */
/* DISABLED: EXPORT_SYMBOL(memchr); */
