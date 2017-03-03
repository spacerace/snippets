This folder contains code to print a string via BIOS without use of DOS


List of files:
BUILDALL.BAT - build it on DOS
Makefile - build it on linux
b_prnstr.asm - source code to print a string
bioschar.asm - source code to print a character

bioschar.com - executable made by nasm for dos
b_prnstr.com - executable made by nasm for dos
b_prnstr.crossasm.com - executable made by nasm for linux

bioschar.com.disassembly.asm - disassembly of DOS generated executable
b_prnstr.com.disassembly.asm - disassembly of DOS generated executable
b_prnstr.crossasm.com.disassembly.asm - disassembly of linux generated executable

to assemble it on linux use the following command:
$ nasm -o b_prnstr.crossasm.com -f bin b_prnstr.asm

to assemble it on dos use the following command:
$ nasm -o b_prnstr.com -f bin b_prnstr.asm


