        bits 16
        cpu 8086
        org 100h

start:
        mov ah, 0x09		; int function used
        mov al, '#'		; write #
        mov cx, 100		; 100 chars to write
        mov bl, 0xf3		; attribute white on cyan
        int 0x10
        ret
   
        

