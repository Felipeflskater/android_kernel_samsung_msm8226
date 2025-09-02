#ifndef _LINUX_EXPORT_H
#define _LINUX_EXPORT_H
/* PostmarketOS: All exports disabled */
#define EXPORT_SYMBOL(sym)
#define EXPORT_SYMBOL_GPL(sym)
#define EXPORT_SYMBOL_GPL_FUTURE(sym)
#define EXPORT_UNUSED_SYMBOL(sym)
#define EXPORT_UNUSED_SYMBOL_GPL(sym)
#define __EXPORT_SYMBOL(sym, sec)
#endif
