#ifndef _LINUX_SPARSE_H
#define _LINUX_SPARSE_H

#ifdef __CHECKER__
# define __user         __attribute__((noderef, address_space(1)))
# define __kernel       __attribute__((address_space(0)))
# define __iomem        __attribute__((noderef, address_space(2)))
# define __safe         __attribute__((safe))
# define __force        __attribute__((force))
# define __nocast       __attribute__((nocast))
# define __acquires(x)  __attribute__((context(x,0,1)))
# define __releases(x)  __attribute__((context(x,1,0)))
# define __acquire(x)   __context__(x,1)
# define __release(x)   __context__(x,-1)
# define __cond_lock(x,c) ((c) ? ({ __acquire(x); 1; }) : 0)
# define __percpu       __attribute__((noderef, address_space(3)))
# define __rcu          __attribute__((noderef, address_space(4)))
#else
# define __user
# define __kernel
# define __iomem
# define __safe
# define __force
# define __nocast
# define __acquires(x)
# define __releases(x)
# define __acquire(x)   (void)0
# define __release(x)   (void)0
# define __cond_lock(x,c) (c)
# define __percpu
# define __rcu
#endif

#endif /* _LINUX_SPARSE_H */
