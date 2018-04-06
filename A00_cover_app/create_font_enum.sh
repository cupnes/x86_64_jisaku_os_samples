#!/bin/bash

SRC_DIR=~/x86_64_poios/materials/cover_font/64x64

echo 'enum FONT_IDX {'
for s in $(ls ${SRC_DIR}); do
	echo -e "\tfont_$(echo $s | rev | cut -d'.' -f2- | rev)",
done
echo '};'
