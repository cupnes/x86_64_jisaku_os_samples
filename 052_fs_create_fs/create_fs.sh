#!/bin/bash

FILE_NAME_LEN=28
FS_IMG_NAME='fs.img'

while [ -n "$1" ]; do
	# ヘッダ作成
	## ファイル名を出力
	name=$(basename $1)
	echo -ne "$name\0"
	dd if=/dev/zero count=$((${FILE_NAME_LEN} - ${#name} - 1)) bs=1 \
	   status=none

	## ファイルサイズを出力
	### ファイルサイズを16進8桁へ変換
	size=$(stat -c '%s' $1)
	size_hex=$(printf "%08X" $size)
	### リトルエンディアンへ変換
	size_hex_le=''
	for b in $(echo $size_hex | fold -w2 -b); do
		size_hex_le="$b$size_hex_le"
	done
	### 8ビットずつ出力
	for b in $(echo $size_hex_le | fold -w2 -b); do
		printf '%b' "\x$b"
	done

	# データ出力
	dd if=$1 status=none

	# 位置変数をシフト
	shift
done > ${FS_IMG_NAME}	# whileループ内の出力はfs.imgへ出力

# ファイルシステムの終わり(0x00)をfs.imgへ追記
echo -ne "\x00" >> ${FS_IMG_NAME}
