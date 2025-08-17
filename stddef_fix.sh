#!/bin/bash
# Correção específica para o erro de stddef.h

echo "=== CORREÇÃO CRÍTICA: stddef.h para kernel 3.4.x ==="

# O erro indica que tentamos incluir uapi/linux/stddef.h que não existe em kernel 3.4.x
# Vamos criar uma versão compatível

# 1. Primeiro, verificar se o diretório uapi existe
echo "Verificando estrutura uapi..."
if [ ! -d include/uapi ]; then
    echo "Criando estrutura uapi..."
    mkdir -p include/uapi/linux
    mkdir -p include/uapi/asm
fi

# 2. Criar uapi/linux/stddef.h que está faltando
echo "Criando uapi/linux/stddef.h..."
cat > include/uapi/linux/stddef.h << 'EOF'
#ifndef _UAPI_LINUX_STDDEF_H
#define _UAPI_LINUX_STDDEF_H

#ifndef __ASSEMBLY__

#ifdef __KERNEL__
/* Kernel space definitions */
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#else
/* User space definitions */
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#endif /* __KERNEL__ */

#endif /* __ASSEMBLY__ */

#endif /* _UAPI_LINUX_STDDEF_H */
EOF

# 3. Corrigir include/linux/stddef.h para ser compatível com kernel 3.4.x
echo "Corrigindo include/linux/stddef.h para compatibilidade kernel 3.4.x..."

if [ -f include/linux/stddef.h ]; then
    cp include/linux/stddef.h include/linux/stddef.h.backup
    
    cat > include/linux/stddef.h << 'EOF'
#ifndef _LINUX_STDDEF_H
#define _LINUX_STDDEF_H

#include <uapi/linux/stddef.h>

#ifndef __ASSEMBLY__

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

    echo "✓ stddef.h corrigido para kernel 3.4.x"
else
    echo "ERRO: include/linux/stddef.h não encontrado!"
    exit 1
fi

# 4. Verificar e corrigir outros arquivos uapi que podem estar faltando
echo "Verificando outros arquivos uapi essenciais..."

# Criar uapi/linux/types.h se não existir
if [ ! -f include/uapi/linux/types.h ]; then
    echo "Criando uapi/linux/types.h..."
    cat > include/uapi/linux/types.h << 'EOF'
#ifndef _UAPI_LINUX_TYPES_H
#define _UAPI_LINUX_TYPES_H

#include <asm/types.h>

#ifndef __ASSEMBLY__

#ifndef __KERNEL__
#warning "Userspace API header used in kernel space"
#endif

typedef __u16 __le16;
typedef __u16 __be16;
typedef __u32 __le32;
typedef __u32 __be32;
typedef __u64 __le64;
typedef __u64 __be64;

typedef __u16 __sum16;
typedef __u32 __wsum;

#endif /* __ASSEMBLY__ */
#endif /* _UAPI_LINUX_TYPES_H */
EOF
fi

# 5. Verificar se asm/types.h existe
if [ ! -f include/uapi/asm/types.h ]; then
    echo "Criando link simbólico para uapi/asm/types.h..."
    if [ -f arch/arm/include/asm/types.h ]; then
        ln -sf ../../../arch/arm/include/asm/types.h include/uapi/asm/types.h
    elif [ -f include/asm-generic/types.h ]; then
        ln -sf ../../asm-generic/types.h include/uapi/asm/types.h
    fi
fi

# 6. Teste rápido - verificar se os arquivos estão acessíveis
echo "Testando acessibilidade dos arquivos criados..."
if [ -f include/uapi/linux/stddef.h ] && [ -f include/linux/stddef.h ]; then
    echo "✓ Arquivos stddef.h criados e acessíveis"
    
    # Mostrar conteúdo para debug
    echo "Conteúdo de include/linux/stddef.h:"
    cat include/linux/stddef.h
    echo ""
    echo "Conteúdo de include/uapi/linux/stddef.h:"
    cat include/uapi/linux/stddef.h
else
    echo "ERRO: Arquivos não foram criados corretamente"
    exit 1
fi

# 7. Limpar cache de build que pode estar corrompido
echo "Limpando cache de build..."
find . -name "*.o" -delete 2>/dev/null || true
find . -name "*.s" -delete 2>/dev/null || true
find . -name ".*.o.cmd" -delete 2>/dev/null || true
rm -f include/linux/version.h include/generated/utsrelease.h 2>/dev/null || true

echo ""
echo "=== CORREÇÃO stddef.h CONCLUÍDA ==="
echo "✓ uapi/linux/stddef.h criado"
echo "✓ include/linux/stddef.h corrigido"
echo "✓ Cache de build limpo"
echo ""
echo "Execute novamente: ./pmbootstrap.py build linux-samsung-matisse3g"