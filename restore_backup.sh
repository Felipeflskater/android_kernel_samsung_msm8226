#!/bin/bash
echo "Restaurando arquivos originais..."

if [ -d ".backup_fixes" ]; then
    [ -f ".backup_fixes/erase.c.backup" ] && cp .backup_fixes/erase.c.backup fs/jffs2/erase.c
    [ -f ".backup_fixes/Makefile.backup" ] && cp .backup_fixes/Makefile.backup Makefile
    [ -f ".backup_fixes/Makefile.exfat.backup" ] && cp .backup_fixes/Makefile.exfat.backup fs/exfat/Makefile
    echo "Arquivos restaurados!"
else
    echo "Nenhum backup encontrado!"
fi
