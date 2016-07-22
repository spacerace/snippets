#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int main(int argc, char **argv) {
	printf("usage:\n %s <frequency>\n", argv[0]);
	if(argc < 2) return -1;
	
	uint32_t frequency = atoi(argv[1]);
	printf("calculating divl/divh for %dHz\n", frequency);
	
	uint32_t div = 1193180/frequency;
	printf("divl 0x%02x\ndivh 0x%02x\n", (uint8_t)div, (uint8_t)(div>>8));

	return 0;
}
