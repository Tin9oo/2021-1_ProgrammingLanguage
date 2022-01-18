#include <stdio.h>
#include <limits.h>

#define bit_mask 1
#define num_bits_int 33

void printint_bits(int d);

int main(void) {
	long x, y;

	printf("Input first number in : ");
	scanf("%08d", &x);
	printint_bits(x);
	printf("\n");

	printf("Input second number in : ");
	scanf("%08d", &y);
	printint_bits(y);

	printf("\n\n");

	printf("Bitwise AND\n   ");
	printint_bits(x);
	printf(" & ");
	printint_bits(y);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x & y);
	printf("\n");

	printf("Bitwise OR\n   ");
	printint_bits(x);
	printf(" | ");
	printint_bits(y);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x | y);
	printf("\n");

	printf("Bitwise XOR\n   ");
	printint_bits(x);
	printf(" ^ ");
	printint_bits(y);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x ^ y);
	printf("\n");

	printf("Bitwise Shift Left\n   ");
	printint_bits(x);
	printf("<< ");
	printint_bits(1);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x << 1);
	printf("\n");

	printf("Bitwise Shift Right\n   ");
	printint_bits(y);
	printf(">> ");
	printint_bits(1);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(y >> 1);
	printf("\n\n====================\n====================\n\n");

	int num = 0;
	printf("Input number : ");
	scanf("%d", &num);
	printint_bits(num);
	printf("\n1) ");
	printint_bits(~num);
	printf("\n2) ");
	printint_bits(~num + 1);
	printf("\nResult : %d", ~num + 1);
	printf("\n\n====================\n====================\n\n");

	printf("Int_max     : ");
	printint_bits(INT_MAX);
	printf("\nInt_max + 1 : ");
	printint_bits(INT_MAX + 1);
	printf("\nInt_min     : ");
	printint_bits(INT_MIN);
	printf("\nInt_min - 1 : ");
	printint_bits(INT_MIN - 1);
	printf("\n");

	return 0;
}

void printint_bits(long d) {
	unsigned long l1, l2, msk;
	int n = num_bits_int - 1;

	while (--n >= 0) {
		msk = bit_mask << n;
		l1 = d & msk;
		l2 = l1 >> n;
		printf("%d", l2);
		if ((n % 8) == 0) {
			printf(" ");
		}
	}
	printf("\n");
}