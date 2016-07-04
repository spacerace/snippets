#!/bin/bash


DST=$1

echo "gentoo chroot dst=$DST"

mount -o bind /dev $DST/dev
mount -t proc none $DST/proc
mount -t sysfs none $DST/sys
cp -L /etc/resolv.conf $DST/etc/
chroot $DST
