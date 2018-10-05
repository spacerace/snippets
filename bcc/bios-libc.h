#ifndef __BLC_H__
#define __BLC_H__

#define uint8_t	unsigned char
#define uint16_t unsigned short
#define NULL ( (void *) 0)

/* IO functions */
void _outb(uint16_t port, uint16_t data);
void _outw(uint16_t port, uint16_t data);
uint16_t _inb(uint16_t port);
uint16_t _inw(uint16_t port);

/* BIOS only functions */
void put_hex8(uint8_t hex8);
void put_hex16(uint16_t hex16);
void _putc(c);
void putc_attr(uint16_t attrib, uint16_t c);
void print_str(char *s);
void inc_cursor();
void new_line();
void clrscr();
void set_cursor(uint16_t col, uint16_t row);
void _kbhit();
uint16_t _getch();
uint16_t _strlen(char * str);
uint16_t get_cursor();
void scroll();
uint16_t get_from_screen();
uint16_t int11_getconfig();
uint16_t int12_getmaxrambelow1m();
uint16_t get_cs();
uint16_t get_ds();
uint16_t get_es();
uint16_t get_ss();
uint16_t get_ax();
uint16_t get_bx();
uint16_t get_cx();
uint16_t get_dx();
char *_itoa(int i);
char *_ltoa(long val);
char *_ultoa(unsigned long val);


/* DOS only functions */
void return_to_dos();

/* BIOS+DOS functions */

#ifdef __FIRST_ARG_IN_AX__
#error "calling conventions changed, can't compile this way."
#endif

#endif // __BLC_H__
