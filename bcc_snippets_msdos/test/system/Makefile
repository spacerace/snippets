# needs dev86/bcc for building

all:
	bcc -Md -ansi -0 -O -V -W -o system.com main.c
	bcc -Md -ansi -0 -O -V -W -o argtest.com argtest.c
	@du -b system.com
	@du -b argtest.com
	@cp system.com a/system.com
	@cp argtest.com a/argtest.com
	
dosbox:
	dosbox
	
