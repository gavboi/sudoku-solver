#include <stdio.h>
#include <math.h>

int main() {
	double x = 6.0;
	double result;
	int even;
	
	result = log(x) / log(2);
	printf("result: %.2f\n", result);
	
	printf("Is pow 2: %s\n", result == (int)result ? "yes" : "no");
	
	return 0;
}