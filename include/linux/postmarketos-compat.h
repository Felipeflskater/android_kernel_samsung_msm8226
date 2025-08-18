#ifndef _LINUX_POSTMARKETOS_COMPAT_H
#define _LINUX_POSTMARKETOS_COMPAT_H

/* Compatibilidade postmarketOS para kernel 3.4.x - Previne conflitos de bool */

/* Limpar definições anteriores */
#ifdef false
#undef false
#endif
#ifdef true  
#undef true
#endif
#ifdef bool
#undef bool
#endif

/* Garantir definições consistentes */
#ifndef __cplusplus
#ifndef _Bool
typedef unsigned char _Bool;
#endif
#define bool _Bool
#define false 0
#define true 1
#endif

#endif /* _LINUX_POSTMARKETOS_COMPAT_H */
