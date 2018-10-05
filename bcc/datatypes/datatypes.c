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
char *_ultoa(unsigned long val);
char *_ltoa(long val);

int main() {
	long s_uc, s_sc, s_ui, s_si, s_ul, s_sl;
	
	unsigned char uc;
	signed   char sc; 
	unsigned int  ui;
	signed   int  si;
	unsigned long ul;
	signed   long sl;
	
	
	s_uc = sizeof(uc);
	s_sc = sizeof(sc);
	s_ui = sizeof(ui);
	s_si = sizeof(si);
	s_ul = sizeof(ul);
	s_sl = sizeof(sl);
	
	print_str("unsigned char ");
	print_str(_ltoa(s_uc));
	print_str(" bytes.\r\n");
	
	print_str("signed char ");
	print_str(_ltoa(s_sc));
	print_str(" bytes.\r\n");
	
	print_str("unsigned int ");
	print_str(_ltoa(s_ui));
	print_str(" bytes.\r\n");
	
	print_str("signed int ");
	print_str(_ltoa(s_si));
	print_str(" bytes.\r\n");
	
	print_str("unsigned long ");
	print_str(_ltoa(s_ul));
	print_str(" bytes.\r\n");
	
	print_str("signed long ");
	print_str(_ltoa(s_sl));
	print_str(" bytes.\r\n");
	
	
		
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
