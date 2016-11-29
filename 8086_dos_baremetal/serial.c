#include "dblib.h"
#include "serial.h"

static uint8_t _serial_rxbuf[32];
static uint8_t _serial_txbuf[32];
static int _serial_rxbuf_idx;
static int _serial_txbuf_idx;

/*
 * IVT offset | INT # | IRQ # | COM PORT
 * 0x002C     | 0x0B  | 3     | COM2 / COM4
 * 0x0030     | 0x0C  | 4     | COM1 / COM3
 */
 
void serial_irq_handler() {
	
}

uint16_t serial_rxbuf_get() {
	return 0;
}

uint16_t serial_txbuf_write() {
	return 0;
}

void serial_setbaud(uint16_t divisor) {
	uint8_t divl, divh;
	
	divl = (uint8_t)(divisor&0xff);
	divh = (uint8_t)((divisor>>8)&0xff);
	
   /* set baudrate */
   _outb(SERIAL_PORT + SER_LCR, SER_BIT_DLAB);	/* to write DIVH,DIVL registers, we need DLAB set */
   _outb(SERIAL_PORT + SER_DIVL, divl);    
   _outb(SERIAL_PORT + SER_DIVH, divh);
   _outb(SERIAL_PORT + SER_LCR, 0x00);			/* disable DLAB bit */
   
   return;
}

void init_serial() {
	int i;
	
   _outb(SERIAL_PORT + SER_IER, 0x00);    	/* disable all IRQs */
   
   serial_setbaud(SER_DIV_19200);
   
   /* data format, ... */
   _outb(SERIAL_PORT + SER_LCR, (LCR_WLS0|LCR_WLS1));     	/* 8N1 */
   _outb(SERIAL_PORT + SER_FCR, 0xC7);   	/* Enable FIFO, clear them, with 14-byte threshold */
   _outb(SERIAL_PORT + SER_MCR, 0x0B);     	/* IRQs enabled, RTS/DSR set */

	/* clear buffers */
	for(i = 0; i < sizeof(_serial_rxbuf); i++) 
		_serial_rxbuf[i] = 0;
	for(i = 0; i < sizeof(_serial_txbuf); i++) 
		_serial_txbuf[i] = 0;
		
	_serial_rxbuf_idx = 0;
	_serial_txbuf_idx = 0;
   
   return;
}

char read_serial() {
	/* do a NOP, as we can't rely on empty loops not to be
	 * optimized away by the compiler */ 	
	while((_inb(SERIAL_PORT + SER_LSR) & 1) == 0) asm("nop");	
	return _inb(SERIAL_PORT);
}
 
void write_serial(char c) {
	while((_inb(SERIAL_PORT + SER_LSR) & 0x20) == 0) asm("nop");
	_outb(SERIAL_PORT, c);
	return;
}

