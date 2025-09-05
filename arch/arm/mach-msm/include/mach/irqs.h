/* PostmarketOS: Completely rewritten MSM IRQs header */
#ifndef __ASM_ARCH_MSM_IRQS_H
#define __ASM_ARCH_MSM_IRQS_H

#define MSM_IRQ_BIT(irq)     (1 << ((irq) & 31))

/* PostmarketOS: MSM8226 Timer interrupts - CRITICAL DEFINITIONS */
#define INT_GP_TIMER_EXP        32
#define INT_DEBUG_TIMER_EXP     40

/* PostmarketOS: Additional MSM8226 interrupts */
#define INT_ADSP_A9_A11         0
#define INT_UART1               1
#define INT_UART2               2
#define INT_USB_HS              3

/* PostmarketOS: Standard MSM interrupts */
#define MSM_GPIO_TO_INT(n)      ((n) + 64)
#define MSM_GPIO_TO_INT_BASE    64

/* PostmarketOS: Interrupt counts */
#define NR_MSM_IRQS             256
#define NR_GPIO_IRQS            146  
#define NR_BOARD_IRQS           64
#define NR_IRQS                 (NR_MSM_IRQS + NR_GPIO_IRQS + NR_BOARD_IRQS)

#endif /* __ASM_ARCH_MSM_IRQS_H */
