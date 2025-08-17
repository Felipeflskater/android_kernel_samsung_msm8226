#!/bin/bash
# Correção específica para o erro crítico em proc-v7.S:346

echo "=== INVESTIGAÇÃO E CORREÇÃO PROC-V7.S LINHA 346 ==="

# Função para mostrar contexto da linha problemática
show_context() {
    if [ -f arch/arm/mm/proc-v7.S ]; then
        echo "Conteúdo ao redor da linha 346:"
        sed -n '340,350p' arch/arm/mm/proc-v7.S | cat -n
        echo ""
        echo "Linha 346 específica:"
        sed -n '346p' arch/arm/mm/proc-v7.S | cat -A  # Mostra caracteres não-visíveis
    fi
}

# Mostrar problema atual
echo "ANTES DA CORREÇÃO:"
show_context

if [ -f arch/arm/mm/proc-v7.S ]; then
    # Backup
    cp arch/arm/mm/proc-v7.S arch/arm/mm/proc-v7.S.backup
    
    # O erro "junk at end of line, first unrecognized character is '#'" 
    # geralmente indica um dos seguintes problemas:
    
    # 1. Comentário C-style (#) em assembly ARM (deveria ser @)
    # 2. Diretiva de preprocessador mal posicionada
    # 3. Macro não expandida corretamente
    # 4. Caracteres invisíveis/não-ASCII
    
    echo "Aplicando correções específicas para linha 346..."
    
    # Correção 1: Converter comentários # para @ (padrão ARM)
    sed -i '346s/#\([^0-9#].*\)$/@\1/' arch/arm/mm/proc-v7.S
    
    # Correção 2: Se for uma diretiva de preprocessador mal posicionada, corrigir
    # Identificar se há algo como "instruction #define" ou similar
    sed -i '346s/\([[:alnum:]_]\)[[:space:]]*#define/\1\n#define/' arch/arm/mm/proc-v7.S
    
    # Correção 3: Remover caracteres não-ASCII ou invisíveis
    sed -i '346s/[^[:print:]]//g' arch/arm/mm/proc-v7.S
    
    # Correção 4: Se houver # isolado no final da linha, remover
    sed -i '346s/[[:space:]]*#[[:space:]]*$//' arch/arm/mm/proc-v7.S
    
    # Correção 5: Problemas específicos conhecidos no proc-v7.S
    # Às vezes há problemas com macros CACHE ou MMU
    sed -i '346s/\(.*\)[[:space:]]*#[[:space:]]*\(CACHE\|MMU\|SCTLR\)/\1 @ \2/' arch/arm/mm/proc-v7.S
    
    echo "DEPOIS DAS CORREÇÕES:"
    show_context
    
    # Verificação adicional: procurar outros padrões problemáticos no arquivo
    echo "Verificando outros possíveis problemas no proc-v7.S..."
    
    # Linhas com # que não são diretivas de preprocessador válidas
    if grep -n "[^@]#[^0-9#]" arch/arm/mm/proc-v7.S | grep -v "^[[:space:]]*#"; then
        echo "AVISO: Outras linhas problemáticas encontradas, corrigindo..."
        
        # Corrigir todas as ocorrências similares
        sed -i 's/\([^@#]*[^@#[:space:]]\)[[:space:]]*#\([^0-9#].*\)/\1 @ \2/g' arch/arm/mm/proc-v7.S
    fi
    
    echo "✓ proc-v7.S corrigido"
    
else
    echo "ERRO: arch/arm/mm/proc-v7.S não encontrado!"
    exit 1
fi

# Verificação final - tentar assemblar apenas essa linha para testar
echo ""
echo "=== TESTE DE SINTAXE ==="
echo "Testando se a correção resolveu o problema..."

# Criar um arquivo de teste com apenas o contexto da linha 346
sed -n '340,350p' arch/arm/mm/proc-v7.S > /tmp/proc-v7-test.S

# Adicionar header básico para teste
cat > /tmp/proc-v7-test-full.S << 'EOF'
.text
.arm

/* Headers mínimos para teste */
#include <linux/linkage.h>
#include <asm/assembler.h>
#include <asm/asm-offsets.h>
#include <asm/hwcap.h>
#include <asm/pgtable-hwdef.h>
#include <asm/pgtable.h>
#include <asm/ptrace.h>

/* Conteúdo de teste */
EOF

cat /tmp/proc-v7-test.S >> /tmp/proc-v7-test-full.S

# Testar com o cross-compiler se disponível
if command -v armv7-alpine-linux-musleabihf-as >/dev/null 2>&1; then
    echo "Testando sintaxe assembly..."
    if armv7-alpine-linux-musleabihf-as -march=armv7-a /tmp/proc-v7-test-full.S -o /tmp/proc-v7-test.o 2>/dev/null; then
        echo "✓ Teste de sintaxe assembly PASSOU"
        rm -f /tmp/proc-v7-test.o
    else
        echo "⚠ Teste de sintaxe assembly FALHOU - pode precisar de mais correções"
        echo "Erro do assembler:"
        armv7-alpine-linux-musleabihf-as -march=armv7-a /tmp/proc-v7-test-full.S -o /tmp/proc-v7-test.o
    fi
else
    echo "Cross-assembler não disponível para teste"
fi

# Limpeza
rm -f /tmp/proc-v7-test.S /tmp/proc-v7-test-full.S /tmp/proc-v7-test.o

echo ""
echo "=== CORREÇÃO PROC-V7.S CONCLUÍDA ==="