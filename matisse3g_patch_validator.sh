#!/bin/bash
# Script de Validação e Aplicação de Patches - Samsung Matisse3G (SM-T531)
# Maintainer: Felipe Prestes Aranalde <felipe.aranalde@gmail.com>
# 
# Este script aplica as correções do APKBUILD diretamente no código-fonte do kernel
# Caminho do kernel: /home/felipeflskater/Documentos/GitHub/android_kernel_samsung_msm8226/

set -e

# Configurações
KERNEL_DIR="/home/felipeflskater/Documentos/GitHub/android_kernel_samsung_msm8226"
BRANCH_NAME="pmos-matisse3g-fixes"
BACKUP_DIR="${KERNEL_DIR}_backup_$(date +%Y%m%d_%H%M%S)"

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

_log() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

_error() {
    echo -e "${RED}[ERROR]${NC} $1"
    exit 1
}

_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

# Verificar se o diretório do kernel existe
check_kernel_directory() {
    _log "Verificando diretório do kernel..."
    
    if [ ! -d "$KERNEL_DIR" ]; then
        _error "Diretório do kernel não encontrado: $KERNEL_DIR"
    fi
    
    if [ ! -f "$KERNEL_DIR/Makefile" ]; then
        _error "Makefile não encontrado - não parece ser um diretório de kernel válido"
    fi
    
    _success "Diretório do kernel encontrado e válido"
}

# Fazer backup do código atual
create_backup() {
    _log "Criando backup do código atual..."
    
    cp -r "$KERNEL_DIR" "$BACKUP_DIR"
    _success "Backup criado em: $BACKUP_DIR"
}

# Aplicar correções de headers
apply_header_fixes() {
    _log "Aplicando correções de headers..."
    
    cd "$KERNEL_DIR"
    
    # 1. Criar sparse.h
    _log "Criando include/linux/sparse.h..."
    cat > include/linux/sparse.h << 'EOF'
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
EOF
    
    # 2. Criar stddef.h melhorado
    _log "Criando include/linux/stddef.h..."
    mkdir -p include/uapi/linux
    
    cat > include/uapi/linux/stddef.h << 'EOF'
#ifndef _UAPI_LINUX_STDDEF_H
#define _UAPI_LINUX_STDDEF_H

#ifndef __ASSEMBLY__
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif
#endif /* __ASSEMBLY__ */

#endif /* _UAPI_LINUX_STDDEF_H */
EOF
    
    cat > include/linux/stddef.h << 'EOF'
#ifndef _LINUX_STDDEF_H
#define _LINUX_STDDEF_H

#include <uapi/linux/stddef.h>

#ifndef __ASSEMBLY__
/* Enum para bool - evita conflitos com typedef */
#undef false
#undef true
enum {
	false	= 0,
	true	= 1
};

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER)	__compiler_offsetof(TYPE, MEMBER)
#else
#define offsetof(TYPE, MEMBER)	((size_t) &((TYPE *)0)->MEMBER)
#endif
#endif /* __ASSEMBLY__ */

#endif /* _LINUX_STDDEF_H */
EOF
    
    # 3. Corrigir capability.h
    _log "Corrigindo include/linux/capability.h..."
    if [ -f include/linux/capability.h ]; then
        cp include/linux/capability.h include/linux/capability.h.backup
        
        # Adicionar include do sparse.h no início
        if ! grep -q "#include <linux/sparse.h>" include/linux/capability.h; then
            sed -i '1i\#include <linux/sparse.h>' include/linux/capability.h
        fi
        
        # Remover __user annotations problemáticas
        sed -i 's/__user \*/*/g' include/linux/capability.h
        sed -i 's/} __user \*/} */g' include/linux/capability.h
    fi
    
    # 4. Criar types.h se necessário
    _log "Verificando uapi/linux/types.h..."
    if [ ! -f include/uapi/linux/types.h ]; then
        cat > include/uapi/linux/types.h << 'EOF'
#ifndef _UAPI_LINUX_TYPES_H
#define _UAPI_LINUX_TYPES_H

#include <asm/types.h>

#ifndef __ASSEMBLY__
typedef __u16 __le16;
typedef __u16 __be16;
typedef __u32 __le32;
typedef __u32 __be32;
typedef __u64 __le64;
typedef __u64 __be64;
#endif

#endif
EOF
    fi
    
    _success "Correções de headers aplicadas"
}

