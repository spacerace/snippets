#include <stdio.h>
#include <string.h>

int main() {
	char c[4] = "abc";
	
	c[3] = 0;

	printf("str='%s' len=%d\n", c, strlen(c));
}
