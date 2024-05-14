#include <stdio.h>
#include <math.h>

int main() {
	double x = 6.0;
	double result;
	int even;
	
	result = log(x) / log(2);
	printf("result: %.2f\n", result);
	
	printf("Is pow 2: %s\n", result == (int)result ? "yes" : "no");
	
	printf("------------------\n");
	printf("%f flr:%d rem:%d\n", 1.0/2.0, 1/2, 1%2);
	
	printf("------------------\n");
	printf("%s\n", 0 ? "yes" : "no");
	
	return 0;
}