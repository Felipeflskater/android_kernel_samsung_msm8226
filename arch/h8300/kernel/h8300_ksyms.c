#include <linux/module.h>
#include <linux/linkage.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/user.h>
#include <linux/elfcore.h>
#include <linux/in6.h>
#include <linux/interrupt.h>

#include <asm/setup.h>
#include <asm/pgalloc.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/checksum.h>
#include <asm/current.h>
#include <asm/gpio.h>

//asmlinkage long long __ashrdi3 (long long, int);
//asmlinkage long long __lshrdi3 (long long, int);
extern char h8300_debug_device[];

/* platform dependent support */

/* DISABLED: EXPORT_SYMBOL(strnlen); */
/* DISABLED: EXPORT_SYMBOL(strrchr); */
/* DISABLED: EXPORT_SYMBOL(strstr); */
/* DISABLED: EXPORT_SYMBOL(strchr); */
/* DISABLED: EXPORT_SYMBOL(strcat); */
/* DISABLED: EXPORT_SYMBOL(strlen); */
/* DISABLED: EXPORT_SYMBOL(strcmp); */
/* DISABLED: EXPORT_SYMBOL(strncmp); */

/* DISABLED: EXPORT_SYMBOL(ip_fast_csum); */

/* DISABLED: EXPORT_SYMBOL(kernel_thread); */
/* DISABLED: EXPORT_SYMBOL(enable_irq); */
/* DISABLED: EXPORT_SYMBOL(disable_irq); */

/* Networking helper routines. */
/* DISABLED: EXPORT_SYMBOL(csum_partial_copy_nocheck); */

/* The following are special because they're not called
   explicitly (the C compiler generates them).  Fortunately,
   their interface isn't gonna change any time soon now, so
   it's OK to leave it out of version control.  */
//EXPORT_SYMBOL(__ashrdi3);
//EXPORT_SYMBOL(__lshrdi3);
/* DISABLED: EXPORT_SYMBOL(memcpy); */
/* DISABLED: EXPORT_SYMBOL(memset); */
/* DISABLED: EXPORT_SYMBOL(memcmp); */
/* DISABLED: EXPORT_SYMBOL(memscan); */
/* DISABLED: EXPORT_SYMBOL(memmove); */

/*
 * libgcc functions - functions that are used internally by the
 * compiler...  (prototypes are not correct though, but that
 * doesn't really matter since they're not versioned).
 */
extern void __gcc_bcmp(void);
extern void __ashldi3(void);
extern void __ashrdi3(void);
extern void __cmpdi2(void);
extern void __divdi3(void);
extern void __divsi3(void);
extern void __lshrdi3(void);
extern void __moddi3(void);
extern void __modsi3(void);
extern void __muldi3(void);
extern void __mulsi3(void);
extern void __negdi2(void);
extern void __ucmpdi2(void);
extern void __udivdi3(void);
extern void __udivmoddi4(void);
extern void __udivsi3(void);
extern void __umoddi3(void);
extern void __umodsi3(void);

        /* gcc lib functions */
/* DISABLED: EXPORT_SYMBOL(__gcc_bcmp); */
/* DISABLED: EXPORT_SYMBOL(__ashldi3); */
/* DISABLED: EXPORT_SYMBOL(__ashrdi3); */
/* DISABLED: EXPORT_SYMBOL(__cmpdi2); */
/* DISABLED: EXPORT_SYMBOL(__divdi3); */
/* DISABLED: EXPORT_SYMBOL(__divsi3); */
/* DISABLED: EXPORT_SYMBOL(__lshrdi3); */
/* DISABLED: EXPORT_SYMBOL(__moddi3); */
/* DISABLED: EXPORT_SYMBOL(__modsi3); */
/* DISABLED: EXPORT_SYMBOL(__muldi3); */
/* DISABLED: EXPORT_SYMBOL(__mulsi3); */
/* DISABLED: EXPORT_SYMBOL(__negdi2); */
/* DISABLED: EXPORT_SYMBOL(__ucmpdi2); */
/* DISABLED: EXPORT_SYMBOL(__udivdi3); */
/* DISABLED: EXPORT_SYMBOL(__udivmoddi4); */
/* DISABLED: EXPORT_SYMBOL(__udivsi3); */
/* DISABLED: EXPORT_SYMBOL(__umoddi3); */
/* DISABLED: EXPORT_SYMBOL(__umodsi3); */

/* DISABLED: EXPORT_SYMBOL(h8300_reserved_gpio); */
/* DISABLED: EXPORT_SYMBOL(h8300_free_gpio); */
/* DISABLED: EXPORT_SYMBOL(h8300_set_gpio_dir); */
