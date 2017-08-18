#include <linux/ppdev.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
	int pp;

	pp = open("/dev/parport0", O_RDWR);
	ioctl(pp, PPCLAIM, NULL);

	unsigned char data_reg;

	ioctl(pp, PPRDATA, &data_reg);


	printf("data now 0x%02x\n", data_reg);
	data_reg = 0xff;

	ioctl(pp, PPWDATA, &data_reg);

	ioctl(pp, PPRELEASE, NULL);
	close(pp);

	exit(0);

}
