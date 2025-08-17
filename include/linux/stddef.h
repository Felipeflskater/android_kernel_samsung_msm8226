#include <linux/kernel_bool_fix.h>
#ifndef _LINUX_STDDEF_H
#define _LINUX_STDDEF_H

#include <linux/compiler.h>

#ifdef __KERNEL__

#undef NULL
#define NULL ((void *)0)

enum {
	__kernel_false = 0,
	__kernel_true  = 1
};

#ifndef __cplusplus
#define false __kernel_false
#define true  __kernel_true
#endif

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif
#endif /* __KERNEL__ */

/**
 * offsetofend(TYPE, MEMBER)
 *
 * @TYPE: The type of the structure
 * @MEMBER: The member within the structure to get the end offset of
 */
#define offsetofend(TYPE, MEMBER) \
	(offsetof(TYPE, MEMBER)	+ sizeof(((TYPE *)0)->MEMBER))

#endif
