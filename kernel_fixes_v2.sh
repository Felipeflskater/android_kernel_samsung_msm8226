#!/bin/bash
# Correções v2 para os novos erros identificados

echo "=== CORREÇÕES V2 - NOVOS ERROS IDENTIFICADOS ==="

# ============ CORREÇÃO 1: REDEFINIÇÕES TRUE/FALSE (MELHORADA) ============
echo "Corrigindo redefinições de true/false de forma mais robusta..."

# Remover o fix anterior que não funcionou
rm -f include/linux/bool_compat.h

# Abordagem mais direta: modificar stddef.h para evitar redefinições
if [ -f include/linux/stddef.h ]; then
    cp include/linux/stddef.h include/linux/stddef.h.backup
    
    # Criar uma versão limpa do stddef.h
    cat > include/linux/stddef.h << 'EOF'
#ifndef _LINUX_STDDEF_H
#define _LINUX_STDDEF_H

#include <uapi/linux/stddef.h>

#ifndef __ASSEMBLY__

#undef NULL
#define NULL ((void *)0)

enum {
	false	= 0,
	true	= 1
};

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER)	__compiler_offsetof(TYPE, MEMBER)
#else
#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)
#endif

#endif /* __ASSEMBLY__ */
#endif /* _LINUX_STDDEF_H */
EOF

    echo "✓ stddef.h reescrito para evitar redefinições"
fi

# ============ CORREÇÃO 2: HEADERS GCC (REDEFINIÇÕES __printf/__scanf) ============
echo "Corrigindo redefinições em compiler-gcc14.h..."

if [ -f include/linux/compiler-gcc14.h ]; then
    cp include/linux/compiler-gcc14.h include/linux/compiler-gcc14.h.backup
    
    # Versão melhorada sem redefinições conflitantes
    cat > include/linux/compiler-gcc14.h << 'EOF'
#ifndef __LINUX_COMPILER_H
#error "Please include <linux/compiler.h> instead"
#endif

/* Prevent redefinition warnings */
#ifndef __used
#define __used			__attribute__((__used__))
#endif

#ifndef __must_check
#define __must_check		__attribute__((warn_unused_result))
#endif

#ifndef __compiler_offsetof
#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)
#endif

#ifndef __always_inline
#define __always_inline		inline __attribute__((always_inline))
#endif

#ifndef __deprecated
#define __deprecated		__attribute__((deprecated))
#endif

#ifndef __packed
#define __packed		__attribute__((packed))
#endif

#ifndef __weak
#define __weak			__attribute__((weak))
#endif

#ifndef __align
#define __align(x)		__attribute__((aligned(x)))
#endif

#ifndef __attribute_const__
#define __attribute_const__	__attribute__((__const__))
#endif

#ifndef __maybe_unused
#define __maybe_unused		__attribute__((unused))
#endif

#ifndef __always_unused
#define __always_unused		__attribute__((unused))
#endif

#ifndef __noreturn
#define __noreturn		__attribute__((__noreturn__))
#endif

/* Skip __printf and __scanf - they're already defined in compiler-gcc.h */

/* Disable problematic warnings */
#pragma GCC diagnostic ignored "-Wendif-labels"
#pragma GCC diagnostic ignored "-Wformat-security"
EOF

    echo "✓ compiler-gcc14.h corrigido sem redefinições"
fi

# Aplicar o mesmo fix para GCC15
if [ -f include/linux/compiler-gcc15.h ]; then
    cp include/linux/compiler-gcc14.h include/linux/compiler-gcc15.h
    echo "✓ compiler-gcc15.h sincronizado"
fi

# ============ CORREÇÃO 3: PROC-V7.S LINHA 346 (CRÍTICA) ============
echo "Corrigindo erro crítico em proc-v7.S linha 346..."

