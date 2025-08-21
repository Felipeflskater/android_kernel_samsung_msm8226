#ifndef __LINUX_COMPILER_H
#error "Please include <linux/compiler.h> instead"
#endif

#define __used			__attribute__((__used__))
#define __must_check		__attribute__((warn_unused_result))
#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)
#define __always_inline		inline __attribute__((always_inline))
#define __deprecated		__attribute__((deprecated))
#define __packed		__attribute__((packed))
#define __weak			__attribute__((weak))

/* Disable problematic warnings for GCC 14 */
#pragma GCC diagnostic ignored "-Wendif-labels"
#pragma GCC diagnostic ignored "-Wformat-security"
#pragma GCC diagnostic ignored "-Warray-bounds"
#pragma GCC diagnostic ignored "-Wstringop-overflow"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
