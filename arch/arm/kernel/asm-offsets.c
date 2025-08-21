/*
 * Generate definitions needed by assembly language modules.
 * This code generates raw asm output which is post-processed to extract
 * and format the required data.
 */

#include <linux/sparse.h>
#include <linux/stddef.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/kbuild.h>
#include <asm/thread_info.h>
#include <asm/memory.h>

int main(void)
{
  DEFINE(TSK_ACTIVE_MM,		offsetof(struct task_struct, active_mm));
  BLANK();
  DEFINE(TI_FLAGS,		offsetof(struct thread_info, flags));
  DEFINE(TI_PREEMPT,		offsetof(struct thread_info, preempt_count));
  DEFINE(TI_ADDR_LIMIT,		offsetof(struct thread_info, addr_limit));
  DEFINE(TI_TASK,		offsetof(struct thread_info, task));
  DEFINE(TI_EXEC_DOMAIN,	offsetof(struct thread_info, exec_domain));
  DEFINE(TI_CPU,		offsetof(struct thread_info, cpu));
  DEFINE(TI_CPU_DOMAIN,		offsetof(struct thread_info, cpu_domain));
  DEFINE(TI_CPU_SAVE,		offsetof(struct thread_info, cpu_context));
  DEFINE(TI_USED_CP,		offsetof(struct thread_info, used_cp));
  DEFINE(TI_TP_VALUE,		offsetof(struct thread_info, tp_value));
  DEFINE(TI_FPSTATE,		offsetof(struct thread_info, fpstate));
  BLANK();
  DEFINE(S_R0,			offsetof(struct pt_regs, ARM_r0));
  DEFINE(S_R1,			offsetof(struct pt_regs, ARM_r1));
  DEFINE(S_R2,			offsetof(struct pt_regs, ARM_r2));
  DEFINE(S_R3,			offsetof(struct pt_regs, ARM_r3));
  DEFINE(S_R4,			offsetof(struct pt_regs, ARM_r4));
  DEFINE(S_R5,			offsetof(struct pt_regs, ARM_r5));
  DEFINE(S_R6,			offsetof(struct pt_regs, ARM_r6));
  DEFINE(S_R7,			offsetof(struct pt_regs, ARM_r7));
  DEFINE(S_R8,			offsetof(struct pt_regs, ARM_r8));
  DEFINE(S_R9,			offsetof(struct pt_regs, ARM_r9));
  DEFINE(S_R10,			offsetof(struct pt_regs, ARM_r10));
  DEFINE(S_FP,			offsetof(struct pt_regs, ARM_fp));
  DEFINE(S_IP,			offsetof(struct pt_regs, ARM_ip));
  DEFINE(S_SP,			offsetof(struct pt_regs, ARM_sp));
  DEFINE(S_LR,			offsetof(struct pt_regs, ARM_lr));
  DEFINE(S_PC,			offsetof(struct pt_regs, ARM_pc));
  DEFINE(S_PSR,			offsetof(struct pt_regs, ARM_cpsr));
  DEFINE(S_OLD_R0,		offsetof(struct pt_regs, ARM_ORIG_r0));
  DEFINE(S_FRAME_SIZE,		sizeof(struct pt_regs));
  BLANK();
  return 0;
}
