#ifndef _UAPI_LINUX_STDDEF_H
#define _UAPI_LINUX_STDDEF_H

#ifndef __ASSEMBLY__

#ifdef __KERNEL__
/* Kernel space definitions */
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#else
/* User space definitions */
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#endif /* __KERNEL__ */

#endif /* __ASSEMBLY__ */

#endif /* _UAPI_LINUX_STDDEF_H */
