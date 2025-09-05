.arm
.syntax unified
/* PostmarketOS: ARM mode forced */
/*
 *  linux/arch/arm/mm/proc-v7.S
 *
 *  Copyright (C) 2001 Deep Blue Solutions Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *  This is the "shell" of the ARMv7 processor support.
 */
















ENTRY(cpu_v7_proc_init)
mov pc, lr
ENDPROC(cpu_v7_proc_init)

ENTRY(cpu_v7_proc_fin)
mrc p15, 0, r0, c1, c0, 0@ ctrl register
bicr0, r0, #0x1000@ ...i............
bicr0, r0, #0x0006@ .............ca.
mcr p15, 0, r0, c1, c0, 0@ disable caches
mov pc, lr
ENDPROC(cpu_v7_proc_fin)

/*
 *cpu_v7_reset(loc)
 *
 *Perform a soft reset of the system.  Put the CPU into the
 *same state as it would be if it had been reset, and branch
 *to what would be the reset vector.
 *
 *- loc   - location to jump to for soft reset
 *
 *This code must be executed using a flat identity mapping with
 *      caches disabled.
 */
.align 5
.pushsection .idmap.text, "ax", "ax"
ENTRY(cpu_v7_reset)
mrc p15, 0, r1, c1, c0, 0@ ctrl register
bicr1, r1, #0x1@ ...............m
 THUMB(bicr1, r1, #1 << 30 )@ SCTLR.TE (Thumb exceptions)
mcr p15, 0, r1, c1, c0, 0@ disable MMU
mcr     p15, 0, ip, c8, c7, 0           @ invalidate I & D,flush TLB
mcr     p15, 0, ip, c7, c5, 6           @ flush BTC
dsb
isb
mov pc, r0
ENDPROC(cpu_v7_reset)
.popsection

/*
 *cpu_v7_do_idle()
 *
 *Idle the processor (eg, wait for interrupt).
 *
 *IRQs are already disabled.
 */
ENTRY(cpu_v7_do_idle)
dsb@ WFI may enter a low-power mode
wfi
mov pc, lr
ENDPROC(cpu_v7_do_idle)

ENTRY(cpu_v7_dcache_clean_area)

dcache_line_size r2, r3
1:mcr p15, 0, r0, c7, c10, 1@ clean D entry
addr0, r0, r2
subsr1, r1, r2
bhi 1b
dsb

mov pc, lr
ENDPROC(cpu_v7_dcache_clean_area)

.asciz "ARMv7 Processor"
.align

/* Suspend/resume support: derived from arch/arm/mach-s5pv210/sleep.S */
.globl cpu_v7_suspend_size
.equ cpu_v7_suspend_size, 4 * 8

ENTRY(cpu_v7_do_suspend)
stmfdsp!, {r4 - r11, lr}
mrc p15, 0, r4, c13, c0, 0@ FCSE/PID
mrc p15, 0, r5, c13, c0, 3@ User r/o thread ID
stmiar0!, {r4 - r5}
mrc p15, 0, r6, c3, c0, 0@ Domain ID
mrc p15, 0, r7, c2, c0, 1@ TTB 1
mrc p15, 0, r11, c2, c0, 2@ TTB control register
mrc p15, 0, r8, c1, c0, 0@ Control register
mrc p15, 0, r9, c1, c0, 1@ Auxiliary control register
mrc p15, 0, r10, c1, c0, 2@ Co-processor access control
stmiar0, {r6 - r11}
ldmfdsp!, {r4 - r11, pc}
ENDPROC(cpu_v7_do_suspend)

ENTRY(cpu_v7_do_resume)
movip,
mcr p15, 0, ip, c8, c7, 0@ invalidate TLBs
mcr p15, 0, ip, c7, c5, 0@ invalidate I cache
mcr p15, 0, ip, c13, c0, 1@ set reserved context ID
ldmia r0!, {r4 - r5}
mcr p15, 0, r4, c13, c0, 0@ FCSE/PID
mcr p15, 0, r5, c13, c0, 3@ User r/o thread ID
ldmia r0, {r6 - r11}

mcr p15, 0, r6, c3, c0, 0@ Domain ID


ALT_SMP(orr r1, r1, @ TTB_FLAGS_SMP)
ALT_UP(orr r1, r1, @ TTB_FLAGS_UP)


mcr p15, 0, r1, c2, c0, 0@ TTB 0

mcr p15, 0, r7, c2, c0, 1@ TTB 1

mcr p15, 0, r11, c2, c0, 2@ TTB control register



mov r4, r0
ldr r0, =0x3f806221
smc
movr0, r4
/* Flush TLB */
mcr    p15, 0, r0, c8, c3, 0
dsb


mrc p15, 0, r4, c1, c0, 1@ Read Auxiliary control register
teq r4, r9@ Is it already set?
mcrne p15, 0, r9, c1, c0, 1@ No, so write it
mcr p15, 0, r10, c1, c0, 2@ Co-processor access control
ldr r4, =PRRR@ PRRR
ldr r5, =NMRR@ NMRR
mcr p15, 0, r4, c10, c2, 0@ write PRRR
mcr p15, 0, r5, c10, c2, 1@ write NMRR
isb
dsb
mov r0, r8@ control register
bcpu_resume_mmu
ENDPROC(cpu_v7_do_resume)


__CPUINIT

/*
 *__v7_setup
 *
 *Initialise TLB, Caches, and MMU state ready to switch the MMU
 *on.  Return in r0 the new CP15 C1 control register setting.
 *
 *This should be able to cover all ARMv7 cores.
 *
 *It is assumed that:
 *- cache type register is implemented
 */
__v7_ca5mp_setup:
__v7_ca9mp_setup:
movr10, @ (1 << 0)@ TLB ops broadcasting
b 1f
__v7_ca7mp_setup:
__v7_ca15mp_setup:
mov r10,
1:

ALT_SMP(mrc p15, 0, r0, c1, c0, 1)
ALT_UP(movr0, @ (1 << 6))@ fake it for UP
tstr0, @ (1 << 6)@ SMP/nAMP mode enabled?
orreqr0, r0, @ (1 << 6)@ Enable SMP/nAMP mode
orreqr0, r0, r10@ Enable CPU-specific SMP bits
mcreqp15, 0, r0, c1, c0, 1

__v7_setup:
adr r12, __v7_setup_stack@ the local stack
stmia r12, {r0-r5, r7, r9, r11, lr}
bl v7_flush_dcache_all
ldmia r12, {r0-r5, r7, r9, r11, lr}

mrc p15, 0, r0, c0, c0, 0@ read main ID register
andr10, r0, #0xff000000@ ARM?
teq r10,
bne 3f
andr5, r0, #0x00f00000@ variant
andr6, r0, #0x0000000f@ revision
orrr6, r6, r5, lsr #20-4@ combine variant and revision
ubfxr0, r0, #4, #12@ primary part number

/* Cortex-A8 Errata */
ldr r10, =0x00000c08@ Cortex-A8 primary part number
teq r0, r10
bne 2f

teqr5, #0x00100000@ only present in r1p*
mrceqp15, 0, r10, c1, c0, 1@ read aux control register
orreqr10, r10, @ (1 << 6)@ set IBE to 1
mcreqp15, 0, r10, c1, c0, 1@ write aux control register


teqr6, #0x20@ only present in r2p0
mrceqp15, 0, r10, c1, c0, 1@ read aux control register
orreqr10, r10, @ (1 << 5)@ set L1NEON to 1
orreqr10, r10, @ (1 << 9)@ set PLDNOP to 1
mcreqp15, 0, r10, c1, c0, 1@ write aux control register


teqr6, #0x20@ only present in r2p0
mrceqp15, 1, r10, c9, c0, 2@ read L2 cache aux ctrl register
tsteq r10,
orreqr10, r10, @ (1 << 22)@ set the Write Allocate disable bit
mcreqp15, 1, r10, c9, c0, 2@ write the L2 cache aux ctrl register

b 3f

/* Cortex-A9 Errata */
2:ldr r10, =0x00000c09@ Cortex-A9 primary part number
teq r0, r10
bne 3f

cmpr6, #0x22@ only present up to r2p2
mrclep15, 0, r10, c15, c0, 1@ read diagnostic register
orrler10, r10, #1 << 4@ set bit
mcrlep15, 0, r10, c15, c0, 1@ write diagnostic register


teqr6, #0x20@ present in r2p0
teqner6, #0x21@ present in r2p1
teqner6, #0x22@ present in r2p2
mrceqp15, 0, r10, c15, c0, 1@ read diagnostic register
orreqr10, r10, #1 << 12@ set bit
orreqr10, r10, #1 << 22@ set bit
mcreqp15, 0, r10, c15, c0, 1@ write diagnostic register


teqr5, #0x00200000@ only present in r2p*
mrceqp15, 0, r10, c15, c0, 1@ read diagnostic register
orreqr10, r10, #1 << 6@ set bit
mcreqp15, 0, r10, c15, c0, 1@ write diagnostic register


ALT_SMP(cmp r6, #0x30)@ present prior to r3p0
ALT_UP_B(1f)
mrcltp15, 0, r10, c15, c0, 1@ read diagnostic register
orrltr10, r10, #1 << 11@ set bit
mcrltp15, 0, r10, c15, c0, 1@ write diagnostic register
1:


3:mov r10,
mcr p15, 0, r10, c7, c5, 0@ I+BTB cache invalidate

mcr p15, 0, r10, c8, c7, 0@ invalidate I + D TLBs
v7_ttb_setup r10, r4, r8, r5@ TTBCR, TTBRx setup
ldr r5, =PRRR@ PRRR
ldr r6, =NMRR@ NMRR
mcr p15, 0, r5, c10, c2, 0@ write PRRR
mcr p15, 0, r6, c10, c2, 1@ write NMRR

dsb@ Complete invalidations


mov     r0,
mcr     p15, 3, r0, c15, c0, 3          @ set L2CR1


mrc     p15, 0, r0, c1, c0, 1           @ read ACTLR

orr     r0, r0, #0x37                   @ turn on L1/L2 error reporting

bic     r0, r0,


orr    r0, r0, #0x1 << 24     @ optimal setting for Scorpion MP


mcr     p15, 0, r0, c1, c0, 1           @ write ACTLR



mrc     p15, 3, r0, c15, c0, 2  @ optimal setting for Scorpion MP
orr         r0, r0,
mcr     p15, 3, r0, c15, c0, 2



mrc p15, 0, r0, c0, c1, 0@ read ID_PFR0 for ThumbEE
andr0, r0, @ (0xf << 12)@ ThumbEE enabled field
teqr0, @ (1 << 12)@ check if ThumbEE is present
bne 1f
mov r5,
mcrp14, 6, r5, c1, c0, 0@ Initialize TEEHBR to 0
mrcp14, 6, r0, c0, c0, 0@ load TEECR
orrr0, r0, #1@ set the 1st bit in order to
mcrp14, 6, r0, c0, c0, 0@ stop userspace TEEHBR access
1:

adr r5, v7_crval
ldmia r5, {r5, r6}

orrr6, r6, #1 << 25@ big-endian page tables


orr     r5, r5, @ (1 << 10)              @ set SW bit in "clear"
bic     r6, r6, @ (1 << 10)              @ clear it in "mmuset"

   mrc p15, 0, r0, c1, c0, 0@ read control register
bicr0, r0, r5@ clear bits them
orrr0, r0, r6@ set them
 THUMB(orrr0, r0, #1 << 30)@ Thumb exceptions
mov pc, lr@ return to head.S:__ret
ENDPROC(__v7_setup)

.align 2
__v7_setup_stack:
.space 4 * 11@ 11 registers

__INITDATA

@ define struct processor (see <asm/proc-fns.h> and proc-macros.S)
define_processor_functions v7, dabort=v7_early_abort, pabort=v7_pabort, suspend=1

.section ".rodata"

.asciz "armv7"
.asciz "v7"
.align

.section ".proc.info.init", @ alloc, @ execinstr

/*
 * Standard v7 proc info content
 */
.macro __v7_proc initfunc, mm_mmuflags = 0, io_mmuflags = 0, hwcaps = 0
ALT_SMP(.longPMD_TYPE_SECT | PMD_SECT_AP_WRITE | PMD_SECT_AP_READ | \
PMD_SECT_AF | PMD_FLAGS_SMP | \mm_mmuflags)
ALT_UP(.longPMD_TYPE_SECT | PMD_SECT_AP_WRITE | PMD_SECT_AP_READ | \
PMD_SECT_AF | PMD_FLAGS_UP | \mm_mmuflags)
.longPMD_TYPE_SECT | PMD_SECT_AP_WRITE | \
PMD_SECT_AP_READ | PMD_SECT_AF | \io_mmuflags
b\initfunc
.long cpu_arch_name
.long cpu_elf_name
.longHWCAP_SWP | HWCAP_HALF | HWCAP_THUMB | HWCAP_FAST_MULT | \
HWCAP_EDSP | \hwcaps
.long cpu_v7_name
.long v7_processor_functions
.long v7wbi_tlb_fns
.long v6_user_fns
.long v7_cache_fns
.endm


/*
 * ARM Ltd. Cortex A5 processor.
 */
.type   __v7_ca5mp_proc_info, @ object
__v7_ca5mp_proc_info:
.long 0x410fc050
.long 0xff0ffff0
__v7_proc __v7_ca5mp_setup
.size __v7_ca5mp_proc_info, . - __v7_ca5mp_proc_info

/*
 * ARM Ltd. Cortex A9 processor.
 */
.type   __v7_ca9mp_proc_info, @ object
__v7_ca9mp_proc_info:
.long 0x410fc090
.long 0xff0ffff0
__v7_proc __v7_ca9mp_setup
.size __v7_ca9mp_proc_info, . - __v7_ca9mp_proc_info


/*
 * ARM Ltd. Cortex A7 processor.
 */
.type __v7_ca7mp_proc_info, @ object
__v7_ca7mp_proc_info:
.long 0x410fc070
.long 0xff0ffff0
__v7_proc __v7_ca7mp_setup, hwcaps = HWCAP_IDIV
.size __v7_ca7mp_proc_info, . - __v7_ca7mp_proc_info

/*
 * ARM Ltd. Cortex A15 processor.
 */
.type __v7_ca15mp_proc_info, @ object
__v7_ca15mp_proc_info:
.long 0x410fc0f0
.long 0xff0ffff0
__v7_proc __v7_ca15mp_setup, hwcaps = HWCAP_IDIV
.size __v7_ca15mp_proc_info, . - __v7_ca15mp_proc_info

/*
 * Qualcomm Inc. Krait processors.
 */
.type __krait_proc_info, @ object
__krait_proc_info:
.long 0x510f0400@ Required ID value
.long 0xff0ffc00@ Mask for ID
__v7_proc __v7_setup, hwcaps = HWCAP_IDIV
.size __krait_proc_info, . - __krait_proc_info

/*
 * Match any ARMv7 processor core.
 */
.type __v7_proc_info, @ object
	/*
	 * Qualcomm MSM8226 - Samsung Matisse3G
	 */
	.type   __msm8226_proc_info,
__msm8226_proc_info:
	.long	0x410fc070		/* Cortex-A7 r0p0 */
	.long	0xff0ffff0
	__v7_proc __v7_setup, hwcaps = HWCAP_IDIV
	.size	__msm8226_proc_info, . - __msm8226_proc_info


__v7_proc_info:
.long 0x000f0000@ Required ID value
.long 0x000f0000@ Mask for ID
__v7_proc __v7_setup
.size __v7_proc_info, . - __v7_proc_info
