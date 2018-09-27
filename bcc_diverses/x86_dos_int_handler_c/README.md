# MS-DOS interrupt example for dev86/bcc c compiler

16bit real mode program

2016 stecdose@gmail.com

this example installs an interrupt handler for int 0x64.
this handler prints a number on the screen and increments this
number.
it gets called ten times.
afterwards the original interrupt handler location will be restored. 

compile with:
$ bcc -Md -ansi -0 -V -o dosint.com dos-int-handler.c

This will generate a DOS-compatible .com-file (dosint.com).
It can be used on any DOS system.

If you like to use this on bare metal hardware, there's another file,
which uses bios interrupts only. but this will be published later...

