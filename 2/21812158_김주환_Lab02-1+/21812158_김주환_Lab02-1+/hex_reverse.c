#include <stdio.h>

int main(void) {
	long num = 0;
	int buf = 0;

	printf("Input positive hexadecimal number (upto 10 digits) : ");
	scanf("%x", &num);

	printf("Digits in revers order : ");
	while (num > 0) {
		buf = num % 16;
		num /= 16;
		printf("%x ", buf);
	}

	return 0;
}