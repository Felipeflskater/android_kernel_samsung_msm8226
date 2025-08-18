#!/bin/bash
echo "Testando compilação do kernel PostmarketOS..."
echo "Configuração: $1"

DEFCONFIG=${1:-msm8226_defconfig}

echo "Limpando build anterior..."
make mrproper

echo "Aplicando defconfig: $DEFCONFIG"
make ARCH=arm $DEFCONFIG

echo "Iniciando compilação de teste (apenas alguns arquivos)..."
make ARCH=arm CROSS_COMPILE=armv7-alpine-linux-musleabihf- -j$(nproc) arch/arm/kernel/entry-armv.o kernel/panic.o arch/arm/mach-msm/timer.o

if [ $? -eq 0 ]; then
    echo "✅ Compilação de teste PASSOU! Os patches funcionaram."
else
    echo "❌ Compilação de teste FALHOU. Verifique os erros acima."
fi