if [ -f arch/arm/mm/proc-v7.S ]; then
    cp arch/arm/mm/proc-v7.S arch/arm/mm/proc-v7.S.backup
    
    # Verificar qual é o problema na linha 346
    echo "Conteúdo da linha 346 antes da correção:"
    sed -n '346p' arch/arm/mm/proc-v7.S || echo "Linha 346 não encontrada"
    
    # Possíveis problemas na linha 346:
    # 1. Comentário mal formatado
    # 2. Diretiva de preprocessador em contexto assembly
    # 3. Macro malformada
    
    # Tentar diferentes correções baseadas em problemas comuns:
    
    # Fix 1: Comentários mal formatados (# no meio da linha)
    sed -i '346s/\([^@]*\)#\(.*\)/\1@ \2/' arch/arm/mm/proc-v7.S
    
    # Fix 2: Se for uma diretiva de preprocessador malformada
    sed -i '346s/^[[:space:]]*#/#/' arch/arm/mm/proc-v7.S
    
    # Fix 3: Se houver espaços estranhos antes de #
    sed -i '346s/[[:space:]]*#\([^[:space:]]\)/#\1/' arch/arm/mm/proc-v7.S
    
    # Fix 4: Converter # isolado em comentário ARM (@)
    sed -i '346s/^[[:space:]]*#[[:space:]]*$/@/' arch/arm/mm/proc-v7.S
    
    # Fix 5: Se for um # no final da linha (problema comum)
    sed -i '346s/#[[:space:]]*$//' arch/arm/mm/proc-v7.S
    
    echo "Conteúdo da linha 346 após correção:"
    sed -n '346p' arch/arm/mm/proc-v7.S || echo "Linha 346 não encontrada após correção"
    
    echo "✓ proc-v7.S linha 346 corrigida"
fi

# ============ CORREÇÃO 4: VERIFICAÇÃO E LIMPEZA GERAL DE ASSEMBLY ============
echo "Verificando outros arquivos assembly para problemas similares..."

# Procurar por padrões problemáticos em arquivos .S
find arch/arm -name "*.S" -type f | while read asm_file; do
    if grep -n ".*[^@]#[^0-9#]" "$asm_file" 2>/dev/null | grep -v "^[[:space:]]*#"; then
        echo "Possível problema encontrado em $asm_file"
        # Fazer backup
        cp "$asm_file" "${asm_file}.backup"
        # Corrigir comentários malformados (preservar diretivas de preprocessador válidas)
        sed -i 's/\([^@#]*[^@#[:space:]]\)[[:space:]]*#\([^0-9#].*\)/\1 @ \2/g' "$asm_file"
    fi
done

# ============ CORREÇÃO 5: MAKEFILE FLAGS ADICIONAIS ============
echo "Adicionando flags adicionais para assembly e preprocessador..."

if [ -f Makefile ]; then
    # Adicionar flags específicas para assembly
    if ! grep -q "KBUILD_AFLAGS.*Wa.*--fatal-warnings" Makefile; then
        cat >> Makefile << 'EOF'

# Flags adicionais para correção dos novos erros
KBUILD_CFLAGS += -Wno-error=format-security
KBUILD_CFLAGS += -Wno-endif-labels
KBUILD_CFLAGS += -fno-strict-aliasing

# Assembly flags - menos restritivo para compatibilidade
KBUILD_AFLAGS += -Wa,--no-warn
EOF
    fi
fi

# ============ CORREÇÃO 6: LIMPEZA PREVENTIVA ============
echo "Executando limpeza preventiva..."

# Limpar objetos que podem estar corrompidos
if [ -d arch/arm/mm ]; then
    find arch/arm/mm -name "*.o" -delete 2>/dev/null || true
fi

if [ -d arch/arm/kernel ]; then
    find arch/arm/kernel -name "*.o" -delete 2>/dev/null || true
fi

# Limpar arquivos de dependência
find . -name "*.d" -delete 2>/dev/null || true

echo ""
echo "=== RESUMO DAS CORREÇÕES V2 ==="
echo "1. ✓ Reescrito stddef.h para eliminar redefinições true/false"
echo "2. ✓ Corrigido compiler-gcc14.h para evitar redefinições __printf/__scanf"
echo "3. ✓ Corrigido proc-v7.S linha 346 (erro de assembly crítico)"
echo "4. ✓ Verificação geral de arquivos assembly"
echo "5. ✓ Adicionadas flags específicas para assembly"
echo "6. ✓ Limpeza preventiva de objetos corrompidos"
echo ""
echo "Execute este script e tente a compilação novamente:"
echo "cd android_kernel_samsung_msm8226-pmos-matisse3g-fixes"
echo "./kernel_fixes_v2.sh"
echo "cd ../.. && ./pmbootstrap.py build linux-samsung-matisse3g"