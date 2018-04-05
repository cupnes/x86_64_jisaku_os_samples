#!/bin/bash

WIDTH=64

src=$1

pbm=$(convert $src -compress none pbm:- | grep -v '^#' | tail -n +3 | tr -d '\n')
size=$(echo -n $pbm | wc -c)

while [ $size -gt 0 ]; do
        echo -n $pbm | head -c $((WIDTH * 2))
        size=$((size - (WIDTH * 2)))
        pbm=$(echo -n $pbm | tail -c $size)
        echo
done
