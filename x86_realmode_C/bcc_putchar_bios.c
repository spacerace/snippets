/* bcc_putchar_bios.c
 * 
 * 2016 Nils Stec <stecdose@gmail.com>
 * 
 * this file shows how to use bcc compiler on linux to produce MS-DOS
 * real-mode 8086 executables.
 * 
 * It uses a BIOS interrupt to print a character.
 * 
 * This will run on any *-DOS system as well as on bare metal 8086-
 * platforms, *IF* they have a PC-compatible BIOS.
 * 
 * At the end there is a call to a DOS interrupt, that causes the
 * currently running program to be terminated. If you don't have DOS
 * or a BIOS, just remove these parts.
 * 
 * Possible uses for this "template":
 *   option rom code
 *   16bit real mode OS in C
 *   *-DOS executables
 * 
 * 
 * compile with: 
 *   $ bcc -i -Md -ansi -0 -I -I. -V -W -x -o bcc_pcb.com bcc_putchar_bios.c
 */

void putc(c);
void print_str(char *s);
void return_to_dos();

unsigned short ret_test();

#define uint8_t	unsigned char
#define uint16_t unsigned short

int main() {
	uint8_t a;
	uint16_t retval;
	
	a = 1+5;
	a += '0';	// convert to ASCII, more than 9 won't work this way
	putc(a);
	
	print_str("\r\n");	// new line on DOS
	
	retval = ret_test();
	
	if(retval == 0x1234) print_str("return-test ok!");
	
	return_to_dos();
	
}

/* ret_test()
 * 
 * this example shows how to return data from inline assembler to C.
 * 
 * simple ints are returned via AX register. On x86 DOS an int equals
 * unsigned short. 
 * 
 */
unsigned short ret_test() {
	#asm
		mov ax, #0x1234		; at the end of a C-function without
							; trailing code (save/restore context)
							; this is the same like 'return 0x1234;'
	#endasm
}

void print_str(char *s) {
	while(*s) {
		putc(*s);
		s++;
	}
}

void putc(c) {
	#asm
		mov ah, #0x0E	; int function Eh, write char, move cursor
		mov bx, sp
		mov al, [bx+2]	; arguments are on stack, 
						; see cdecl calling conventions
		mov bh, #0		; page
		mov cx, #1		; number of chars
		int 0x10
	#endasm
}

void return_to_dos() {
	#asm
		mov ah, 0x4c
		int 0x21
	#endasm
}

#ifdef __FIRST_ARG_IN_AX__
#error "calling conventions changed, can't compile this way."
#endif
