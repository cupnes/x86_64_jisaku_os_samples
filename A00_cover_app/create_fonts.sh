#!/bin/bash

WIDTH=64
HEIGHT=64
CREATE_FONT=~/x86_64_jisaku_os_samples/A00_cover_app/create_font.sh

idx=0
for s in $(ls ${WIDTH}x${HEIGHT}); do
	echo -e "\t{\t/* $idx: $(echo $s | rev | cut -d'.' -f2- | rev) */"
	${CREATE_FONT} ${WIDTH}x${HEIGHT}/$s
	echo -e '\t},'
	idx=$((idx + 1))
done
