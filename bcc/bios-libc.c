/* bios libc 
 * 
 * proof of concept
 * gpl
 * 2016 NS, other years - others, see comments in code
 * stecdose@gmail.com
 *
 */

#include "bios-libc.h"

uint16_t int11_getconfig() {
	#asm
		xor ax, ax
		xor bx, bx
		xor cx, cx
		xor dx, dx
		int 0x11		; returns config in AX
	#endasm
}

uint16_t int12_getmaxrambelow1m() {
	#asm
		xor ax, ax
		xor bx, bx
		xor cx, cx
		xor dx, dx
		int 0x12		; returns memsize in kB
	#endasm
}

void _kbhit() {
	#asm
		mov ah, #0x00	; read keyboard, blocking
		int 0x16
	#endasm
}

// lower byte = ASCII, higher byte = SCANCODE
uint16_t _getch() {
	#asm
		xor ax, ax
		mov ah, #0x00	; read keyboard, blocking
		int 0x16
	#endasm	
}

/* get char and attribute from screen, lower 8bits=char,high8=attrib */
uint16_t get_from_screen() {
	#asm
		mov ah, #0x08	; get character+attrib
		xor bx, bx		; page 0
		int 0x10
		push ax
		mov al, bl		; ret attrib in upper 8bits		
		shr ax, 8
		pop cx
		mov ah, cl
		xor cx, cx
		mov cx, ax
		mov ah, cl
		mov al, ch
	#endasm
}
uint8_t scroll_color;

void scroll() {
	#asm
		mov ah, #0x06	; scroll
		xor cx, cx		; top left edge
		mov dh, #24		; lower right edge
		mov dl, #79		; lower right edge
		mov bh, #0x00	; attribute
		mov al, #1		; 1 line
		int 0x10
	#endasm
	
}

/* http://wiki.osdev.org/Meaty_Skeleton#libc.2Fstring.2Fstrlen.c */
uint16_t _strlen(char * str) {
		uint16_t len = 0;
		while (str[len])
			len++;
		return len;
}

char *_gets(char *s) {
	uint8_t c = 0xff;
	
	do {
		c = (uint8_t)_getch()&0xff;
		*s = c;
		s++;
	} while(c != 0x0D);

	*(--s) = '\0';	// end of string
	
	return s;
}

void print_str(char *s) {
	while(*s) {
		_putc(*s);
		s++;
	}
}

void put_hex8(uint8_t hex8) {
	uint8_t save = hex8;
	
	hex8 = hex8 >> 4;
	hex8 = hex8 & 0x0f;
	hex8 += '0';
	if(hex8 > '9') hex8 += 7;
	_putc(hex8);
	
	save = save & 0x0f;
	save += '0';
	if(save > '9') save += 7;
	_putc(save);	
}

void put_hex16(uint16_t hex16) {
	uint8_t hex8 = (hex16 >> 8) & 0xff;
	put_hex8(hex8);
	
	hex8 = hex16 & 0xff;
	put_hex8(hex8);
}

/* itoa.c <ndf@linux.mit.edu> taken from bcc's source */
#define __MAX_INT_CHARS 7

char *_itoa(int i) {
   static char a[__MAX_INT_CHARS];
   char *b = a + sizeof(a) - 1;
   int   sign = (i < 0);

   if (sign)
      i = -i;
   *b = 0;
   do
   {
      *--b = '0' + (i % 10);
      i /= 10;
   }
   while (i);
   if (sign)
      *--b = '-';
   return b;
}

/* Copyright (C) 1995,1996 Robert de Bath <rdebath@cix.compulink.co.uk>
 * This file is part of the Linux-8086 C library and is distributed
 * under the GNU Library General Public License.
 * 
 * taken from bcc's source
 */

static char buf[12];

extern char * ultoa();

char *_ltoa(long val) {
   char *p;
   int flg = 0;
   if( val < 0 ) { flg++; val= -val; }
   p = ultoa(val);
   if(flg) *--p = '-';
   return p;
}

char *_ultoa(unsigned long val) {
   char *p;

   p = buf+sizeof(buf);
   *--p = '\0';

   do
   {
      *--p = '0' + val%10;
      val/=10;
   }
   while(val);
   return p;
}


void inc_cursor() {
	#asm
		xor bx, bx		; page 0
		mov ah, #0x03
		int 0x10		; get cursor
		inc dl			; inc row
		mov ah, #0x02
		int 0x10		; set cursor
	#endasm
}

void new_line() {
	#asm
		xor bx, bx		; page 0
		mov ah, #0x03	; get cursor
		int 0x10
		inc dh			; inc line
		xor dl,dl		; col = 0
		mov ah, #0x02	; set cursor
		int 0x10		
	#endasm
}

void clrscr() {
	set_cursor(0,0);
	#asm
		mov ah, #0x0A	; repeat printing chars
		mov al, #0x20	; space
		mov bh, #0
		mov cx, #2000
		int 0x10
	#endasm
}

void set_cursor(uint16_t col, uint16_t row) {
	#asm
		mov bx, sp
		mov dh, [bx+4]
		mov dl, [bx+2]
		xor bx, bx		; page 0
		mov ah, #0x02	; DH = row, DL = col
		int 0x10
	#endasm
}

uint16_t get_cursor() {
	#asm
		xor bx, bx		; page 0
		mov ah, #0x03	; get cursor DH = row, DL = col
		int 0x10
		mov ax, dx		; return cursor in AX
	#endasm
}



void putc_attr(uint16_t attrib, uint16_t c) {
	#asm
		; put_char takes:
		; AL     = char (ASCII)
		; BL     = color
		; located at cursor
		
		mov bx, sp
		mov al, [bx+4]	; get c
		mov ah, #0x09	; interrupt function
		mov bl, [bx+2]	; get attrib
		mov bh, #0		; page
		mov cx, #1
		
		int 0x10
	#endasm
}

void _putc(c) {
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

void _outb(uint16_t port, uint16_t data) {
	#asm
		mov bx, sp
		mov dx, [bx+2]	; get port
		xor ax, ax
		mov ax, [bx+4]	; get data
		out dx, al		; 8bit output
	#endasm
}

void _outw(uint16_t port, uint16_t data) {
	#asm
		mov bx, sp
		mov dx, [bx+2]	; get port
		mov ax, [bx+4]	; get data
		out dx, ax		; 16bit output
	#endasm
}

uint16_t _inb(uint16_t port) {
	#asm
		mov bx, sp
		mov dx, [bx+2]	; get port
		xor ax, ax		; clear AX
		in al, dx		
	#endasm
}

uint16_t _inw(uint16_t port) {
	#asm
		mov bx, sp
		mov dx, [bx+2]	; get port
		in ax, dx
	#endasm
}

uint16_t get_cs() {
	#asm
		mov ax, cs
	#endasm
}

uint16_t get_ds() {
	#asm
		mov ax, ds
	#endasm
}
uint16_t get_es() {
	#asm
		mov ax, es
	#endasm
}
uint16_t get_ss() {
	#asm
		mov ax, ss
	#endasm
}

uint16_t get_ax() {
	#asm
		nop
	#endasm
}

uint16_t get_bx() {
	#asm
		mov ax, bx
	#endasm
}

uint16_t get_cx() {
	#asm
		mov ax, cx
	#endasm
}
uint16_t get_dx() {
	#asm
		mov ax, dx
	#endasm
}
