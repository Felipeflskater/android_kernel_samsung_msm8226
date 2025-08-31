#include <linux/module.h>
#include <linux/user.h>
#include <linux/elfcore.h>
#include <linux/sched.h>
#include <linux/in6.h>
#include <linux/interrupt.h>
#include <linux/pm.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/tty.h>

#include <asm/processor.h>
#include <asm/uaccess.h>
#include <asm/checksum.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/pgtable.h>
#include <asm/fasttimer.h>

extern unsigned long get_cmos_time(void);
extern void __Udiv(void);
extern void __Umod(void);
extern void __Div(void);
extern void __Mod(void);
extern void __ashldi3(void);
extern void __ashrdi3(void);
extern void __lshrdi3(void);
extern void __negdi2(void);
extern void iounmap(volatile void * __iomem);

/* Platform dependent support */
/* DISABLED: EXPORT_SYMBOL(kernel_thread); */
/* DISABLED: EXPORT_SYMBOL(get_cmos_time); */
/* DISABLED: EXPORT_SYMBOL(loops_per_usec); */

/* Math functions */
/* DISABLED: EXPORT_SYMBOL(__Udiv); */
/* DISABLED: EXPORT_SYMBOL(__Umod); */
/* DISABLED: EXPORT_SYMBOL(__Div); */
/* DISABLED: EXPORT_SYMBOL(__Mod); */
/* DISABLED: EXPORT_SYMBOL(__ashldi3); */
/* DISABLED: EXPORT_SYMBOL(__ashrdi3); */
/* DISABLED: EXPORT_SYMBOL(__lshrdi3); */
/* DISABLED: EXPORT_SYMBOL(__negdi2); */

/* Memory functions */
/* DISABLED: EXPORT_SYMBOL(__ioremap); */
/* DISABLED: EXPORT_SYMBOL(iounmap); */

/* Userspace access functions */
/* DISABLED: EXPORT_SYMBOL(__copy_user_zeroing); */
/* DISABLED: EXPORT_SYMBOL(__copy_user); */

#undef memcpy
#undef memset
extern void * memset(void *, int, __kernel_size_t);
extern void * memcpy(void *, const void *, __kernel_size_t);
/* DISABLED: EXPORT_SYMBOL(memcpy); */
/* DISABLED: EXPORT_SYMBOL(memset); */

#ifdef CONFIG_ETRAX_FAST_TIMER
/* Fast timer functions */
/* DISABLED: EXPORT_SYMBOL(fast_timer_list); */
/* DISABLED: EXPORT_SYMBOL(start_one_shot_timer); */
/* DISABLED: EXPORT_SYMBOL(del_fast_timer); */
/* DISABLED: EXPORT_SYMBOL(schedule_usleep); */
#endif
/* DISABLED: EXPORT_SYMBOL(csum_partial); */
