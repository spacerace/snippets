#include <stdio.h>
#include <math.h>

int main() {
	
	double s;

	double x;

	for(x = 0; x < 60; x += 0.25) {
		s = sin(x);
		printf("x = %03d  sin = %f\n", x, s);
	}


	return 0;
}
