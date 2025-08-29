#!/bin/bash
# Script de compilação com flags otimizadas para Matisse 3G

export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-

# Flags para suprimir warnings específicos
export KCFLAGS="-Wno-format -Wno-macro-redefined -Wno-unused-function"
export KAFLAGS="-Wa,--noexecstack"

echo "Iniciando compilação com flags otimizadas..."
echo "ARCH: $ARCH"
echo "CROSS_COMPILE: $CROSS_COMPILE"
echo "KCFLAGS: $KCFLAGS"

# Limpar compilação anterior
make clean

# Compilar com paralelismo
make -j$(nproc) 2>&1 | tee compilation.log

echo "Compilação finalizada. Log salvo em compilation.log"
