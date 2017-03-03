#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("usage: %s input-file.bin\n", argv[0]);
		exit(-99);
	}

	int data, i, fill_bytes;
	uint8_t b;
	int count = 0;
	uint8_t mpe[4*16];
	uint16_t magic = 0x55AA;
	char filename[129];
	char outfile[6+129+4];
	FILE *f, *dst;
	struct stat attr;

	sprintf(filename, "%s", argv[1]);
	sprintf(outfile, "image_%s.mbr", filename);

	if(stat(filename, &attr)) {
		printf("error opening bootsector code!\n");
		exit(-10);
	}
	
	
	if(attr.st_size > 446) {
		printf("bootsector program code too big! maximum 446bytes, code is %ub.\n", (unsigned int)attr.st_size);
		exit(-15);
	}

	printf("in: %s (%ubytes), out: %s\n", filename, (unsigned int)attr.st_size, outfile);

	f = fopen(filename, "r");
	if(f == NULL) {
		printf("can't open %s\n", filename);
		exit(-1);
	}
	dst = fopen(outfile, "w+");
	if(dst == NULL) {
		printf("can't open %s for writing.\n", outfile);
		exit(-2);
	}

	for(i = 0; i < (4*16); i++) {
		mpe[i] = 0x00;
	}

	while((data = fgetc(f)) != EOF) {
		b = (uint8_t)data;
		putc(b, dst);
		count++;
	}
	printf(" [0x%03x-0x%03x] [%03ub] stage1 bootloader\n", 0, count-1, count);
//	printf("wrote %db stage1 bootloader 0x%03x-0x%03x\n", count, 0, count-1);
	
	fill_bytes = 512-2-64-count;
	if(fill_bytes > 0) {
		for(i = 0; i < fill_bytes; i++) {
			putc(0x00, dst);
			count++;
		}
		printf(" [0x%03x-0x%03x] [\e[96m%03ub\e[0m] unused, free space in stage1 area\n", count, count+fill_bytes, fill_bytes);
	}
	else    printf(" [-------------] [\e[31m%03ub\e[0m] no free space in stage1 area\n", 0);

	for(i = 0; i < (4*16); i++) {
		b = (uint8_t)mpe[i];
		putc(b, dst);
		count++;
	}
	printf(" [0x%03x-0x%03x] [%03ub] 4 master partition entries\n", 446, 509, 4*16);
	putc((uint8_t)(magic>>8), dst);
	putc((uint8_t)(magic&0xff), dst);
	printf(" [0x%03x-0x%03x] [%03ub] Magic\n", 510, 511, 2);

	fclose(f);
	fclose(dst);

	return 0;
}
