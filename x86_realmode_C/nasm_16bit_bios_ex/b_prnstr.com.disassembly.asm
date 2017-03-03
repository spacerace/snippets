; this disassembly is commented. stored string we're disassembled to nonsense-
; instructions. I replaced these by the strings.

	; bits 16
	; cpu 8086
	; org 100h

start:
00000100  E84B00            call word 0x14e	; call clrscr
	
00000103  B33F              mov bl,0x3f			; set color white on cyan
00000105  BE0E01            mov si,0x10e		; place string at 10e into SI
00000108  E82200            call word 0x12d	; call print_str
0000010B  E85A00            call word 0x168	; call return_to_dos

0000010E 68 ; h
         65 ; e
         6C ; l
         6C ; l
         6F ; o
         20 ; 
         31 ; 1
         36 ; 6
         62 ; b
         69 ; i
         74 ; t
         20 ; 
         77 ; w
         6F ; o
         72 ; r
         6C ; l
         64 ; d
         21 ; !
00000120 00 ; zero termination

new_line:
00000121  B403              mov ah,0x3		; get cursor
00000123  CD10              int 0x10		
00000125  FEC6              inc dh		; row++
00000127  30D2              xor dl,dl		; line = 0
00000129  E83700            call word 0x163	; call set_cursor
0000012C  C3                ret

print_str:
0000012D  FC                cld
0000012E  AC                lodsb
0000012F  84C0              test al,al		; is it zero?
00000131  7405              jz 0x138		; jz out
00000133  E80300            call word 0x139	; call print_char
00000136  EBF5              jmp short 0x12d	; jmp print_str
out:
00000138  C3                ret

print_char:
00000139  B90100            mov cx,0x1
0000013C  B409              mov ah,0x9
0000013E  CD10              int 0x10
00000140  E80100            call word 0x144
00000143  C3                ret

inc_cursor:
00000144  B403              mov ah,0x3		; get cursor
00000146  CD10              int 0x10		; now DH=row DL=col
00000148  FEC2              inc dl
0000014A  E81600            call word 0x163	; call set_cursor
0000014D  C3                ret

clrscr:
0000014E  B600              mov dh,0x0		; cursor to 0/0
00000150  B200              mov dl,0x0
00000152  E80E00            call word 0x163	; call set_cursor
00000155  B409              mov ah,0x9		; print 2k spaces, 80x25, default attributes
00000157  B020              mov al,0x20		; space char
00000159  B700              mov bh,0x0		; page 0
0000015B  B9D007            mov cx,0x7d0	; 2k spaces
0000015E  B307              mov bl,0x7		; grey on black
00000160  CD10              int 0x10
00000162  C3                ret

set_cursor:
00000163  B402              mov ah,0x2
00000165  CD10              int 0x10
00000167  C3                ret

return_to_dos:
00000168  B44C              mov ah,0x4c
0000016A  CD21              int 0x21
