# Writing x86 realmode code in C

This repo contains an example on how to use bcc to write x86 real mode code.

The folder ***nasm_16bit_dos_ex*** contains examples on how to write simple x86 real mode *assembly*-programs. 
They and their' disassemblys were used as a starting point, when figuring out how to use bcc on bare metal hardware.

Here's there C part, beginning with a list of files and a short description:

 - *bcc_pcb.com* - assembled executable, runs on DOS
 - *bcc_putchar_bios.c* - source code
 - *bcc_putchar_bios.disassembly.asm* - disassembly of executable
 - *bcc_putchar_bios.png* - a screenshot

It uses a BIOS interrupt to print a character.
This will run on any *-DOS system, as well as on bare metal 8086-
platforms, **if** they have a PC-compatible BIOS.

At the end there is a call to a DOS interrupt, that causes the
currently running program to be terminated. 
If you don't have DOS or a BIOS, just remove these parts.

