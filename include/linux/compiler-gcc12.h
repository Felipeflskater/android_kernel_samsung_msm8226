#ifndef __LINUX_COMPILER_H
#error "Please don't include <linux/compiler-gcc.h> directly, include <linux/compiler.h> instead."
#endif

#define __used			__attribute__((__used__))
#define __must_check		__attribute__((warn_unused_result))
#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)
#define __always_inline		inline __attribute__((always_inline))
#define __deprecated		__attribute__((deprecated))
#define __packed		__attribute__((packed))
#define __weak			__attribute__((weak))
#define __alias(symbol)		__attribute__((alias(#symbol)))
#define __pure			__attribute__((pure))
#define __aligned(x)		__attribute__((aligned(x)))
#define __printf(a, b)		__attribute__((format(printf, a, b)))
#define __scanf(a, b)		__attribute__((format(scanf, a, b)))
#define __maybe_unused		__attribute__((unused))
#define __always_unused		__attribute__((unused))
#define __cold			__attribute__((cold))
#define __hot			__attribute__((hot))

/* Builtin functions */
#define __HAVE_BUILTIN_BSWAP32__
#define __HAVE_BUILTIN_BSWAP64__
#define __HAVE_BUILTIN_BSWAP16__
