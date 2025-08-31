#include <linux/module.h>
#include <linux/smp.h>
#include <linux/user.h>
#include <linux/elfcore.h>
#include <linux/sched.h>
#include <linux/in6.h>
#include <linux/interrupt.h>
#include <linux/string.h>

#include <asm/processor.h>
#include <asm/uaccess.h>
#include <asm/checksum.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/tlbflush.h>
#include <asm/pgtable.h>

/* platform dependent support */
/* DISABLED: EXPORT_SYMBOL(boot_cpu_data); */
/* DISABLED: EXPORT_SYMBOL(dump_fpu); */
/* DISABLED: EXPORT_SYMBOL(__ioremap); */
/* DISABLED: EXPORT_SYMBOL(iounmap); */
/* DISABLED: EXPORT_SYMBOL(kernel_thread); */

/* DISABLED: EXPORT_SYMBOL(strncpy_from_user); */
/* DISABLED: EXPORT_SYMBOL(__strncpy_from_user); */
/* DISABLED: EXPORT_SYMBOL(clear_user); */
/* DISABLED: EXPORT_SYMBOL(__clear_user); */
/* DISABLED: EXPORT_SYMBOL(__generic_copy_from_user); */
/* DISABLED: EXPORT_SYMBOL(__generic_copy_to_user); */
/* DISABLED: EXPORT_SYMBOL(strnlen_user); */

#ifdef CONFIG_SMP
#ifdef CONFIG_CHIP_M32700_TS1
extern void *dcache_dummy;
/* DISABLED: EXPORT_SYMBOL(dcache_dummy); */
#endif
/* DISABLED: EXPORT_SYMBOL(cpu_data); */

/* TLB flushing */
/* DISABLED: EXPORT_SYMBOL(smp_flush_tlb_page); */
#endif

/* compiler generated symbol */
extern void __ashldi3(void);
extern void __ashrdi3(void);
extern void __lshldi3(void);
extern void __lshrdi3(void);
extern void __muldi3(void);
/* DISABLED: EXPORT_SYMBOL(__ashldi3); */
/* DISABLED: EXPORT_SYMBOL(__ashrdi3); */
/* DISABLED: EXPORT_SYMBOL(__lshldi3); */
/* DISABLED: EXPORT_SYMBOL(__lshrdi3); */
/* DISABLED: EXPORT_SYMBOL(__muldi3); */

/* memory and string operations */
/* DISABLED: EXPORT_SYMBOL(memcpy); */
/* DISABLED: EXPORT_SYMBOL(memset); */
/* DISABLED: EXPORT_SYMBOL(copy_page); */
/* DISABLED: EXPORT_SYMBOL(clear_page); */
/* DISABLED: EXPORT_SYMBOL(strlen); */
/* DISABLED: EXPORT_SYMBOL(empty_zero_page); */

/* DISABLED: EXPORT_SYMBOL(_inb); */
/* DISABLED: EXPORT_SYMBOL(_inw); */
/* DISABLED: EXPORT_SYMBOL(_inl); */
/* DISABLED: EXPORT_SYMBOL(_outb); */
/* DISABLED: EXPORT_SYMBOL(_outw); */
/* DISABLED: EXPORT_SYMBOL(_outl); */
/* DISABLED: EXPORT_SYMBOL(_inb_p); */
/* DISABLED: EXPORT_SYMBOL(_inw_p); */
/* DISABLED: EXPORT_SYMBOL(_inl_p); */
/* DISABLED: EXPORT_SYMBOL(_outb_p); */
/* DISABLED: EXPORT_SYMBOL(_outw_p); */
/* DISABLED: EXPORT_SYMBOL(_outl_p); */
/* DISABLED: EXPORT_SYMBOL(_insb); */
/* DISABLED: EXPORT_SYMBOL(_insw); */
/* DISABLED: EXPORT_SYMBOL(_insl); */
/* DISABLED: EXPORT_SYMBOL(_outsb); */
/* DISABLED: EXPORT_SYMBOL(_outsw); */
/* DISABLED: EXPORT_SYMBOL(_outsl); */
/* DISABLED: EXPORT_SYMBOL(_readb); */
/* DISABLED: EXPORT_SYMBOL(_readw); */
/* DISABLED: EXPORT_SYMBOL(_readl); */
/* DISABLED: EXPORT_SYMBOL(_writeb); */
/* DISABLED: EXPORT_SYMBOL(_writew); */
/* DISABLED: EXPORT_SYMBOL(_writel); */

