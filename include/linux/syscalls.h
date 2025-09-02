#ifndef _LINUX_SYSCALLS_H
#define _LINUX_SYSCALLS_H

/*
 * PostmarketOS: Simplified syscalls header
 * Disables problematic SYSCALL_DEFINE macros
 */

#include <linux/types.h>

/* Disable all SYSCALL_DEFINE macros */
#define SYSCALL_DEFINE1(name, ...) asmlinkage long sys_##name(__VA_ARGS__)
#define SYSCALL_DEFINE2(name, ...) asmlinkage long sys_##name(__VA_ARGS__)
#define SYSCALL_DEFINE3(name, ...) asmlinkage long sys_##name(__VA_ARGS__)
#define SYSCALL_DEFINE4(name, ...) asmlinkage long sys_##name(__VA_ARGS__)
#define SYSCALL_DEFINE5(name, ...) asmlinkage long sys_##name(__VA_ARGS__)
#define SYSCALL_DEFINE6(name, ...) asmlinkage long sys_##name(__VA_ARGS__)

/* Define missing types */
typedef unsigned long aio_context_t;
typedef unsigned int qid_t;
typedef int key_serial_t;

#endif /* _LINUX_SYSCALLS_H */
