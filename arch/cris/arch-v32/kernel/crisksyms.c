#include <linux/module.h>
#include <linux/irq.h>
#include <arch/dma.h>
#include <arch/intmem.h>
#include <mach/pinmux.h>
#include <arch/io.h>

/* Functions for allocating DMA channels */
/* DISABLED: EXPORT_SYMBOL(crisv32_request_dma); */
/* DISABLED: EXPORT_SYMBOL(crisv32_free_dma); */

/* Functions for handling internal RAM */
/* DISABLED: EXPORT_SYMBOL(crisv32_intmem_alloc); */
/* DISABLED: EXPORT_SYMBOL(crisv32_intmem_free); */
/* DISABLED: EXPORT_SYMBOL(crisv32_intmem_phys_to_virt); */
/* DISABLED: EXPORT_SYMBOL(crisv32_intmem_virt_to_phys); */

/* Functions for handling pinmux */
/* DISABLED: EXPORT_SYMBOL(crisv32_pinmux_alloc); */
/* DISABLED: EXPORT_SYMBOL(crisv32_pinmux_alloc_fixed); */
/* DISABLED: EXPORT_SYMBOL(crisv32_pinmux_dealloc); */
/* DISABLED: EXPORT_SYMBOL(crisv32_pinmux_dealloc_fixed); */
/* DISABLED: EXPORT_SYMBOL(crisv32_io_get_name); */
/* DISABLED: EXPORT_SYMBOL(crisv32_io_get); */

/* Functions masking/unmasking interrupts */
/* DISABLED: EXPORT_SYMBOL(crisv32_mask_irq); */
/* DISABLED: EXPORT_SYMBOL(crisv32_unmask_irq); */
