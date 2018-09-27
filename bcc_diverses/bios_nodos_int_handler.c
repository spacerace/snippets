/*
 * 
 */
#define uint8_t	unsigned char
#define uint16_t unsigned short
#define NULL ( (void *) 0)
void _putc(c);
void print_str(char *s);
void put_hex8(uint8_t hex8);
void put_hex16(uint16_t hex16);
uint16_t get_cs();
uint16_t get_mem(uint16_t seg, uint16_t off);
void install_ivt_entry(uint8_t int_n, uint16_t segment, uint16_t offset);
void set_mem(uint16_t seg, uint16_t off, uint16_t data);
void print_addr(uint16_t seg, uint16_t off);
char *_ltoa(long val);
char *_ultoa(unsigned long val);
void print_ivt_entry(uint8_t int_n);
void int64h_handler();

static int count;

int main() {
	int int_n;
	
	count = '0';

	print_str("my CS=0x"); 
	put_hex16(get_cs());
	print_str("\r\n");

	print_ivt_entry(0x64);			// print before change
	print_str("\r\n");
	
	install_ivt_entry(0x64, get_cs(), int64h_handler);

	print_ivt_entry(0x64);			// after change
	print_str("\r\n");

	#asm
		int #0x64
		int #0x64
		int #0x64
	#endasm
	
}

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

void install_ivt_entry(uint8_t int_n, uint16_t segment, uint16_t offset) {
	set_mem(0, ((int_n*4)+2), segment);
	set_mem(0, (int_n*4), offset);
}

void print_ivt_entry(uint8_t int_n) {
	put_hex8(int_n);
	print_str(": ");
	print_addr(get_mem(0, ((int_n*4)+2)), get_mem(0, (int_n*4)));
	
}

void print_addr(uint16_t seg, uint16_t off) {
	put_hex16(seg);
	_putc(':');
	put_hex16(off);
}

uint16_t get_mem(uint16_t seg, uint16_t off) {
	#asm
		mov bx, sp
		mov es, [bx+2]	; seg
		mov	bx, [bx+4]	; off
		seg	es
		mov	ax, [bx]
	
	
	#endasm
}

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

uint16_t get_cs() {
	#asm
		push cs
		pop ax
	#endasm
}


void print_str(char *s) {
	while(*s) {
		_putc(*s);
		s++;
	}
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

static char buf[12];

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

