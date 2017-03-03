some simple bootsectors
=====================

This repository contains some simple bootsectors, I've started to write to do some x86 assembly.

There's also a tool for building the mbr including MPE information+magic as well as a PIT frequency calculator.

For building the bootsectors you will need the netwide assembler (nasm).
For building the utilities you will need a simple c compiler (cc/gcc).

> **Build all:**
$ make

The PC's bootsector layout is always the same:

    start     end    size   description
    0        445     446    stage1 bootloader
    446      461     16	    master partition entry #1
    462      477     16     master partition entry #2
    478      493     16     master partition entry #3
    494      509     16     master partition entry #4
    510	     511     2      magic 0x55AA




