#ifndef __ASM_MACH_MSM_IRQS_H
#define __ASM_MACH_MSM_IRQS_H

/*
 * IRQ counts for Samsung Matisse (msm8226)
 * Values based on common MSM8x26 platforms.
 */

#ifndef NR_MSM_IRQS
#define NR_MSM_IRQS         128
#endif

#ifndef NR_GPIO_IRQS
#define NR_GPIO_IRQS        85
#endif

#ifndef NR_BOARD_IRQS
#define NR_BOARD_IRQS       32
#endif

/*
 * Recalculate total IRQs
 */
#undef NR_IRQS
#define NR_IRQS             (NR_MSM_IRQS + NR_GPIO_IRQS + NR_BOARD_IRQS)

#endif /* __ASM_MACH_MSM_IRQS_H */
