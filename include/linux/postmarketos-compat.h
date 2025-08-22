#ifndef _LINUX_POSTMARKETOS_COMPAT_H
#define _LINUX_POSTMARKETOS_COMPAT_H

/*
 * PostmarketOS compatibility layer for ancient Android kernels
 * Fixes compilation issues with modern toolchains
 */

#include <linux/types.h>
#include <linux/compiler.h>

/* Avoid Bool typedef conflicts */
#ifndef Bool
#ifndef __cplusplus
#define Bool int
#else
typedef bool Bool;
#endif
#endif

/* ARM architecture compatibility */
#ifndef __LINUX_ARM_ARCH__
#ifdef CONFIG_CPU_ARM926T
#define __LINUX_ARM_ARCH__ 5
#elif defined(CONFIG_CPU_ARM1136)
#define __LINUX_ARM_ARCH__ 6
#elif defined(CONFIG_CPU_V6K)
#define __LINUX_ARM_ARCH__ 6
#elif defined(CONFIG_CPU_V7)
#define __LINUX_ARM_ARCH__ 7
#else
#define __LINUX_ARM_ARCH__ 7
#endif
#endif

/* GCC compatibility fixes */
#if __GNUC__ >= 9
#pragma GCC diagnostic ignored "-Waddress-of-packed-member"
#pragma GCC diagnostic ignored "-Wpacked-not-aligned"
#endif

#if __GNUC__ >= 11
#pragma GCC diagnostic ignored "-Warray-parameter"
#pragma GCC diagnostic ignored "-Wzero-length-bounds"
#endif

#if __GNUC__ >= 12
#pragma GCC diagnostic ignored "-Wdangling-pointer"
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif

/* Legacy type definitions for old Android kernels */
#ifndef __kernel_long_t
typedef long __kernel_long_t;
typedef unsigned long __kernel_ulong_t;
#endif

#ifndef __kernel_suseconds_t  
typedef __kernel_long_t __kernel_suseconds_t;
#endif

/* Memory barrier compatibility */
#ifndef smp_store_release
#define smp_store_release(p, v) \
do { \
    compiletime_assert_atomic_type(*p); \
    smp_mb(); \
    WRITE_ONCE(*p, v); \
} while (0)
#endif

#ifndef smp_load_acquire
#define smp_load_acquire(p) \
({ \
    typeof(*p) ___p1 = READ_ONCE(*p); \
    compiletime_assert_atomic_type(*p); \
    smp_mb(); \
    ___p1; \
})
#endif

/* Compiler attribute compatibility */
#ifndef __always_unused
#define __always_unused __attribute__((unused))
#endif

#ifndef __visible
#define __visible __attribute__((externally_visible))
#endif

/* Modern kernel compatibility stubs */
#ifndef VERIFY_OCTAL_PERMISSIONS
#define VERIFY_OCTAL_PERMISSIONS(perms) (perms)
#endif

#ifndef __ro_after_init
#define __ro_after_init __attribute__((__section__(".data..ro_after_init")))
#endif

/* Time64 compatibility for old kernels */
#ifndef time64_to_tm
#define time64_to_tm time_to_tm
#endif

/* Network namespace compatibility */
#ifndef __net_get_random_once
#define __net_get_random_once(buf, nbytes) \
    get_random_once((buf), (nbytes))
#endif

#endif /* _LINUX_POSTMARKETOS_COMPAT_H */
