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
	
	
----------------------------------------
calculate divh/divl from frequency:
	int div = 1193180/400;	// base/desired frequency
	printf("divl 0x%02x\ndivh 0x%02x\n", (uint8_t)div, (uint8_t)(div>>8));