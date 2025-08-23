#ifndef _ASM_ARM_COMPILER_H
#define _ASM_ARM_COMPILER_H

#ifdef __KERNEL__

/*
 * Definições de espaços de endereço para verificação em tempo de compilação.
 * Em ambientes de build de porta como pmOS, muitas vezes simplificamos essas macros
 * para evitar erros de build, já que o controle rigoroso de espaço de memória
 * não é necessário em arquivos como asm-offsets.c.
 */

#ifndef __user
#define __user		__attribute__((address_space(1)))
#endif

#ifndef __kernel
#define __kernel	__attribute__((address_space(0)))
#endif

#ifndef __iomem
#define __iomem		__attribute__((noderef, address_space(2)))
#endif

#define __acquires(x)	__attribute__((context(x, 1, 1)))
#define __releases(x)	__attribute__((context(x, -1, -1)))
#define __percpu	__attribute__((__percpu__))
#define __rcu		__attribute__((rcu))

/*
 * Macro de verificação para garantir que o registrador foi alocado corretamente
 * em assembly inline. Usado em alguns trechos críticos do kernel.
 */
#define __asmeq(x, y)  ".ifnc " x "," y " ; .err ; .endif\n\t"

#endif /* __KERNEL__ */

#endif /* _ASM_ARM_COMPILER_H */
