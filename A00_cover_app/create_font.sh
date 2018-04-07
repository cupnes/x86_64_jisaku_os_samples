#!/bin/bash

if [ $# -lt 4 ]; then
	echo "Usage: $0 SOURCE_DIR DEST_DIR WIDTH HIGHT" > /dev/stderr
	exit 1
fi

SRC_DIR=$1
DST_DIR=$2
WIDTH=$3
HEIGHT=$4

img2font()
{
	src=$1

	pbm=$(convert $src -resize ${WIDTH}x${HEIGHT}! -strip \
		      -compress none pbm:- | grep -v '^#' | tail -n +3 \
			     | tr -d '\n')
	size=$(echo -n $pbm | wc -c)


	while [ $size -gt 0 ]; do
		echo -ne '\t\t{'
		echo -n $pbm | head -c $((WIDTH * 2 - 1)) | tr ' ' ','
		size=$((size - (WIDTH * 2)))
		pbm=$(echo -n $pbm | tail -c $size)
		echo -e '},'
	done
}

create_space_char()
{
	echo -e "\t[FONT_space] = {\t/* 0: space */"
	for y in $(seq ${HEIGHT}); do
		echo -en '\t\t{'
		for x in $(seq ${WIDTH}); do
			echo -n '0'
			[ $x != ${WIDTH} ] && echo -n ','
		done
		echo '},'
	done
	echo -e '\t},'
}

create_font_h()
{
	cat >${DST_DIR}/font.h <<EOF
#ifndef _FONT_H_
#define _FONT_H_

#define FONT_WIDTH	${WIDTH}
#define FONT_HEIGHT	${HEIGHT}

enum FONT_IDX {
	FONT_space,
EOF
	for s in $(ls ${SRC_DIR}); do
		echo -e "\tFONT_$(echo $s | rev | cut -d'.' -f2- | rev),"
	done >>${DST_DIR}/font.h
	cat >>${DST_DIR}/font.h <<EOF
};

extern const unsigned char font_bitmap[][FONT_HEIGHT][FONT_WIDTH];

#endif
EOF
}

create_font_c()
{
	echo '#include <font.h>' >${DST_DIR}/font.c
	echo >>${DST_DIR}/font.c
	echo 'const unsigned char font_bitmap[][FONT_HEIGHT][FONT_WIDTH] = {' \
	     >>${DST_DIR}/font.c
	idx=1
	create_space_char >>${DST_DIR}/font.c
	for s in $(ls ${SRC_DIR}); do
		name=$(echo $s | rev | cut -d'.' -f2- | rev)
		echo -e "\t[FONT_$name] = {\t/* $idx: $name */"
		img2font ${SRC_DIR}/$s
		echo -e '\t},'
		idx=$((idx + 1))
	done >>${DST_DIR}/font.c
	echo '};' >>${DST_DIR}/font.c
}

# main
mkdir -p ${DST_DIR}
create_font_h
create_font_c
