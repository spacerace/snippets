# bcc bios keyboard/video out
 
It uses bcc/dev86 as compiler and all IO (keyboard, video) is done via 
BIOS-interrupts and inline assembler. 
 
# Running it 
 
On linux-systems you can use my makefile for starting dosbox: 
```
$ make dosbox 
``` 
If you don't have it installed, here's how to do that on debian (ubuntu): 
```
$ apt-get install dosbox qemu
```
 
# Building it 
 
You'll only need "dev86 / bcc" and "make"
```
$ apt-get install bcc make
``` 
There are different targets for make: 
- all 
- dosbox 

all builds x86-pong. 
dosbox starts dosbox with my provided dosbox.conf 

# License

GPL-v2
