#ifndef __ASM_ARM_SWAB_H
#define __ASM_ARM_SWAB_H

#include <linux/compiler.h>
#include <linux/types.h>

#if !defined(__STRICT_ANSI__) || defined(__KERNEL__)
#  define __SWAB_64_THRU_32__
#endif

#ifdef __ARMEB__
static inline __attribute_const__ __u32 __arch_swab32(__u32 x)
{
	__asm__ ("rev %0, %1" : "=r" (x) : "r" (x));
	return x;
}
#define __arch_swab32 __arch_swab32

#if !defined(__KERNEL__) || __LINUX_ARM_ARCH__ >= 6
static inline __attribute_const__ __u16 __arch_swab16(__u16 x)
{
	__asm__ ("rev16 %0, %1" : "=r" (x) : "r" (x));
	return x;
}
#define __arch_swab16 __arch_swab16
#endif

#endif

#include <linux/byteorder.h>

#endif /* __ASM_ARM_SWAB_H */
