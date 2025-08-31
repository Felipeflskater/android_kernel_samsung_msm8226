#ifndef _LINUX_EXPORT_H
#define _LINUX_EXPORT_H

/* PostmarketOS: Simplified export.h - disables problematic EXPORT_SYMBOL macros */

/* All export macros disabled to avoid section/alignment issues */
#define EXPORT_SYMBOL(sym)              /* disabled */
#define EXPORT_SYMBOL_GPL(sym)          /* disabled */  
#define EXPORT_SYMBOL_GPL_FUTURE(sym)   /* disabled */
#define EXPORT_UNUSED_SYMBOL(sym)       /* disabled */
#define EXPORT_UNUSED_SYMBOL_GPL(sym)   /* disabled */

/* These were causing the "storage class specified for parameter" errors */
#define __EXPORT_SYMBOL(sym, sec)       /* disabled */

#endif /* _LINUX_EXPORT_H */
