; tampers ah, bh, ch, dl, dh, dl, ax, ALL
inc_cursor:
	mov	ah,0x03	; get cursor
	mov	bh,0
	int	0x10
	; now  AX=0, CH=start scan line, CL=end scan line, DH=Row, DL=Col
	cmp 	dl, 79
	jne 	no_row_overflow
row_overflow:
	inc 	dh
	mov 	dl, 0
	call 	set_curs
	ret
no_row_overflow:
	inc 	dl
	call 	set_curs
	ret
	
	
	
; save_cursor:
; 	mov	ah, 0x03
; 	mov	bh, 0
; 	int	0x10
; 	; AX = 0; DH=Row; DL=col
; 	mov	[save_row], dh
; 	mov	[save_col], dl
; 	ret
; 	save_row db 0x00
; 	save_col db 0x00
; 
; restore_cursor:
; 	mov	dh, [save_row]
; 	mov	dl, [save_col]
; 	call	set_curs
; 	ret