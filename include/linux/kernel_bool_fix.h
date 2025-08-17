#ifndef _LINUX_KERNEL_BOOL_FIX_H
#define _LINUX_KERNEL_BOOL_FIX_H

/* Fix para redefinições de true/false em kernel 3.4.x com GCC moderno */
#ifdef __KERNEL__
#ifndef __cplusplus
#undef true
#undef false
#define true 1
#define false 0
#endif
#endif

#endif /* _LINUX_KERNEL_BOOL_FIX_H */
