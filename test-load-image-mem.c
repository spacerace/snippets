#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "6502-test.h"

#define E_GENERAL	-1
#define E_OUTOFMEM 	-2

int load_image(uint16_t offset, uint32_t size, uint8_t *data) {
//  	if((offset + size) > 0xffff) {
//  		return E_OUTOFMEM;
//  	}
 	
 	uint32_t i; 
	
	for(i = 0; i < size; i++) {
		printf("putting $%02x to $%04x\n", data[i], offset+i);
	}
	
	return 0;
}



int main() {
	load_image(0x0000, sizeof(test65), test65);
	
	return 0;
	
}