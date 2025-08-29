#!/bin/bash
# Script para restaurar arquivos originais

echo "Restaurando arquivos originais..."

if [ -d ".backup_kernel_fixes" ]; then
    for backup in .backup_kernel_fixes/*.bak; do
        if [ -f "$backup" ]; then
            original=$(basename "$backup" .bak)
            # Tentar encontrar o arquivo original
            find . -name "$original" -type f | head -1 | while read orig_path; do
                echo "Restaurando: $orig_path"
                cp "$backup" "$orig_path"
            done
        fi
    done
    echo "Restauração concluída!"
else
    echo "Nenhum backup encontrado!"
fi
