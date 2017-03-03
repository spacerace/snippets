#ifndef __IO_PORT_EX_H__
#define __IO_PORT_EX_H__

#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <asm/io.h>

#define SUCCESS		0

#define DEVICE_NAME	"io-port-ex"	/* Dev name as it appears in /proc/devices   */
#define BUF_LEN 	350		/* length of the receive/send buffer, max 192 byte = 191 chars + trailing zero */
#define DRIVER_AUTHOR	"2013 Nils Stec \"krumeltee\" <nils.stec@gmail.com>"
#define DRIVER_DESC	"example on how to use x86 io ports"

static int device_open(struct inode *inode, struct file *file); 
static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t * offset);

#define LPT_DEFAULT_BASE	0x378
#define LPT_DATA	lpt_addr
#define LPT_STATUS	lpt_addr+1
#define LPT_CONTROL	lpt_addr+2
#define LPT_LENGTH	3

#define STATUS_S2_IRQ		0x04 
#define STATUS_S3_nERROR	0x08
#define STATUS_S4_SELECT	0x10
#define STATUS_S5_PAPER_END	0x20
#define STATUS_S6_nACK		0x40
#define STATUS_S7_BUSY		0x80

#define CONTROL_C0_nSTROBE	0x01
#define CONTROL_C1_nAUTOLF	0x02
#define CONTROL_C2_nINIT	0x04
#define CONTROL_C3_nSELECTIN	0x08
#define CONTROL_C4_IRQACK	0x10
#define CONTROL_C5_BIDI		0x20

#endif
