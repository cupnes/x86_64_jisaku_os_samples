#!/bin/bash

SRC_DIR=~/x86_64_poios/materials/cover_font/64x64
DST_DIR=out

WIDTH=64
HEIGHT=64
CREATE_FONT=./create_font.sh

mkdir -p ${DST_DIR}

# font.h
cat >${DST_DIR}/font.h <<EOF
#ifndef _FONT_H_
#define _FONT_H_

#define FONT_WIDTH	${WIDTH}
#define FONT_HEIGHT	${HEIGHT}

enum FONT_IDX {
EOF
for s in $(ls ${SRC_DIR}); do
	echo -e "\tFONT_$(echo $s | rev | cut -d'.' -f2- | rev),"
done >>${DST_DIR}/font.h
cat >>${DST_DIR}/font.h <<EOF
};

extern const unsigned char font_bitmap[][FONT_HEIGHT][FONT_WIDTH];

#endif
EOF

# font.c
echo '#include <font.h>' >${DST_DIR}/font.c
echo >>${DST_DIR}/font.c
echo 'const unsigned char font_bitmap[][FONT_HEIGHT][FONT_WIDTH] = {' >>${DST_DIR}/font.c
idx=0
for s in $(ls ${SRC_DIR}); do
	name=$(echo $s | rev | cut -d'.' -f2- | rev)
	echo -e "\t[FONT_$name] = {\t/* $idx: $name */"
	${CREATE_FONT} ${SRC_DIR}/$s
	echo -e '\t},'
	idx=$((idx + 1))
done >>${DST_DIR}/font.c
echo '};' >>${DST_DIR}/font.c
