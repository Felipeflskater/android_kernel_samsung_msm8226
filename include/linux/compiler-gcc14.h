#ifndef __LINUX_COMPILER_H
#error "Please include <linux/compiler.h> instead"
#endif

/* Prevent redefinition warnings */
#ifndef __used
#define __used			__attribute__((__used__))
#endif

#ifndef __must_check
#define __must_check		__attribute__((warn_unused_result))
#endif

#ifndef __compiler_offsetof
#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)
#endif

#ifndef __always_inline
#define __always_inline		inline __attribute__((always_inline))
#endif

#ifndef __deprecated
#define __deprecated		__attribute__((deprecated))
#endif

#ifndef __packed
#define __packed		__attribute__((packed))
#endif

#ifndef __weak
#define __weak			__attribute__((weak))
#endif

#ifndef __align
#define __align(x)		__attribute__((aligned(x)))
#endif

#ifndef __attribute_const__
#define __attribute_const__	__attribute__((__const__))
#endif

#ifndef __maybe_unused
#define __maybe_unused		__attribute__((unused))
#endif

#ifndef __always_unused
#define __always_unused		__attribute__((unused))
#endif

#ifndef __noreturn
#define __noreturn		__attribute__((__noreturn__))
#endif

/* Skip __printf and __scanf - they're already defined in compiler-gcc.h */

/* Disable problematic warnings */
#pragma GCC diagnostic ignored "-Wendif-labels"
#pragma GCC diagnostic ignored "-Wformat-security"
