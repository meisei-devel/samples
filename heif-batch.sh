#!/bin/sh

FILES="*.HEIC"

if [ ! -d "JPEG" ]; then
 mkdir JPEG
fi

for FILE in $FILES; do
 heif-convert $FILE JPEG/$FILE.jpg
done
