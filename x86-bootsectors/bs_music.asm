; simple bootsector replacement for MS or other's boring default bootsectors.
; if you try to bootup from a disk with this bs you'll have something more
; than just a few chars telling you, that there is nothing.
;
; we have 446 bytes to do this, we do better!
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
	
	call	print_messages	
	
footer:	mov	dh, 19		; row
	mov	dl, 2		; col
	call	set_curs
	mov	cx, 380		; 80x4 = 320 chars
loopfs:	push	ax
	push	bx
	push	cx
	push	dx
	call	rand		; 8bit rand in AL
	mov	bl, al		; BL=color for put_char
	and	bl, 0x0f
	mov	al, 0x03		; char to put
	call	put_char
	call	inc_cursor
	call	keyboard_handler	
	pop	dx
	pop	cx
	pop	bx
	pop	ax
	loop	loopfs
	
.hang_forever:	jmp	footer

keyboard_handler:
	mov	ah, 0x11	; get keyboard status without wait
	int	0x16		; on return: ZF=0 if key pressed (data waiting)
				;            AX=0 if no scan code avail
				;            AH=scancode
				;            AL=ascii char or special function key
	jnz	gotkey
	ret
gotkey:
	mov	ah, 0x10
	int	0x16
	mov	[rcv_key], al	; receive ascii code of pressed key
	call	save_cursor
	mov	bl, 0x0d
	mov	dh, 5
	mov	dl, 10
	mov	si, boot_msg1
	call	set_curs
	call	puts
	call	restore_cursor
	ret
rcv_key db 0x00	

; tampers ALL, si
print_messages:	
	mov	bl, 0x0A
	mov	dh, 3		; cursor y
	mov	dl, 10		; cursor x
	mov	si, boot_msg0	; print first message
	call	set_curs
	call	puts

	mov cx, 15
.l1:	push ax
	push bx
	push cx
	push dx
	mov bl, cl
	mov dh, cl
	add dh, 2
	mov dl, 58
	mov si, boot_msg2
	call set_curs
	call puts
	pop dx
	pop cx
	pop bx
	pop ax
	loop .l1
	ret	

; http://www.programmersheaven.com/discussion/219366/a-random-number-generator-routine
; returns AL 8bit rand
; tampers ax, dx
rand:
	mov ax,[seed]
	mov dx,0x8405
	mul dx		; dx*ax into dword dx:ax
	
	cmp ax,[seed]
	jnz gotseed	; if new seed = old seed, alter seed
	mov ah, dl
	inc ax
gotseed:
	mov word [seed], ax
	mov ax, dx 	; al = random num
	mov word [rndnum], ax
	ret
random_variables:
	seed	dw 0x3749
	rndnum	dw 0x0000
	
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

; SI=string BL=color
puts:
	cld
	lodsb
	test	al, al	; test if zero char
	jz	.done
	call put_char
	call inc_cursor
	jmp	puts
.done:
	ret

; DH=y DL=x
set_curs:
	mov	bh, 0
	mov	ah, 0x02
	int	0x10
	ret

; tampers ah, bh, ch, dl, dh, dl, ax, ALL
inc_cursor:
	mov	ah,0x03	; get cursor
	mov	bh,0
	int	0x10
	; now  AX=0, CH=start scan line, CL=end scan line, DH=Row, DL=Col
	cmp 	dl, 77
	jne 	no_row_overflow
row_overflow:
	inc 	dh
	mov 	dl, 2
	call 	set_curs
	ret
no_row_overflow:
	inc 	dl
	call 	set_curs
	ret
	
save_cursor:
	mov	ah, 0x03
	mov	bh, 0
	int	0x10
	; AX = 0; DH=Row; DL=col
	mov	[save_row], dh
	mov	[save_col], dl
	ret
	save_row db 0x00
	save_col db 0x00

restore_cursor:
	mov	dh, [save_row]
	mov	dl, [save_col]
	call	set_curs
	ret

beep:	;400hz divl 0xa6 divh 0x0b
	mov al, 0xb6
	out 0x43, al
	
	mov al, 0xa6
	out 0x42, al
	mov al, 0x0b
	out 0x42, al
	
	in al, 0x61
	or al, 0x03 	
	out 0x61, al
	ret
beepoff:
	in al, 0x61
	and al, 0xfc
	out 0x61, al
	ret
	
boot_msg0	db "nothing will happen.", 0
boot_msg1	db "nothing but noise. press keys 1-9.", 0
;boot_msg2	db 0x11,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,0x10,0
boot_msg2       db 0x11,1,2,1,2,13,13,14,14,14,14,13,13,2,1,2,1,0x10,0
; fill with zeroes till signature
;        times 	510-($-$$) db 0x00
;        dw 0xAA55 ; some bioses need this signature, some not. qemu wont boot without.