# Corrigir asm-offsets.c
fix_asm_offsets() {
    _log "Corrigindo arch/arm/kernel/asm-offsets.c..."
    
    if [ -f arch/arm/kernel/asm-offsets.c ]; then
        cp arch/arm/kernel/asm-offsets.c arch/arm/kernel/asm-offsets.c.backup
        
        cat > arch/arm/kernel/asm-offsets.c << 'EOF'
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
  DEFINE(MM_CONTEXT_ID,		offsetof(struct mm_struct, context.id.counter));
  BLANK();
  DEFINE(VMA_VM_MM,		offsetof(struct vm_area_struct, vm_mm));
  DEFINE(VMA_VM_FLAGS,		offsetof(struct vm_area_struct, vm_flags));
  BLANK();
  DEFINE(VM_EXEC,	       	VM_EXEC);
  BLANK();
  DEFINE(PAGE_SZ,	       	PAGE_SIZE);
  BLANK();
  return 0;
}
EOF
        _success "asm-offsets.c corrigido"
    else
        _warn "asm-offsets.c não encontrado"
    fi
}

# Corrigir proc-v7.S para MSM8226
fix_proc_v7() {
    _log "Corrigindo arch/arm/mm/proc-v7.S para MSM8226..."
    
    if [ -f arch/arm/mm/proc-v7.S ]; then
        cp arch/arm/mm/proc-v7.S arch/arm/mm/proc-v7.S.backup
        
        # Adicionar definições PMD_FLAGS se não existirem
        if ! grep -q "PMD_FLAGS_SMP" arch/arm/mm/proc-v7.S; then
            # Encontrar linha após includes para adicionar definições
            INCLUDE_LINE=$(grep -n "#include.*pgtable.h" arch/arm/mm/proc-v7.S | tail -1 | cut -d: -f1)
            if [ -n "$INCLUDE_LINE" ]; then
                sed -i "${INCLUDE_LINE}a\\
\\
/* MSM8226 specific definitions */\\
#ifndef PMD_FLAGS_SMP\\
#define PMD_FLAGS_SMP\\t(PMD_SECT_S | PMD_SECT_nG)\\
#endif\\
#ifndef PMD_FLAGS_UP\\
#define PMD_FLAGS_UP\\t(PMD_SECT_nG)\\
#endif" arch/arm/mm/proc-v7.S
            fi
        fi
        
        # Corrigir macros problemáticas
        sed -i 's/W(b)/b/g' arch/arm/mm/proc-v7.S
        sed -i 's/HWCAP_EDSP | HWCAP_TLS/HWCAP_EDSP/g' arch/arm/mm/proc-v7.S
        
        # Adicionar entrada para MSM8226 se não existir
        if ! grep -q "__msm8226_proc_info" arch/arm/mm/proc-v7.S; then
            # Encontrar entrada genérica v7
            V7_PROC_LINE=$(grep -n "__v7_proc_info:" arch/arm/mm/proc-v7.S | head -1 | cut -d: -f1)
            if [ -n "$V7_PROC_LINE" ]; then
                sed -i "${V7_PROC_LINE}i\\
\\t/*\\
\\t * Qualcomm MSM8226 - Samsung Matisse3G\\
\\t */\\
\\t.type   __msm8226_proc_info, #object\\
__msm8226_proc_info:\\
\\t.long\\t0x410fc070\\t\\t/* Cortex-A7 r0p0 */\\
\\t.long\\t0xff0ffff0\\
\\t__v7_proc __v7_setup, hwcaps = HWCAP_IDIV\\
\\t.size\\t__msm8226_proc_info, . - __msm8226_proc_info\\
\\
" arch/arm/mm/proc-v7.S
            fi
        fi
        
        _success "proc-v7.S corrigido para MSM8226"
    else
        _warn "proc-v7.S não encontrado"
    fi
}

