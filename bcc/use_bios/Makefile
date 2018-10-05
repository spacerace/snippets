all:
	/usr/lib64/bcc/bcc-cpp bioslib.c -o tmp-cpp -A -D__MSDOS__ -D__STDC__ -I. -D__HAS_NO_FLOATS__ -D__BCC_VERSION__=0x001015L -O -0
	/usr/lib64/bcc/unproto tmp-cpp tmp-unproto
	/usr/lib64/bcc/bcc-cc1 tmp-unproto -o tmp-cc1 -O -0
	/usr/lib64/bcc/copt tmp-cc1 -o tmp-copt -c! -d/usr/lib64/bcc rules.start rules.86 rules.end
	/usr/bin/as86 tmp-copt -o tmp-as86 -u -O -w- -0 -n bioslib.s
	/usr/bin/ld86 -o bioslib.com -y -d -T100 -0 tmp-as86
	rm -rf tmp-cpp tmp-unproto tmp-cc1 tmp-copt tmp-as86
	ls -al bioslib.com

clean:
	rm -rf bioslib.com

dosbox:
	dosbox

qemu:
	qemu-system-i386 -m 4 -fda floppy.img -net none -boot a -serial stdio

copy_to_floppy: all
	sudo mount -o loop floppy.img loop
	sudo cp bioslib.com loop/STARTUP.BIN
	sudo umount loop

