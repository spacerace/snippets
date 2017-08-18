#!/bin/bash


IMAGES=$@
echo "extracting images: $IMAGES"

for i in $IMAGES
do
	echo "processing image \"$i\" ..."
	mkdir tmp
	mkdir "$i-extracted"
	sudo mount -o loop "$i" tmp
	cp tmp/* "$i-extracted" -rfv
	sudo umount tmp
	rmdir tmp
done
