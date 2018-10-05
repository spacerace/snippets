all:
	nasm -f bin -o rom.bin option_rom.asm
	ls -al rom.bin
	python signrom.py rom.bin rom.bin.signed
	
	
test:
	qemu-system-i386 -m 4 -net none -option-rom rom.bin.signed
