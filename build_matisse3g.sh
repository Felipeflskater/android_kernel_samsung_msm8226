#!/bin/bash
# Script de build para Samsung Matisse 3G com GCC 14

set -e

export HOSTCFLAGS="-O2 -fno-PIE -Wno-error"
export HOSTLDFLAGS="-no-pie"
export ARCH="arm"
export CROSS_COMPILE="arm-linux-gnueabi-"

# Flags de compatibilidade para GCC 14 com kernel 3.4.113
export KCFLAGS="-Wno-error=dangling-pointer -Wno-error=array-bounds -Wno-error=stringop-overflow -Wno-error=format-overflow -Wno-error=incompatible-pointer-types -Wno-error=discarded-qualifiers -Wno-error=int-conversion -Wno-error=implicit-function-declaration -Wno-error=format-security -fgnu89-inline -std=gnu89"

echo "Compilando kernel Samsung Matisse 3G..."
echo "Cross-compiler: $CROSS_COMPILE"
echo "Flags: $KCFLAGS"
echo

make KCFLAGS="$KCFLAGS" -j$(nproc) $@

echo
echo "Build concluído! Arquivos gerados:"
echo "  Kernel: arch/arm/boot/zImage"
echo "  Módulos: (se compilados)"
