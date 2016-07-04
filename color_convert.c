#include <stdio.h>
#include <inttypes.h>

int main(int argc, char **argv) {
	uint8_t red = atoi(argv[1]);
	uint8_t green = atoi(argv[2]);
	uint8_t blue = atoi(argv[3]);

    	unsigned short  b =   (blue  >> 3) & 0x001f;
	unsigned short  g = ( (green >> 2) & 0x003f ) << 6;
	unsigned short  r = ( (red   >> 3) & 0x001f ) << 11;

	uint16_t rgb = (unsigned short int) (r | g | b);


	printf("%04x\n", rgb);

	return 0;
}
