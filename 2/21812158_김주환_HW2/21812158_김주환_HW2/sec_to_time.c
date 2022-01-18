#include <stdio.h>

int main_stt(void) {
	int input;
	int hour, min, sec;

	printf("Input time : ");
	scanf("%d", &input);
	printf("%d sec => ", input);
	hour = input / 3600;
	input %= 3600;
	min = input / 60;
	input %= 60;
	sec = input;

	printf("%d hour %d min %d sec", hour, min, sec);

	return 0;
}