/* datatypes */
#define uint8_t		unsigned char
#define uint16_t 	unsigned short
#define NULL 		((void *)0)

void _puts(char *str);
void putc(c);
void clrscr();
void set_cursor(uint16_t col, uint16_t row);
int _kbhit();
void put_hex8(uint8_t hex8);
void put_hex16(uint16_t hex16);


int main() {
    uint16_t c;

    clrscr();

    _puts("bcc bios keyboard test\r\n");

    for(;;) {
        c = _kbhit();
        if(c != 0) {
            _puts("keystroke! _kbhit() returned 0x");
            put_hex16(c);
            _puts("\r\n");
        }
    }
    
}

/* returns:
 *  no keystroke = 0x00
 *  keystroke    = returns AX => AH = SCANCODE, AL=ASCII */
int _kbhit() {
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

void _puts(char *s) {
	while(*s) {
		putc(*s);
		s++;
	}
}

void put_hex8(uint8_t hex8) {
	uint8_t save = hex8;
	
	hex8 = hex8 >> 4;
	hex8 = hex8 & 0x0f;
	hex8 += '0';
	if(hex8 > '9') hex8 += 7;
	putc(hex8);
	
	save = save & 0x0f;
	save += '0';
	if(save > '9') save += 7;
	putc(save);	
}

void put_hex16(uint16_t hex16) {
	uint8_t hex8 = (hex16 >> 8) & 0xff;
	put_hex8(hex8);
	
	hex8 = hex16 & 0xff;
	put_hex8(hex8);
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

