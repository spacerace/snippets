#include <stdio.h>
#include <time.h>


int main() {
	srand(time(NULL));
	while(1) printf("%d\r\n", rand()%240);

	return 0;

}
