#include <stdio.h>

void calc(double a, double b);

int main_cd(void) {
	double a, b;

	printf("Input double data: ");
	scanf("%lf %lf", &a, &b);

	calc(a, b);

	return 0;
}

void calc(double a, double b) {
	printf("\n%.2lf + %.2lf = %.2lf\n", a, b, a + b);
	printf("%.2lf - %.2lf = %.2lf\n", a, b, a - b);
	printf("%.2lf * %.2lf = %.2lf\n", a, b, a * b);
	printf("%.2lf / %.2lf = %.2lf\n", a, b, a / b);
}