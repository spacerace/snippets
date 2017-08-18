#include <stdio.h>

int main() {
	int test = 0;

	printf("0x%08x\n", test);
	test = !test;
	printf("0x%08x\n", test);
	test = !test;
	printf("0x%08x\n", test);
}
