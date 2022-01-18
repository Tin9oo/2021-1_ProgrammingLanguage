#ifndef BO
#define BO

#include <stdio.h>

#define GET_BIT(w, k) (((w) >> (k)) & 0x01)

#define num_bits_int 33

enum Operater { BIT_AND = 1, BIT_OR, BIT_XOR, BIT_NOR, SHIFT_LEFT, SHIFT_RIGHT };

void printint_bits(long d) {
	unsigned long l;
	int n = num_bits_int - 1;

	while (--n >= 0) {
		l = GET_BIT(d, n);
		printf("%d", l);
		if ((n % 8) == 0) {
			printf(" ");
		}
	}
	printf("\n");
}
void printIntOper_Bits(enum Operater bop, int x, int y) {
	switch (bop) {
	case 1:
		printf("Bitwise AND : %#010x & %#010x => %#010x\n      ", x, y, x & y);
		printint_bits(x);
		printf(" & ");
		printint_bits(y);
		printf("-------------------------------------\n");
		printf(" = ");
		printint_bits(x & y);
		printf("\n");
		break;
	case 2:
		printf("Bitwise OR : %#010x | %#010x => %#010x\n      ", x, y, x | y);
		printint_bits(x);
		printf(" | ");
		printint_bits(y);
		printf("-------------------------------------\n");
		printf(" = ");
		printint_bits(x | y);
		printf("\n");
		break;
	case 3:
		printf("Bitwise XOR : %#010x ^ %#010x => %#010x\n      ", x, y, x ^ y);
		printint_bits(x);
		printf(" ^ ");
		printint_bits(y);
		printf("-------------------------------------\n");
		printf(" = ");
		printint_bits(x ^ y);
		printf("\n");
		break;
	case 4:
		break;
	case 5:
		printf("Bitwise Shift Left : %#010x << %#010x => %#010x\n      ", x, 1, x << 1);
		printint_bits(x);
		printf("<< ");
		printint_bits(y);
		printf("-------------------------------------\n");
		printf(" = ");
		printint_bits(x << y);
		printf("\n");
		break;
	case 6:
		printf("Bitwise Shift Right : %#010x >> %#010x => %#010x\n      ", x, 1, x >> 1);
		printint_bits(x);
		printf(">> ");
		printint_bits(y);
		printf("-------------------------------------\n");
		printf(" = ");
		printint_bits(x >> y);
		break;
	}
}
#endif