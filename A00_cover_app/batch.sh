#!/bin/bash

WIDTH=64
HEIGHT=64

for s in $(ls raw); do
	convert raw/$s -resize ${WIDTH}x${HEIGHT}! -strip ${WIDTH}x${HEIGHT}/$s
done
