/*
 * arch/arm/mach-lpc32xx/suspend.S
 *
 * Original authors: Dmitry Chigirev, Vitaly Wool <source@mvista.com>
 * Modified by Kevin Wells <kevin.wells@nxp.com>
 *
 * 2005 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#include <linux/linkage.h>
#include <asm/assembler.h>
#include <mach/platform.h>
#include <mach/hardware.h>

/* Using named register defines makes the code easier to follow */
#define WORK1_REGr0
#define WORK2_REGr1
#define SAVED_HCLK_DIV_REGr2
#define SAVED_HCLK_PLL_REGr3
#define SAVED_DRAM_CLKCTRL_REGr4
#define SAVED_PWR_CTRL_REGr5
#define CLKPWRBASE_REGr6
#define EMCBASE_REGr7

#define LPC32XX_EMC_STATUS_OFFS0x04
#define LPC32XX_EMC_STATUS_BUSY0x1
#define LPC32XX_EMC_STATUS_SELF_RFSH0x4

#define LPC32XX_CLKPWR_PWR_CTRL_OFFS0x44
#define LPC32XX_CLKPWR_HCLK_DIV_OFFS0x40
#define LPC32XX_CLKPWR_HCLKPLL_CTRL_OFFS 0x58

#define CLKPWR_PCLK_DIV_MASK0xFFFFFE7F

.text

ENTRY(lpc32xx_sys_suspend)
@ Save a copy of the used registers in IRAM, r0 is corrupted
adrr0, tmp_stack_end
stmfdr0!, {r3 - r7, sp, lr}

