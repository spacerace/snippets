all:
	bcc -vv -Md -ansi -0 -O -I./include/ -V -W -o kit_test.com kit_test.c kitten.c
	ls -al kit_test.com
	
upx:	all
	upx -9 kit_test.com
	
dosbox: all
	dosbox
	
