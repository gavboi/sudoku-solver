#include <math.h>
#include "params.h"

int g_size = 9;
int g_spaced_flag = 0;
int g_verbose_flag = 0;

int setSize(int value) {
	if (value <= 0) {
		return 1;
	}
	double square_test = sqrt(value);
	if (square_test != (int)square_test) {
		return 2;
	}
	g_size = value;
	return 0;
}

int getSize() {
	return g_size;
}

int setSpaced(int flag) {
	g_spaced_flag = ((flag != 0) ? 1 : 0);
	return 0;
}

int getSpaced() {
	return g_spaced_flag;
}

int setVerbose(int flag) {
	g_verbose_flag = ((flag != 0) ? 1 : 0);
	return 0;
}

int getVerbose() {
	return g_verbose_flag;
}