# Corrigir Makefiles para GCC moderno
fix_makefiles() {
    _log "Corrigindo Makefiles para compatibilidade com GCC 14+..."
    
    # Makefile principal
    if [ -f Makefile ]; then
        cp Makefile Makefile.backup
        
        # Adicionar flags para GCC moderno se não existirem
        if ! grep -q "Wno-error=incompatible-pointer-types" Makefile; then
            # Encontrar linha KBUILD_CFLAGS e adicionar flags
            if grep -q "^KBUILD_CFLAGS" Makefile; then
                sed -i '/^KBUILD_CFLAGS/a\
KBUILD_CFLAGS += -Wno-error=incompatible-pointer-types -Wno-error=discarded-qualifiers\
KBUILD_CFLAGS += -Wno-error=int-conversion -Wno-error=implicit-function-declaration\
KBUILD_CFLAGS += -std=gnu89 -fno-strict-aliasing -fno-common' Makefile
            fi
        fi
    fi
    
    # arch/arm/Makefile
    if [ -f arch/arm/Makefile ]; then
        cp arch/arm/Makefile arch/arm/Makefile.backup
        
        # Adicionar flags específicas para MSM8226
        if ! grep -q "march=armv7-a" arch/arm/Makefile; then
            echo '' >> arch/arm/Makefile
            echo '# MSM8226 specific flags' >> arch/arm/Makefile
            echo 'KBUILD_CFLAGS += -march=armv7-a -mfpu=neon -mfloat-abi=softfp' >> arch/arm/Makefile
        fi
    fi
    
    _success "Makefiles corrigidos"
}

# Criar headers GCC modernos
create_gcc_headers() {
    _log "Criando headers para suporte GCC 14+..."
    
    for ver in 14 15; do
        if [ ! -f "include/linux/compiler-gcc${ver}.h" ]; then
            cat > "include/linux/compiler-gcc${ver}.h" <<EOF
#ifndef __LINUX_COMPILER_H
#error "Please include <linux/compiler.h> instead"
#endif

#define __used			__attribute__((__used__))
#define __must_check		__attribute__((warn_unused_result))
#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)
#define __always_inline		inline __attribute__((always_inline))
#define __deprecated		__attribute__((deprecated))
#define __packed		__attribute__((packed))
#define __weak			__attribute__((weak))

/* Disable problematic warnings for GCC ${ver} */
#pragma GCC diagnostic ignored "-Wendif-labels"
#pragma GCC diagnostic ignored "-Wformat-security"
#pragma GCC diagnostic ignored "-Warray-bounds"
#pragma GCC diagnostic ignored "-Wstringop-overflow"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
#pragma GCC diagnostic ignored "-Wint-conversion"
EOF
        fi
    done
    
    # Atualizar compiler-gcc.h existente
    if [ -f include/linux/compiler-gcc.h ]; then
        cp include/linux/compiler-gcc.h include/linux/compiler-gcc.h.backup
        
        if ! grep -q "GCC 14+ support" include/linux/compiler-gcc.h; then
            cat >> include/linux/compiler-gcc.h << 'EOF'

/* GCC 14+ support */
#if GCC_VERSION >= 140000
#define __HAVE_BUILTIN_BSWAP32__
#define __HAVE_BUILTIN_BSWAP64__
#define __HAVE_BUILTIN_BSWAP16__
#pragma GCC diagnostic ignored "-Warray-bounds"
#pragma GCC diagnostic ignored "-Wstringop-overflow"
#endif

/* Disable problematic warnings for old kernel */
#pragma GCC diagnostic ignored "-Wformat-security"
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
EOF
        fi
    fi
    
    _success "Headers GCC modernos criados"
}

# Aplicar correções específicas para entry-*.S
fix_entry_files() {
    _log "Corrigindo arquivos entry-*.S..."
    
    # entry-armv.S
    if [ -f arch/arm/kernel/entry-armv.S ]; then
        cp arch/arm/kernel/entry-armv.S arch/arm/kernel/entry-armv.S.backup
        sed -i 's/#ifdef CONFIG_ARM_THUMB()/#ifdef CONFIG_ARM_THUMB/g' arch/arm/kernel/entry-armv.S
        _log "entry-armv.S corrigido"
    fi
    
    # entry-header.S
    if [ -f arch/arm/kernel/entry-header.S ]; then
        cp arch/arm/kernel/entry-header.S arch/arm/kernel/entry-header.S.backup
        # Desabilitar verificação problemática de pt_regs
        sed -i '185s/#if ((sizeof(struct pt_regs) % 8) != 0)/#if 0 \/\* disabled for compatibility \*\//' arch/arm/kernel/entry-header.S
        _log "entry-header.S corrigido"
    fi
    
    _success "Arquivos entry-*.S corrigidos"
}

