; simple bootsector replacement for MS or other's boring default bootsectors.
; if you try to bootup from a disk with this bs you'll have something more
; than just a few chars telling you, that there is nothing.
;
; we have 446 bytes to do this, we do better!
;
; this file 'bs_simple.asm' contains a slighty too complicated bootsector
; for just displaying one line...
; 
; this bs only takes 100 bytes of which 68 bytes are used by the message.
;  only 32bytes used for printing the message.
;
; (c) 2016 nils stec
;
;
	bits	16
	org 	0x7c00

	mov	bl, 0x06	; color for text = brown
	mov	si, boot_msg
print_msg:			; si = string, bl = color
	cld
	lodsb
	test	al, al		; test if zero char
	jz	outhere
put_char:
	mov	cx, 1		
	mov	ah, 0x09
	int	0x10		; print CX n chars in AL with color BL to cursor
inc_cursor:
	mov	ah, 0x03 	; get cursor
	int	0x10		; now DH=row DL=col
	inc	dl
	mov	ah, 0x02 	; set cursor
	int	0x10
	jmp	print_msg
outhere:
	.hang	jmp	.hang

boot_msg	db "there is no operating system to boot. go and get a proper dos disk!",0

; fill with zeroes till signature
; times 	510-($-$$) db 0x00
; dw 0xAA55 ; some bioses need this signature, some not. qemu wont boot without.
