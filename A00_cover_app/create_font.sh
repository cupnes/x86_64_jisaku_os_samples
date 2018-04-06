#!/bin/bash

WIDTH=64

src=$1

pbm=$(convert $src -compress none pbm:- | grep -v '^#' | tail -n +3 | tr -d '\n')
size=$(echo -n $pbm | wc -c)

echo -e '\t{'
while [ $size -gt 0 ]; do
	echo -ne '\t\t{'
	echo -n $pbm | head -c $((WIDTH * 2 - 1)) | tr ' ' ','
	size=$((size - (WIDTH * 2)))
	pbm=$(echo -n $pbm | tail -c $size)
	echo '},'
done
echo -e '\t},'
