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
