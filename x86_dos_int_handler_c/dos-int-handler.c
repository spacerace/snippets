/* MS-DOS interrupt example for dev86/bcc c compiler
 * 16bit real mode program
 * 
 * 2016 stecdose@gmail.com
 * 
 * this example installs an interrupt handler for int 0x64.
 * this handler prints a number on the screen and increments this
 * number.
 * it gets called ten times.
 * afterwards the original interrupt handler location will be restored. 
 * 
 * compile with:
 *  $ bcc -Md -ansi -0 -V -o dosint.com dos-int-handler.c
 * 
 * This will generate a DOS-compatible .com-file (dosint.com).
 * It can be used on any DOS system.
 * 
 * If you like to use this on bare metal hardware, there's another file,
 * which uses bios interrupts only. but this will be published later...
 * 
 */

#include <stdio.h>

#define uint8_t	unsigned char
#define uint16_t unsigned short

/* prototypes */
void install_ivt_entry(uint8_t int_n, uint16_t segment, uint16_t offset);
void get_ivt_entry(uint8_t int_n, uint16_t *segment, uint16_t *offset);
void print_ivt_entry(uint8_t int_n);
void print_addr(uint16_t seg, uint16_t off);
void set_mem(uint16_t seg, uint16_t off, uint16_t data);
uint16_t get_mem(uint16_t seg, uint16_t off);
uint16_t get_cs();
void int64h_handler();

/* global variable */
static int count;

int main() {
	uint16_t read_seg, read_off;
	printf("interrupt test in C, compiler: bcc/dev86\r\n\r\n");
	
	count = '0';
	
	printf("my cs=%04xh, address of ISR=%04xh\r\n", get_cs(), int64h_handler);
	
	printf("ivt entry for int 64h before change, saving it for later restore: ");
	print_ivt_entry(0x64);
	printf("\r\n");
	get_ivt_entry(0x64, &read_seg, &read_off);
	
	install_ivt_entry(0x64, get_cs(), int64h_handler);

	printf("ivt entry for int 64h after change:  ");
	print_ivt_entry(0x64);
	printf("\r\n");
	
	printf("if everything works, you should see \"0123456789\" on next line:\r\n");
	#asm
		int #0x64
		int #0x64
		int #0x64
		int #0x64
		int #0x64
		int #0x64
		int #0x64
		int #0x64
		int #0x64
		int #0x64
	#endasm
	
	printf("\r\n\r\nnow uninstalling IVT entry, restoring old ISR address...\r\n");
	install_ivt_entry(0x64, read_seg, read_off);
	printf("\r\nrestored to: ");
	print_ivt_entry(0x64);
	
	
}

/* Interrupt service routine for int 0x64
 * It prints out the contents of a global variable and increments it.
 * Every int 0x64-instruction the output is 1 greater compared to last
 * call.
 */
void int64h_handler() {
	#asm
		pusha

		mov al, _count	; get counter (global static C variable)
		inc _count		; increment counter

		; print counter
		mov ah, #0x0E	; int function Eh, write char, move cursor
		mov bh, #0		; page
		mov cx, #1		; number of chars
		int 0x10	
		
		popa
		iret
	#endasm
}

/* this functions places an IVT entry, takes segment, offset and 
 * interrupt number
 */
void install_ivt_entry(uint8_t int_n, uint16_t segment, uint16_t offset) {
	set_mem(0, ((int_n*4)+2), segment);
	set_mem(0, (int_n*4), offset);
}

/* returns segment and offset to a given interrupt number */
void get_ivt_entry(uint8_t int_n, uint16_t *segment, uint16_t *offset) {
	*segment = get_mem(0, ((int_n*4)+2));
	*offset = get_mem(0, ((int_n*4)));
}

/* prints an entry in SEG:OFF-format */
void print_ivt_entry(uint8_t int_n) {
	uint16_t segment;
	uint16_t offset;
	get_ivt_entry(int_n, &segment, &offset);
	
	print_addr(segment, offset);
}

/* prints an address of two 16bit variables in XXXX:XXXX format */
void print_addr(uint16_t seg, uint16_t off) {
	printf("%04x:%04x", seg, off);
}


/* get a 16bit word from an absolute location in SEG:OFF format */
uint16_t get_mem(uint16_t seg, uint16_t off) {
	#asm
		mov bx, sp
		mov es, [bx+2]	; seg
		mov	bx, [bx+4]	; off
		seg	es
		mov	ax, [bx]
	
	
	#endasm
}

/* write a 16bit word to an absolute location in SEG:OFF format */
void set_mem(uint16_t seg, uint16_t off, uint16_t data) {
	#asm
		mov bx, sp
		mov es, [bx+2]	; seg
		mov ax, [bx+6]	; data
		mov bx, [bx+4]	; off
		seg es
		mov [bx], ax
	#endasm
}

/* returns current code segment */
uint16_t get_cs() {
	#asm
		push cs
		pop ax
	#endasm
}

