#!/bin/bash
# Script de compilação otimizado para Matisse 3G com correções específicas

export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-

# Flags específicas para resolver os problemas identificados
export KCFLAGS="-Wno-format -Wno-format-security -Wno-macro-redefined -Wno-unused-function -Wno-format-extra-args"
export KAFLAGS="-Wa,--noexecstack"

# Definir explicitamente para evitar conflitos
export CPPFLAGS="-D__LINUX_ARM_ARCH__=7"

echo "=== Compilação Otimizada para Matisse 3G ==="
echo "ARCH: $ARCH"
echo "CROSS_COMPILE: $CROSS_COMPILE" 
echo "KCFLAGS: $KCFLAGS"
echo "CPPFLAGS: $CPPFLAGS"
echo ""

# Verificar se o cross-compiler existe
if ! command -v ${CROSS_COMPILE}gcc &> /dev/null; then
    echo "ERRO: Cross-compiler ${CROSS_COMPILE}gcc não encontrado!"
    echo "Instale com: sudo apt install gcc-arm-linux-gnueabihf"
    exit 1
fi

echo "Cross-compiler encontrado: $(${CROSS_COMPILE}gcc --version | head -1)"
echo ""

# Limpar compilação anterior
echo "Limpando compilação anterior..."
make clean

# Verificar configuração
if [ ! -f ".config" ]; then
    echo "AVISO: Arquivo .config não encontrado!"
    echo "Execute 'make menuconfig' ou copie uma configuração antes de compilar"
    read -p "Continuar mesmo assim? (y/N): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit 1
    fi
fi

echo "Iniciando compilação..."
echo "Logs sendo salvos em compilation.log"
echo ""

# Compilar com paralelismo, salvando log detalhado
make -j$(nproc) V=1 2>&1 | tee compilation.log

# Verificar resultado
if [ $? -eq 0 ]; then
    echo ""
    echo "✅ COMPILAÇÃO CONCLUÍDA COM SUCESSO!"
    echo "Arquivos gerados:"
    [ -f "arch/arm/boot/zImage" ] && echo "  - zImage: arch/arm/boot/zImage"
    [ -f "arch/arm/boot/dts/"*.dtb ] && echo "  - DTB files: arch/arm/boot/dts/*.dtb"
    echo "  - Log completo: compilation.log"
else
    echo ""
    echo "❌ ERRO NA COMPILAÇÃO"
    echo "Verifique o arquivo compilation.log para detalhes"
    echo "Últimas linhas do erro:"
    tail -20 compilation.log
    exit 1
fi
