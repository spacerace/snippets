# needs dev86/bcc for building

all:
	bcc -Md -ansi -0 -O -I./include/ -V -W -o system.com main.c
	@du -b system.com
	@cp system.com a/
	
dosbox:
	dosbox
	
