/* 
 * io-port-ex.c
 * 
 * a simple example which shows how to use IO ports on the x86 platform.
 * 
 * * LAST CHANGE: 21. march 2013, Nils Stec
 * 
 *  Authors:    Nils Stec, "krumeltee", <nils.stec@gmail.com>, (c) 2013
 *              some module parts are by LKMPG                             - taken from version "2007-05-18 ver 2.6.4"
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <linux/ioport.h>

#include "io-port-ex.h"
  

/* command interface WRITE description:
 *
 * register=value
 *
 * where register is:
 *
 * 0 = human readable (0 for non-human-readable-output)
 * 1 = lpt_addr
 * 2 = lpt_data
 * 3 = lpt_control
 *
 */

uint16_t lpt_addr = LPT_DEFAULT_BASE;
int human_readable = 1;
static int Major;		/* Major number assigned to our device driver */
static int Device_Open = 0;	/* Is device open? */
static char msg[BUF_LEN];	/* The msg the device will give when asked */
static char *msg_Ptr;
static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

/*  Called when a process tries to open the device file 
 *
 *  this function reads out lpt port, parses it and puts it into userspace via device_read()
 *
 *  */
static int device_open(struct inode *inode, struct file *file) {
	uint8_t lpt_data;
	uint8_t lpt_control;
	uint8_t lpt_status;

	if(Device_Open) return -EBUSY;
	Device_Open++;
	
	lpt_data = inb(LPT_DATA);
	lpt_control = inb(LPT_CONTROL);
	lpt_status = inb(LPT_STATUS);
	
	if(human_readable) {
		sprintf(msg, "lpt port: 0x%x\n", lpt_addr);
		sprintf(msg, \
		"%slpt: data->0x%02x\nlpt: control->0x%02x\nlpt: status->0x%02x\n", msg, lpt_data, lpt_control, lpt_status);
		sprintf(msg, \
		"%sLPT STATUS:\n S2 IRQ: %d\n S3 #ERROR: %d\n S4 SELECT: %d\n S5 PAPER END: %d\n S6 #ACK: %d\n S7 BUSY: %d\n", \
				msg, \
				(lpt_status&STATUS_S2_IRQ)>>2, \
				(lpt_status&STATUS_S3_nERROR)>>3, \
				(lpt_status&STATUS_S4_SELECT)>>4, \
				(lpt_status&STATUS_S5_PAPER_END)>>5, \
				(lpt_status&STATUS_S6_nACK)>>6, \
				(lpt_status&STATUS_S7_BUSY)>>7
			);
		sprintf(msg, \
		"%sLPT CONTROL:\n C0 nSTROBE: %d\n C1 nAUTOLF: %d\n C2 nINIT: %d\n C3 nSELECTIN: %d\n C4 IRQACK: %d\n C5 BIDI: %d\n", \
				msg, \
				(lpt_control&CONTROL_C0_nSTROBE), \
				(lpt_control&CONTROL_C1_nAUTOLF)>>1, \
				(lpt_control&CONTROL_C2_nINIT)>>2, \
				(lpt_control&CONTROL_C3_nSELECTIN)>>3, \
				(lpt_control&CONTROL_C4_IRQACK)>>4, \
				(lpt_control&CONTROL_C5_BIDI)>>5
		       );
	} else {
		sprintf(msg, "%x,%x,%x", lpt_data, lpt_control, lpt_status);
	}
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);
	return SUCCESS;
}

static void set_base_addr(uint16_t addr) {
	lpt_addr = addr;
	return;
}

static void write_lpt(uint8_t lpt_data, uint8_t lpt_control, uint8_t lpt_status) {
	outb(lpt_data, LPT_DATA);
	outb(lpt_control, LPT_CONTROL);
	outb(lpt_status, LPT_STATUS);
	return;
}

static int parse_input(char *str) {
	if(strlen(str) < 3) {
		return -1;
	}
	if(str[1] != '=') {
		return -1;
	}
	
	/* ex: 0=1 */
	if((strlen(str) == 3) && (str[0] == '0')) {	// change human readable bit
		if(str[2] == '0') human_readable = 0;
		else human_readable = 1;
		return 0;
	}

	/* ex: 2=ff / 3=ff */
	if((strlen(str) == 4)) {
		if(str[0] == '2') {	// change data register
			return 0;
		}
		if(str[0] == '3') {	// change control register
			return 0;
		}
	}

	/* ex: 1=378 */
	if(strlen(str) == 5) {
		if(str[0] == '1') {	// change lpt address
			return 0;
		}
	}
	return -1;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off) {
	char message_from_user[BUF_LEN];
	
	if(copy_from_user(message_from_user, buff, (len < BUF_LEN) ? len : BUF_LEN)) return -EINVAL;
	message_from_user[4] = '\0';
	
	return len;
}


/** called when module loaded */
int init_module_io_port_ex(void) {
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if (Major < 0) {
		printk(KERN_ALERT "[io-port-ex] registering char device failed with %d\n", Major);
		return Major;
	}

	if(request_region(lpt_addr, LPT_LENGTH, "IO PORT EXAMPLE ON LPT1") == NULL) {
		printk(KERN_ALERT "[io-port-ex] couldn't claim IO port range from 0x%x to 0x%x!\n", lpt_addr, lpt_addr+LPT_LENGTH);
		unregister_chrdev(Major, DEVICE_NAME);
		return -EBUSY;
	} 

	printk(KERN_INFO "[io-port-ex] IO PORT EXAMPLE ON LPT1 successfully loaded, claimed ports from 0x%x to 0x%x.\n", lpt_addr, lpt_addr+LPT_LENGTH);
	printk(KERN_INFO "[io-port-ex] now you need to create a device node with  'mknod /dev/%s c %d 0'\n", DEVICE_NAME, Major);
	
	return SUCCESS;
}

/** called when module unloaded */
void cleanup_module_io_port_ex(void) {
	release_region(lpt_addr, LPT_LENGTH);
	unregister_chrdev(Major, DEVICE_NAME);
	printk(KERN_INFO "[io-port-ex] DRIVER UNLOADED\n");
}

/* Called when a process closes the device file. */
static int device_release(struct inode *inode, struct file *file) {
	Device_Open--;		/* We're now ready for our next caller */
				/* Decrement the usage count, or else once you opened the file, you'll never get get rid of the module. */
	module_put(THIS_MODULE);
	return 0;
}

/* Called when a process, which already opened the dev file, attempts to read from it. */
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t * offset) {
	int bytes_read = 0;
	
	if(*msg_Ptr == 0) return 0;
	
	while(length && *msg_Ptr) {
		put_user(*(msg_Ptr++), buffer++);
		length--;
		bytes_read++;
	}
	
	return bytes_read;
}

module_init(init_module_io_port_ex);
module_exit(cleanup_module_io_port_ex);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("io-ports");
