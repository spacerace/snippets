; B_PRNSTR - BIOS PRINT STRING
; this code uses the BIOS to clear the screen and print a line
;
; NO DOS functions are used but of exiting the program.
; If you remove this, it will run completly without DOS on a PC.
;
; \> nasm -o B_PRNSTR.COM -f bin B_PRNSTR.ASM
;
        bits 16
        cpu 8086
        org 100h

start:
        call clrscr

        mov bl, 0x3f    ; set color white on cyan
        mov si, msg
        call print_str

        call return_to_dos

msg     db "hello 16bit world!", 0


new_line:
        mov ah, 0x03    ; get cursor
        int 0x10
        inc dh          ; row++
        xor dl, dl      ; line=0
        call set_cursor
        ret

; print string to cursor
; SI = points to zero terminated string
; BL = color
; located at cursor
print_str:              ; loop to print a zero terminated string of bytes
        cld                
        lodsb
        test al, al     ; is it zero?
        jz out          ; we're done
        call print_char ; not done, print char
        jmp print_str   ; go on
out:    ret

; print a single char to cursor
; AL = char (ASCII)
; BL = color
; located at cursor
print_char:
        mov cx, 1
        mov ah, 0x09
        int 0x10
        call inc_cursor
        ret

inc_cursor:
        mov ah, 0x03    ; get cursor
        int 0x10        ; now DH=row DL=col
        inc dl
        call set_cursor
        ret

clrscr:
        mov dh, 0       ; cursor to 0/0
        mov dl, 0
        call set_cursor
        mov ah, 0x09    ; print 2k spaces, 80x25, default attribute
        mov al, ' '     ; space char
        mov bh, 0       ; page 0
        mov cx, 2000    ; 2k
        mov bl, 0x07    ; grey on black
        int 0x10
        ret
               
set_cursor:
        mov ah, 0x02
        int 0x10
        ret

return_to_dos:
        mov ah, 0x4C
        int 0x21


