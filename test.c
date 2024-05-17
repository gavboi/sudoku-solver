#include <stdio.h>
#include <math.h>

int main() {
	double x = 8.0;
	double result;
	int even;
	
	result = log(x) / log(2);
	printf("result: %.2f\n", result);
	
	printf("Is pow 2: %s\n", result == (int)result ? "yes" : "no");
	
	printf("------------------\n");
	printf("%f flr:%d rem:%d\n", 1.0/2.0, 1/2, 1%2);
	
	printf("------------------\n");
	printf("%s\n", 0 ? "yes" : "no");
	
	printf("------------------\n");
	printf("%d\n", 1 << 2);
	
	printf("------------------\n");
	printf("bit flip: %d %d\n", 13, (13 ^ 15));
	
	printf("------------------\n");
	result = log(x) / log(2);
	printf("%f %d\n", result, (int)result);
	
	printf("------------------\n");
	for (int i = 0; i < 3; i++) {
		printf("%d %d\n", 15 >> i, (15 >> i) & 1);
		if (i == 1) {continue;}
		printf("*");
	}
	
	return 0;
}