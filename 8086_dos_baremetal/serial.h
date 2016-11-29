#ifndef __SERIAL_H__
#define __SERIAL_H__

#define COM1	0x3F8
#define COM2	0x2F8
#define COM3	0x3E8
#define COM4	0x2E8

/* settings of UART driver 
 * baudrate settings are in serial.c:init_serial()
 */
#define SERIAL_PORT COM1	/* set up base address of used COM port */

/* 
 * to set up baudrate give on of these or any other divisor from 0 to
 * 65535 to serial_setbaud()
 * 
 */
#define SER_DIV_115200	1
#define SER_DIV_57600	2
#define SER_DIV_38400	3
#define SER_DIV_19200	6
#define SER_DIV_9600	12
#define SER_DIV_7200	16
#define SER_DIV_4800	24
#define SER_DIV_3600	32
#define SER_DIV_2400	48
#define SER_DIV_1800	64
#define SER_DIV_1200	96
#define SER_DIV_600		192
#define SER_DIV_300		384
#define SER_DIV_150		768
#define SER_DIV_110		1047	/* 0.026% error */
#define SER_DIV_90		1280		
#define SER_DIV_75		1536
#define SER_DIV_50		2304

#define SER_DR		0x00	/* RW data register, combined RBR+THR	*/	
#define SER_RBR		SER_DR	/* RO receiver buffer register			*/
#define SER_THR		SER_DR	/* WO transmit holding resister			*/
#define SER_IER		0x01	/* RW interrupt enable register 		*/
#define SER_DIVL	0x00	/* RW divisor low 						*/
#define SER_DIVH	0x01	/* RW divisor high 						*/
#define SER_IIR		0x02	/* RO interrupt ident              		*/
#define SER_FCR		0x02	/* WO fifo control register				*/
#define SER_LCR		0x03	/* RW line control register 			*/
#define SER_MCR		0x04	/* RW modem control register 			*/
#define SER_LSR		0x05	/* RW line status register 				*/
#define SER_MSR		0x06	/* RW modem status register 			*/
#define SER_SCR		0x07	/* RW scratch register 					*/

#define SER_BIT_DLAB	0x80

/* bits of Interupt Enable Register */
#define IER_ERBFI			0x01	/* enable rcv data avail int */
#define IER_ETBEI			0x02	/* enable transmit holding register empty int */
#define IER_ELSI			0x04	/* enable receiver line status interrupt */
#define IER_EDSSI			0x08	/* enable modem status interrupt */

/* 16750 has some special power saving modes, they are located in IER */
#define IER_16750_SLEEP		0x10	/* 16750 only */
#define IER_16750_LOWPOWER	0x20	/* 16750 only */

/* these are to apply when reading Interrupt Identification Register */ 
#define IIR_INT_PENDING		0x01	/* */
#define IIR_INT_ID0			0x02	/* */
#define IIR_INT_ID1			0x04	/* */
#define IIR_INT_ID2			0x08	/* */
#define IIR_FIFO_EN0		0x40	/* */
#define IIR_FIFO_EN1		0x80	/* */

/* these are to apply when writing FIFO Control Register */
#define FCR_FIFO_EN			0x01	/* fifo enabled */
#define FCR_RX_FIFO_RST		0x02	/* reset receiver fifo */
#define FCR_TX_FIFO_RST		0x04	/* reset transmitter fifo */
#define FCR_DMA_MODE_SEL	0x08	/* */
#define FCR_RXTRIG_LSB		0x40	/* */
#define FCR_RXTRIG_MSB		0x80	/* */

/* bits of Line Control Register (R/W) */
#define LCR_WLS0			0x01	/* word length select register 0 */
#define LCR_WLS1			0x02	/* word length select register 1 *
									 * B1 B0 len
									 * 0  0 5 Bits
									 * 0  1 6 Bits
									 * 1  0 7 Bits
									 * 1  1 8 Bits */
#define LCR_STB				0x04	/* stop bits */
#define LCR_PEN				0x08	/* parity enable */
#define LCR_EPS				0x10	/* even parity select */
#define LCR_STICK_PARITY	0x20	/* */
#define LCR_SET_BREAK		0x40	/* */
#define LCR_DLAB			0x80	/* divisor latch access bit */

/* bits of modem control register (R/W) */
#define MCR_DTR				0x01	/* data terminal ready */
#define MCR_RTS				0x02	/* ready to send */
#define MCR_OUT1			0x04	/* */
#define MCR_OUT2			0x08	/* */
#define MCR_LOOP			0x10	/* */

/* bits of Line Status Register (R/W) */
#define LSR_DR				0x01	/* data ready */
#define LSR_OE				0x02	/* overrun error */
#define LSR_PE				0x04	/* parity error */
#define LSR_FE				0x08	/* framing error */
#define LSR_BI				0x10	/* break interrupt */
#define LSR_THRE			0x20	/* transmitter holding register */
#define LSR_TEMT			0x40	/* transmitter empty */
#define LSR_ERR_RX_FIFO		0x80	/* error in receiver fifo */

/* bits of Modem Status Register */
#define MSR_DCTS			0x01	/* delta clear to send */
#define MSR_DDSR			0x02	/* delta data set ready */
#define MSR_TERI			0x04	/* trailing edge ring indicator */
#define MSR_DDCD			0x08	/* delta data carrier detect */
#define MSR_CTS				0x10	/* clear to send */
#define MSR_DSR				0x20	/* data set ready */
#define MSR_RI				0x40	/* ring indicator */
#define MSR_DCD				0x80	/* data carrier detect */

 
void init_serial();
char read_serial();
void write_serial(char a);

#endif
