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