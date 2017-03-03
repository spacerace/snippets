	; bits 16
	; cpu 8086
	; org 100h

start:
00000100  B409              mov ah,0x9		; int function 9h
00000102  B023              mov al,0x23		; character '#'
00000104  B96400            mov cx,0x64		; print 100 chars
00000107  B3F3              mov bl,0xf3		; attribute: white on cyan
00000109  CD10              int 0x10
0000010B  C3                ret
