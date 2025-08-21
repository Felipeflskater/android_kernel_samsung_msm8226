#ifndef _ASMARM_MMCONTEXT_H
#define _ASMARM_MMCONTEXT_H

/*
 * mm_context_t for ARM.
 * Used to store MMU/ASID state.
 * On MSM8226 (Cortex-A7), this is typically a simple unsigned long.
 * But since asm-offsets.c uses .context.id, we define it as a struct.
 */

typedef struct {
    unsigned long id;
} mm_context_t;

#endif
