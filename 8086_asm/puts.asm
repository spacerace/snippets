	mov si, message
	call	puts


puts:
        cld
        lodsb
        test    al, al  ; test if zero char
        jz      .done

        mov     ah, 0x0E
        mov     bh, 0
        int     0x10
        jmp     puts
.done:
        ret


message	db "blabla",0


----------------------------------

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
	
	
---> needs cursor subroutines from cursor.asm