#include "linux/types.h"
#include "linux/module.h"

/* Some of this are builtin function (some are not but could in the future),
 * so I *must* declare good prototypes for them and then EXPORT them.
 * The kernel code uses the macro defined by include/linux/string.h,
 * so I undef macros; the userspace code does not include that and I
 * add an EXPORT for the glibc one.
 */

#undef strlen
#undef strstr
#undef memcpy
#undef memset

extern size_t strlen(const char *);
extern void *memmove(void *, const void *, size_t);
extern void *memset(void *, int, size_t);
extern int printf(const char *, ...);

/* If it's not defined, the export is included in lib/string.c.*/
#ifdef __HAVE_ARCH_STRSTR
/* DISABLED: EXPORT_SYMBOL(strstr); */
#endif

#ifndef __x86_64__
extern void *memcpy(void *, const void *, size_t);
/* DISABLED: EXPORT_SYMBOL(memcpy); */
#endif

/* DISABLED: EXPORT_SYMBOL(memmove); */
/* DISABLED: EXPORT_SYMBOL(memset); */
/* DISABLED: EXPORT_SYMBOL(printf); */

/* Here, instead, I can provide a fake prototype. Yes, someone cares: genksyms.
 * However, the modules will use the CRC defined *here*, no matter if it is
 * good; so the versions of these symbols will always match
 */
#define EXPORT_SYMBOL_PROTO(sym)       \
	int sym(void);                  \
	EXPORT_SYMBOL(sym);

extern void readdir64(void) __attribute__((weak));
/* DISABLED: EXPORT_SYMBOL(readdir64); */
extern void truncate64(void) __attribute__((weak));
/* DISABLED: EXPORT_SYMBOL(truncate64); */

#ifdef CONFIG_ARCH_REUSE_HOST_VSYSCALL_AREA
/* DISABLED: EXPORT_SYMBOL(vsyscall_ehdr); */
/* DISABLED: EXPORT_SYMBOL(vsyscall_end); */
#endif

/* DISABLED: EXPORT_SYMBOL_PROTO(__errno_location); */

/* DISABLED: EXPORT_SYMBOL_PROTO(access); */
/* DISABLED: EXPORT_SYMBOL_PROTO(open); */
/* DISABLED: EXPORT_SYMBOL_PROTO(open64); */
/* DISABLED: EXPORT_SYMBOL_PROTO(close); */
/* DISABLED: EXPORT_SYMBOL_PROTO(read); */
/* DISABLED: EXPORT_SYMBOL_PROTO(write); */
/* DISABLED: EXPORT_SYMBOL_PROTO(dup2); */
/* DISABLED: EXPORT_SYMBOL_PROTO(__xstat); */
/* DISABLED: EXPORT_SYMBOL_PROTO(__lxstat); */
/* DISABLED: EXPORT_SYMBOL_PROTO(__lxstat64); */
/* DISABLED: EXPORT_SYMBOL_PROTO(__fxstat64); */
/* DISABLED: EXPORT_SYMBOL_PROTO(lseek); */
/* DISABLED: EXPORT_SYMBOL_PROTO(lseek64); */
/* DISABLED: EXPORT_SYMBOL_PROTO(chown); */
/* DISABLED: EXPORT_SYMBOL_PROTO(fchown); */
/* DISABLED: EXPORT_SYMBOL_PROTO(truncate); */
/* DISABLED: EXPORT_SYMBOL_PROTO(ftruncate64); */
/* DISABLED: EXPORT_SYMBOL_PROTO(utime); */
/* DISABLED: EXPORT_SYMBOL_PROTO(utimes); */
/* DISABLED: EXPORT_SYMBOL_PROTO(futimes); */
/* DISABLED: EXPORT_SYMBOL_PROTO(chmod); */
/* DISABLED: EXPORT_SYMBOL_PROTO(fchmod); */
/* DISABLED: EXPORT_SYMBOL_PROTO(rename); */
/* DISABLED: EXPORT_SYMBOL_PROTO(__xmknod); */

/* DISABLED: EXPORT_SYMBOL_PROTO(symlink); */
/* DISABLED: EXPORT_SYMBOL_PROTO(link); */
/* DISABLED: EXPORT_SYMBOL_PROTO(unlink); */
/* DISABLED: EXPORT_SYMBOL_PROTO(readlink); */

/* DISABLED: EXPORT_SYMBOL_PROTO(mkdir); */
/* DISABLED: EXPORT_SYMBOL_PROTO(rmdir); */
/* DISABLED: EXPORT_SYMBOL_PROTO(opendir); */
/* DISABLED: EXPORT_SYMBOL_PROTO(readdir); */
/* DISABLED: EXPORT_SYMBOL_PROTO(closedir); */
/* DISABLED: EXPORT_SYMBOL_PROTO(seekdir); */
/* DISABLED: EXPORT_SYMBOL_PROTO(telldir); */

/* DISABLED: EXPORT_SYMBOL_PROTO(ioctl); */

/* DISABLED: EXPORT_SYMBOL_PROTO(pread64); */
/* DISABLED: EXPORT_SYMBOL_PROTO(pwrite64); */

/* DISABLED: EXPORT_SYMBOL_PROTO(statfs); */
/* DISABLED: EXPORT_SYMBOL_PROTO(statfs64); */

/* DISABLED: EXPORT_SYMBOL_PROTO(getuid); */

/* DISABLED: EXPORT_SYMBOL_PROTO(fsync); */
/* DISABLED: EXPORT_SYMBOL_PROTO(fdatasync); */

/* DISABLED: EXPORT_SYMBOL_PROTO(lstat64); */
/* DISABLED: EXPORT_SYMBOL_PROTO(fstat64); */
/* DISABLED: EXPORT_SYMBOL_PROTO(mknod); */

/* Export symbols used by GCC for the stack protector. */
extern void __stack_smash_handler(void *) __attribute__((weak));
/* DISABLED: EXPORT_SYMBOL(__stack_smash_handler); */

extern long __guard __attribute__((weak));
/* DISABLED: EXPORT_SYMBOL(__guard); */

#ifdef _FORTIFY_SOURCE
extern int __sprintf_chk(char *str, int flag, size_t strlen, const char *format);
/* DISABLED: EXPORT_SYMBOL(__sprintf_chk); */
#endif
