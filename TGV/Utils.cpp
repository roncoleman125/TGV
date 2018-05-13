#include <stdlib.h>

int random(int min, int max) {
	/*
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
	*/
	/*
	double scaled = (double)rand() / RAND_MAX;

	return (max - min + 1)*scaled + min;
	*/
	// See https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range/6852396
	return (rand() % (max + 1 - min)) + min;
}

float random() {
	float ran = rand() / (float)RAND_MAX;

	return ran;
}