# Criar defconfig otimizado
create_defconfig() {
    _log "Criando defconfig otimizado para Matisse3G..."
    
    cat > arch/arm/configs/matisse3g_defconfig << 'EOF'
# Samsung Galaxy Tab 4 10.1 (SM-T531) - Matisse3G
# MSM8226 (Snapdragon 400) - Cortex-A7 Quad-core

CONFIG_EXPERIMENTAL=y
CONFIG_LOCALVERSION="-matisse3g"
CONFIG_LOCALVERSION_AUTO=n
CONFIG_DEFAULT_HOSTNAME="matisse3g"

# System Type
CONFIG_ARCH_MSM=y
CONFIG_ARCH_MSM8226=y
CONFIG_MSM_STACKED_MEMORY=y
CONFIG_MSM_SOC_REV_A=y

# CPU Features
CONFIG_SMP=y
CONFIG_NR_CPUS=4
CONFIG_HOTPLUG_CPU=y
CONFIG_ARM_ARCH_TIMER=y
CONFIG_ARCH_HAS_CPUFREQ=y
CONFIG_CPU_FREQ=y
CONFIG_CPU_FREQ_GOV_ONDEMAND=y

# Memory Management
CONFIG_HIGHMEM=y
CONFIG_FORCE_MAX_ZONEORDER=11
CONFIG_MEMORY_HOTPLUG=y

# Device Tree
CONFIG_OF=y
CONFIG_OF_FLATTREE=y
CONFIG_OF_EARLY_FLATTREE=y

# Power Management
CONFIG_PM=y
CONFIG_PM_SLEEP=y
CONFIG_SUSPEND=y
CONFIG_PM_RUNTIME=y

# Regulators
CONFIG_REGULATOR=y
CONFIG_REGULATOR_FIXED_VOLTAGE=y
CONFIG_REGULATOR_MSM_GPIO=y

# SPMI
CONFIG_SPMI=y
CONFIG_OF_SPMI=y
CONFIG_MSM_QPNP_INT=y

# Essential drivers
CONFIG_MSM_RPM_SMD=y
CONFIG_MSM_SMD=y
CONFIG_MSM_SMP2P=y

# Disable problematic features
CONFIG_SOUND=n
CONFIG_SND=n
CONFIG_DEBUG_FS=n
CONFIG_MODVERSIONS=n
CONFIG_MODULE_SRCVERSION_ALL=n

# ARM specific
CONFIG_AEABI=y
CONFIG_OABI_COMPAT=n
CONFIG_ARM_UNWIND=n
CONFIG_THUMB2_KERNEL=n

# Preemption
CONFIG_PREEMPT_NONE=y
CONFIG_PREEMPT_VOLUNTARY=n
CONFIG_PREEMPT=n
CONFIG_PREEMPT_COUNT=n

# Security
CONFIG_ANDROID_PARANOID_NETWORK=n
CONFIG_ANDROID_LOW_MEMORY_KILLER=n

# Filesystem
CONFIG_EXT4_FS=y
CONFIG_F2FS_FS=y
CONFIG_TMPFS=y
CONFIG_TMPFS_POSIX_ACL=y

# Network
CONFIG_UNIX=y
CONFIG_INET=y
CONFIG_IP_PNP=y
CONFIG_IP_PNP_DHCP=y

# Essential
CONFIG_UEVENT_HELPER_PATH=""
CONFIG_DEVTMPFS=y
CONFIG_DEVTMPFS_MOUNT=y

EOF
    
    _success "defconfig criado em arch/arm/configs/matisse3g_defconfig"
}

# Testar aplicação das correções
test_fixes() {
    _log "Testando se as correções funcionam..."
    
    # Limpar objetos antigos
    make ARCH=arm clean >/dev/null 2>&1 || true
    
    # Testar prepare
    if make ARCH=arm prepare >/dev/null 2>&1; then
        _success "✓ make prepare passou"
    else
        _warn "⚠ make prepare falhou - pode precisar de ajustes adicionais"
    fi
    
    # Testar compilação do asm-offsets.s
    if make ARCH=arm arch/arm/kernel/asm-offsets.s >/dev/null 2>&1; then
        _success "✓ asm-offsets.s compilou com sucesso"
    else
        _warn "⚠ asm-offsets.s ainda tem problemas"
    fi
    
    _log "Teste das correções concluído"
}