@ Load a few common register addresses
adrWORK1_REG, reg_bases
ldrCLKPWRBASE_REG, [WORK1_REG, #0]
ldrEMCBASE_REG, [WORK1_REG, #4]

ldrSAVED_PWR_CTRL_REG, [CLKPWRBASE_REG,\
#LPC32XX_CLKPWR_PWR_CTRL_OFFS]
orrWORK1_REG, SAVED_PWR_CTRL_REG, @ LPC32XX_CLKPWR_SDRAM_SELF_RFSH

@ Wait for SDRAM busy status to go busy and then idle
@ This guarantees a small windows where DRAM isn't busy
1:
ldrWORK2_REG, [EMCBASE_REG, @ LPC32XX_EMC_STATUS_OFFS]
andWORK2_REG, WORK2_REG, @ LPC32XX_EMC_STATUS_BUSY
cmpWORK2_REG, @ LPC32XX_EMC_STATUS_BUSY
bne1b @ Branch while idle
2:
ldrWORK2_REG, [EMCBASE_REG, @ LPC32XX_EMC_STATUS_OFFS]
andWORK2_REG, WORK2_REG, @ LPC32XX_EMC_STATUS_BUSY
cmpWORK2_REG, @ LPC32XX_EMC_STATUS_BUSY
beq2b @ Branch until idle

@ Setup self-refresh with support for manual exit of
@ self-refresh mode
strWORK1_REG, [CLKPWRBASE_REG, @ LPC32XX_CLKPWR_PWR_CTRL_OFFS]
orrWORK2_REG, WORK1_REG, @ LPC32XX_CLKPWR_UPD_SDRAM_SELF_RFSH
strWORK2_REG, [CLKPWRBASE_REG, @ LPC32XX_CLKPWR_PWR_CTRL_OFFS]
strWORK1_REG, [CLKPWRBASE_REG, @ LPC32XX_CLKPWR_PWR_CTRL_OFFS]

@ Wait for self-refresh acknowledge, clocks to the DRAM device
@ will automatically stop on start of self-refresh
3:
ldrWORK2_REG, [EMCBASE_REG, @ LPC32XX_EMC_STATUS_OFFS]
andWORK2_REG, WORK2_REG, @ LPC32XX_EMC_STATUS_SELF_RFSH
cmpWORK2_REG, @ LPC32XX_EMC_STATUS_SELF_RFSH
bne3b @ Branch until self-refresh mode starts

@ Enter direct-run mode from run mode
bicWORK1_REG, WORK1_REG, @ LPC32XX_CLKPWR_SELECT_RUN_MODE
strWORK1_REG, [CLKPWRBASE_REG, @ LPC32XX_CLKPWR_PWR_CTRL_OFFS]

@ Safe disable of DRAM clock in EMC block, prevents DDR sync
@ issues on restart
ldrSAVED_HCLK_DIV_REG, [CLKPWRBASE_REG,\
#LPC32XX_CLKPWR_HCLK_DIV_OFFS]
andWORK2_REG, SAVED_HCLK_DIV_REG, @ CLKPWR_PCLK_DIV_MASK
strWORK2_REG, [CLKPWRBASE_REG, @ LPC32XX_CLKPWR_HCLK_DIV_OFFS]

@ Save HCLK PLL state and disable HCLK PLL
ldrSAVED_HCLK_PLL_REG, [CLKPWRBASE_REG,\
#LPC32XX_CLKPWR_HCLKPLL_CTRL_OFFS]
bicWORK2_REG, SAVED_HCLK_PLL_REG, @ LPC32XX_CLKPWR_HCLKPLL_POWER_UP
strWORK2_REG, [CLKPWRBASE_REG, @ LPC32XX_CLKPWR_HCLKPLL_CTRL_OFFS]

@ Enter stop mode until an enabled event occurs
orrWORK1_REG, WORK1_REG, @ LPC32XX_CLKPWR_STOP_MODE_CTRL
strWORK1_REG, [CLKPWRBASE_REG, @ LPC32XX_CLKPWR_PWR_CTRL_OFFS]
.rept 9
nop
.endr

@ Clear stop status
bicWORK1_REG, WORK1_REG, @ LPC32XX_CLKPWR_STOP_MODE_CTRL

@ Restore original HCLK PLL value and wait for PLL lock
strSAVED_HCLK_PLL_REG, [CLKPWRBASE_REG,\
#LPC32XX_CLKPWR_HCLKPLL_CTRL_OFFS]
4:
ldrWORK2_REG, [CLKPWRBASE_REG, @ LPC32XX_CLKPWR_HCLKPLL_CTRL_OFFS]
andWORK2_REG, WORK2_REG, @ LPC32XX_CLKPWR_HCLKPLL_PLL_STS
bne4b

@ Re-enter run mode with self-refresh flag cleared, but no DRAM
@ update yet. DRAM is still in self-refresh
strSAVED_PWR_CTRL_REG, [CLKPWRBASE_REG,\
#LPC32XX_CLKPWR_PWR_CTRL_OFFS]

@ Restore original DRAM clock mode to restore DRAM clocks
strSAVED_HCLK_DIV_REG, [CLKPWRBASE_REG,\
#LPC32XX_CLKPWR_HCLK_DIV_OFFS]

@ Clear self-refresh mode
orrWORK1_REG, SAVED_PWR_CTRL_REG,\
#LPC32XX_CLKPWR_UPD_SDRAM_SELF_RFSH
strWORK1_REG, [CLKPWRBASE_REG, @ LPC32XX_CLKPWR_PWR_CTRL_OFFS]
strSAVED_PWR_CTRL_REG, [CLKPWRBASE_REG,\
#LPC32XX_CLKPWR_PWR_CTRL_OFFS]

@ Wait for EMC to clear self-refresh mode
5:
ldrWORK2_REG, [EMCBASE_REG, @ LPC32XX_EMC_STATUS_OFFS]
andWORK2_REG, WORK2_REG, @ LPC32XX_EMC_STATUS_SELF_RFSH
bne5b @ Branch until self-refresh has exited

@ restore regs and return
adrr0, tmp_stack
ldmfdr0!, {r3 - r7, sp, pc}

reg_bases:
.longIO_ADDRESS(LPC32XX_CLK_PM_BASE)
.longIO_ADDRESS(LPC32XX_EMC_BASE)

tmp_stack:
.long0, 0, 0, 0, 0, 0, 0
tmp_stack_end:

ENTRY(lpc32xx_sys_suspend_sz)
.word. - lpc32xx_sys_suspend
