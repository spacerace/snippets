# needs dev86/bcc for building, upx for packing

all:
	@rm -rf argtest.com
	bcc -Md -ansi -0 -O -I./include/ -V -W -o argtest.com main.c
	@du -b argtest.com
	@cp argtest.com a/
	
dosbox:
	dosbox
	
