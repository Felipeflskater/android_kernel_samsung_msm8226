#ifndef _LINUX_EXPORT_H
#define _LINUX_EXPORT_H

/*
 * PostmarketOS: Completely disabled export system
 * This eliminates all "storage class specified for parameter" errors
 * caused by section attributes and symbol exports
 */

/* All export macros completely disabled */
#define EXPORT_SYMBOL(sym)
#define EXPORT_SYMBOL_GPL(sym)  
#define EXPORT_SYMBOL_GPL_FUTURE(sym)
#define EXPORT_UNUSED_SYMBOL(sym)
#define EXPORT_UNUSED_SYMBOL_GPL(sym)

/* Internal macros also disabled */
#define __EXPORT_SYMBOL(sym, sec)

#endif /* _LINUX_EXPORT_H */
