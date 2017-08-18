#include <stdio.h>

int f0(char *arg) {
	printf("0:%s\n", arg);
	return 1;
}

int f1(char *arg) {
	printf("1:%s\n", arg);
	return 4;
}

int (*fptr)(char *arg);

int main() {
	fptr = f0;
	printf("%d\n", fptr("haha"));

	fptr = f1;
	printf("%d\n", fptr("hehe"));

	return 0;
}

