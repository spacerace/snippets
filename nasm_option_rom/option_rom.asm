; option rom template for nasm
; 
;  this simple to use template was created for wiriting x86 real mode
;  code in a simple developement environment.
;  
;  you will need nasm, python and qemu to build and run it.
;  this demo just prints a string.
;
;  tbd: load address? stack? ... ...
; 
; (c) 2016 nils stec <stecdose@gmail.com> and others:
; https://sites.google.com/site/pinczakko/building-a-kernel-in-pci-expansion-rom
;
; first i thought, the AA55-size-header would be enough, but qemu hasn't
; booted that shit. So i were forced to build up a pnp-rom.
; this is were pinczakko's site enters the game.
;

	cpu		186
	bits	16 
	org		0x0000
	
	db		0x55
	db		0xAA	; signature
	
	db		16		; length of option rom in 512b increments = 8k
	
	jmp rom_init
	retf
	
	Times 	0x18-($-$$) db 0	;;zero fill in between
	dw	PCI_DATA_STRUC			;;Pointer to PCI HDR structure (at 18h)

	Times 	0x1A-($-$$) db 0	;;zero fill in between
	dw	PnP_Header				;;PnP Expansion Header Pointer (at 1Ah)

;----------------------------
; PCI data structure
;----------------------------
PCI_DATA_STRUC:
	db	'PCIR'		;PCI Header Sign
	dw	0x9004		;Vendor ID; 0x9004 = Adaptec
	dw	0x8178		;Device ID; If Vendor == Adaptec => Ultra/Ultra-Wide SCSI Ctrlr
	dw	0x00		;VPD, Vital Product Data can be used for revision information or something else
	dw	0x18		;PCI data struc length (byte)
	db	0x00		;PCI Data struct Rev
	db	0x02		;Base class code, 02h == Network Controller
	db	0x00		;Sub class code = 00h and interface = 00h -->Ethernet Controller
	db	0x00		;Interface code, see PCI Rev2.2 Spec Appendix D
	dw	16			;Image length in mul of 512 byte, little endian format
	dw	0x00		;rev level
	db	0x00		;Code type = x86
	db	0x80		;last image indicator
	dw	0x00		;reserved

;-----------------------------
; PnP ROM Bios Header
;-----------------------------
PnP_Header:
	db	'$PnP'			;PnP Rom header sign
	db	0x01			;Structure Revision
	db	0x02			;Header structure Length in mul of 16 bytes
	dw	0x00			;Offset to next header (00 if none)
	db	0x00			;reserved
	db	0x7A			;8 Bit checksum (for this header, -->
						; --> check again after compile and repair if needed)   <= ?! TODO ?! 
	dd	0x00			;PnP Device ID --> 0h in Realtek RPL ROM
	dw	msg_author		;pointer to manufacturer string
	dw	msg_product		;pointer to product string
	db	0x02,0x00,0x00	;Device Type code 3 byte
	db	0x14			;Device Indicator, 14h from RPL ROM-->See Page 18 of
						;PnP BIOS spec., Lo nibble (4) means IPL device

	dw	0x00			;Boot Connection Vector, 00h = disabled
	dw	0x00			;Disconnect Vector, 00h = disabled
	dw	os_init 		;Bootstrap Entry Vector (BEV)
	dw	0x00			;reserved
	dw	0x00			;Static resource Information vector (0000h if unused)

rom_init:
		pusha
		cli
		mov	ax,cs		
		mov	ds,ax
		mov	es,ax
		
		; stack is at 0000:2000
		mov ax, 0x0000
		mov ss, ax
		mov sp, 0x2000
		sti				; enable interrupts	
		
		call clrscr
		call clrscr

		mov bl, 0x0F
		mov si, msg_init
		call print_str		
		call new_line

		
		call com1_init
		mov si, msg_serial_init
		call print_str
		call new_line
		
	;	mov dx, 0x378
	;	mov al, '#'
	;	out dx, al

	;	mov dx, 0x378
	;	mov al, '#'
	;	out dx, al

	;	mov dx, 0x378
	;	mov al, '#'
	;	out dx, al
		
		;mov ah, 0x00
		;int 0x16
		
		popa
		retf

msg_serial_init		db	"COM1 at 0x3f8 configured to 38400,8n1", 0

os_init: jmp os_init

com1_init:
	mov dx, 0x3f8+1	
	mov al, 0x00	; disable all interrupts
	out dx, al
	
	mov dx, 0x3f8+3
	mov al, 0x80	; DLAB
	out dx, al
	
	mov dx, 0x3f8+0
	mov al, 0x03	; 38400 baud lo byte divisor
	out dx, al

	mov dx, 0x3f8+1	; lo div
	mov al, 0x00
	out dx, al
	
	mov dx, 0x3f8+3	
	mov al, 0x03	; 8n1
	out dx, al
	
	mov dx, 0x3f8+32
	mov al, 0xc7	; fifo, enable, clear, 14b threshold
	out dx, al
	
	mov dx, 0x3f8+4
	mov al, 0x0b	; irqs enabled, rts/dtr set
	out dx, al

	ret

; sends char in AL via COM1
put_char_com1:
	call wait_for_com1_tx_buf
	mov dx, 0x3f8
	out dx, al

; waits for COM1 transmit buffer to be empty
wait_for_com1_tx_buf:
	
	; TODO this function here
	ret

; print a zero terminated string, args:
; si = string, bl = color
; prints to current cursor position	
print_str:				; si = string, bl = color
	cld
	lodsb
	test	al, al		; test if zero char
	jz	outhere
put_char:
	mov	cx, 1		
	mov	ah, 0x09
	int	0x10			; print CX n chars in AL with color BL to cursor
	call inc_cursor
	jmp	print_str
outhere:
	ret

inc_cursor:
	mov	ah, 0x03 	; get cursor
	int	0x10		; now DH=row DL=col
	inc	dl
	mov	ah, 0x02 	; set cursor
	int	0x10
	ret

new_line:
	mov ah, 0x03
	int 0x10
	inc dh
	xor dl,dl
	mov ah, 0x02
	int 0x10
	ret

clrscr:
	mov dh, 0
	mov dl, 0
	call set_cursor
	mov ah, 0x0a
	mov al, ' '
	mov bh, 0
	mov cx, 2000
	int 0x10
	ret	

; DH = row, DL = col
set_cursor:
	mov ah, 0x02
	int 0x10
	ret

msg_init		db	"option rom init.", 0
msg_author  	db	"nils stec", 0
msg_product		db	"option rom", 0

; fill with zeroes till signature
times 	8191-($-$$) db	0x00
					db 	0x00	; checksum
								; will be calculated by script
