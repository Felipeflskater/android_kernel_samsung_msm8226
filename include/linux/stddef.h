#ifndef _LINUX_STDDEF_H
#define _LINUX_STDDEF_H

#include <uapi/linux/stddef.h>

#ifndef __ASSEMBLY__

/* Proteção robusta contra redefinições de false/true */
#ifndef __cplusplus
#undef false
#undef true
#ifndef _Bool
typedef unsigned char _Bool;
#endif
#define bool _Bool
#define false 0
#define true 1
#else
/* Em C++, usar os valores nativos */
const bool false = 0;
const bool true = 1;
#endif

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER)	__compiler_offsetof(TYPE, MEMBER)
#else
#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)
#endif

#endif /* __ASSEMBLY__ */
#endif /* _LINUX_STDDEF_H */
