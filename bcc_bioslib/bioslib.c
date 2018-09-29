/*  x86 512byte C pong - real mode
 * 
 *  runs on bare metal hardware, it just uses some BIOS
 *  interrupts.
 * 
 *  (c) 2018 <stecdose@gmail.com>
 */

/* datatypes */
#define uint8_t		unsigned char
#define uint16_t 	unsigned short
#define NULL 		((void *)0)

void puts(char *str);
void putc(c);
void clrscr();
void set_cursor(uint16_t col, uint16_t row);
uint16_t getc();
int kbhit();

int main() {
	#asm
		mov ah, #0x01
		mov cx, #0x2607		// invisible cursor
		int 0x10
	#endasm
	puts("hahaha");
    
    

}

/* returns:
 *  no keystroke = 0x00
 *  keystroke    = returns AX => AH = SCANCODE, AL=ASCII */
int kbhit() {
    #asm
        mov ah, #0x01
        int 0x16
        jz nothing
        xor ax, ax
        int 0x16
        jmp outhere
nothing:
        xor ax, ax
outhere:
    #endasm
}


void puts(char *s) {
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
		mov bh, #0	    ; page
		mov cx, #1      ;number of chars
		int 0x10
	#endasm
}

void set_cursor(uint16_t col, uint16_t row) {
	#asm
		mov bx, sp
		mov dh, [bx+4]
		mov dl, [bx+2]
		xor bx, bx        ; page 0
		mov ah, #0x02     ; DH = row, DL = col
		int 0x10
	#endasm
}