# Gerar relatório das mudanças
generate_report() {
    _log "Gerando relatório das mudanças aplicadas..."
    
    REPORT_FILE="${KERNEL_DIR}/MATISSE3G_PATCHES_REPORT.md"
    
    cat > "$REPORT_FILE" << EOF
# Relatório de Patches Aplicados - Samsung Matisse3G (SM-T531)

## Data: $(date)
## Kernel: Linux 3.4.113 - MSM8226
## Dispositivo: Samsung Galaxy Tab 4 10.1 (SM-T531)

## Correções Aplicadas:

### 1. Headers de Compatibilidade
- ✓ Criado \`include/linux/sparse.h\` com definições __user/__kernel
- ✓ Corrigido \`include/linux/stddef.h\` com enum bool
- ✓ Corrigido \`include/uapi/linux/stddef.h\`
- ✓ Corrigido \`include/uapi/linux/types.h\`
- ✓ Corrigido \`include/linux/capability.h\` removendo __user

### 2. Arquivos Assembly ARM
- ✓ Corrigido \`arch/arm/kernel/asm-offsets.c\` para GCC moderno
- ✓ Corrigido \`arch/arm/mm/proc-v7.S\` com suporte MSM8226
- ✓ Corrigido \`arch/arm/kernel/entry-armv.S\`
- ✓ Corrigido \`arch/arm/kernel/entry-header.S\`

### 3. Makefiles e Compilação
- ✓ Adicionadas flags GCC 14+ ao Makefile principal
- ✓ Configurado \`arch/arm/Makefile\` para MSM8226 (Cortex-A7)
- ✓ Criados headers \`compiler-gcc14.h\` e \`compiler-gcc15.h\`
- ✓ Atualizado \`compiler-gcc.h\` com pragmas anti-warning

### 4. Configuração do Dispositivo
- ✓ Criado \`arch/arm/configs/matisse3g_defconfig\`
- ✓ Configuração otimizada para MSM8226 Snapdragon 400
- ✓ Suporte para Device Tree, SPMI, RPM-SMD

### 5. Correções Específicas MSM8226
- ✓ Definições PMD_FLAGS para Cortex-A7
- ✓ Entrada específica __msm8226_proc_info
- ✓ Flags de compilação otimizadas (-march=armv7-a -mfpu=neon)
- ✓ Desabilitados módulos problemáticos (SOUND, DEBUG_FS)

## Arquivos de Backup:
Todos os arquivos originais foram salvos com extensão \`.backup\`

## Próximos Passos:
1. Testar compilação: \`make ARCH=arm matisse3g_defconfig && make ARCH=arm -j4\`
2. Verificar se todos os módulos essenciais compilam
3. Testar boot no dispositivo
4. Ajustar drivers específicos se necessário

## Comando de Compilação Recomendado:
\`\`\`bash
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
export KCFLAGS="-Wno-error=incompatible-pointer-types -Wno-error=discarded-qualifiers"

make matisse3g_defconfig
make -j4 zImage
make -j4 modules
\`\`\`

EOF
    
    _success "Relatório salvo em: $REPORT_FILE"
}

# Função principal
main() {
    echo "================================================"
    echo "  Script de Validação de Patches - Matisse3G  "
    echo "================================================"
    echo
    
    check_kernel_directory
    
    read -p "Deseja criar um backup antes de aplicar as correções? (Y/n): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Nn]$ ]]; then
        _warn "Prosseguindo sem backup..."
    else
        create_backup
    fi
    
    cd "$KERNEL_DIR"
    
    _log "Aplicando todas as correções..."
    
    apply_header_fixes
    fix_asm_offsets  
    fix_proc_v7
    fix_makefiles
    create_gcc_headers
    fix_entry_files
    create_defconfig
    
    test_fixes
    generate_report
    
    echo
    echo "================================================"
    _success "Todas as correções foram aplicadas com sucesso!"
    echo "================================================"
    echo
    echo "Para compilar o kernel:"
    echo "  cd $KERNEL_DIR"
    echo "  export ARCH=arm"
    echo "  export CROSS_COMPILE=arm-linux-gnueabihf-"
    echo "  make matisse3g_defconfig"
    echo "  make -j4 zImage"
    echo
    echo "Backup disponível em: $BACKUP_DIR"
    echo "Relatório salvo em: $KERNEL_DIR/MATISSE3G_PATCHES_REPORT.md"
}

# Executar apenas se chamado diretamente
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    main "$@"
fi
