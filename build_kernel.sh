#!/bin/bash
export HOSTCFLAGS="-O2 -fno-PIE"
export HOSTLDFLAGS="-no-pie"
export ARCH="arm"
export CROSS_COMPILE="arm-linux-gnueabi-"

if ! command -v "${CROSS_COMPILE}gcc" >/dev/null 2>&1; then
    echo "ERRO: Cross-compiler não encontrado: ${CROSS_COMPILE}gcc"
    echo "Instale com: sudo apt install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi"
    exit 1
fi

echo "Compilando kernel com ${CROSS_COMPILE}gcc..."
make -j$(nproc) $@
