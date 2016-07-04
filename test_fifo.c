#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t fifo_data[256];
uint32_t fifo_entries;

void fifo_putc(uint8_t data);
uint8_t fifo_getc();
uint32_t fifo_lock;

int main() {
	fifo_entries = 0;
	fifo_lock = 0;

	fifo_putc('A');
	fifo_putc('B');
	fifo_putc('C');
	fifo_putc('D');
	fifo_putc('E');
	fifo_putc('\0');
	printf("'%s'\n", fifo_data);

	printf("'%c'\n", fifo_getc());
	printf("'%s'\n", fifo_data);
	fifo_entries--;
	fifo_putc('f');
	fifo_putc('\0');
	printf("'%s'\n", fifo_data);

	return;
}

void fifo_putc(uint8_t data) {
	while(fifo_lock);
	fifo_lock = 1;

	while(fifo_entries >= (sizeof(fifo_data)));

	fifo_entries++;
	fifo_data[fifo_entries-1] = data;

	fifo_lock = 0;
}

uint8_t fifo_getc() {
	uint8_t ret;
	uint32_t i;
	
	if (fifo_entries == 0) return 0;

	while(fifo_lock);
	fifo_lock = 1;

	ret = fifo_data[0];
	for(i = 0; i < fifo_entries; i++) {
		fifo_data[i] = fifo_data[i+1];
	}
	fifo_entries--;

	fifo_lock = 0;
	
	return ret;
}

