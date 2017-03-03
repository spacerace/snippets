; simple bootsector replacement for MS or other's boring default bootsectors.
; if you try to bootup from a disk with this bs you'll have something more
; than just a few chars telling you, that there is nothing.
;
; we have 446 bytes to do this, we do better!
;
; this file 'bs_random.asm' contains a very blinky bootsector...
; 
; this bs only takes 153 bytes.
;
;
; (c) 2016 nils stec
;
;
	bits	16
	org 	0x7c00

startup_code:
	cli			; disable interrupts
setup_segments:
	mov	ax, 0		; segment config
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
setup_stack:
	mov	sp, 0xA000	; setup stack
	sti			; enable interrupts
set_video_mode:
	mov	al, 0x03	; video mode 80x25 16colors
	mov	ah, 0x00	; set video mode
	int	0x10
cursor_invis:
	mov	ah, 0x01
	mov	cx, 0x2607
	int	0x10
main:	push	ax
	push	bx
	push	cx
	push	dx
	
	call	rand		; get random row
	mov	[tempvar], al
	call	rand		; get random col
	mov	dl, al
	mov	dh, [tempvar]
	call	set_curs	; set cursor	
	call	rand		; get random color
	mov	bl, al

	mov	al, '%'		; print char
	call	put_char	; AL char, BL color
	call	delay_func

	pop	dx
	pop	cx
	pop	bx
	pop	ax
	jmp	main

	tempvar	db	0x00

delay_func:
	mov cx, 0xfff
.l1:	nop
	loop .l1
	ret

randvars:
	seed	dw	0x0000
rand:
	xor 	ax, ax
	int	0x1a
	ror	dx, 2
	shr	cx, 3
	mov	ax, cx
	mov	bx, dx
	xor	ax, bx
	ret

; http://www.programmersheaven.com/discussion/219366/a-random-number-generator-routine
; returns AL 8bit rand
; tampers ax, dx
;init_random:
;	seed	dw 0x3749
;	rndnum	dw 0x0000
;rand:
;	mov ax,[seed]
;	mov dx,0x8405
;	mul dx		; dx*ax into dword dx:ax
;	
;	cmp ax,[seed]
;	jnz gotseed	; if new seed = old seed, alter seed
;	mov ah, dl
;	inc ax
;gotseed:
;	mov word [seed], ax
;	mov ax, dx 	; al = random num
;	mov word [rndnum], ax
;	ret

; AL=char BL=color
; puts at cursor, does not affect cursor
; use inc_cursor after put_char
; uses internally CX, AH, BH, DL, DH
put_char:
	mov	cx, 1	; count
	mov	ah, 0x09
	mov	bh, 0	; page
	int	0x10
	ret

; DH=y DL=x
set_curs:
	mov	bh, 0
	mov	ah, 0x02
	int	0x10
	ret
; fill with zeroes till signature
; times 	510-($-$$) db 0x00
; dw 0xAA55 ; some bioses need this signature, some not. qemu wont boot without.
