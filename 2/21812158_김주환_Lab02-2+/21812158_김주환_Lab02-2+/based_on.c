#include <stdio.h>
#include <limits.h>

#define bit_mask 1
#define num_bits_int 33

void INT_MM_O(void);
void INT_arithematics();
void Bitwise_calc();
void printint_bits(int d);


int main(void) {
	int sel = 0;

	while (1) {
		printf("Menu (0. Quit, 1. INT_MAX_MIN_Overflow, 2. Integer Arithematics, 3. Bit-wise Operations) : ");
		scanf("%d", &sel);
		switch (sel) {
		case 0:
			break;
		case 1:
			INT_MM_O();
			break;
		case 2:
			INT_arithematics();
			break;
		case 3:
			Bitwise_calc();
			break;
		default:
			break;
		}
	}
		

	return 0;
}

void INT_MM_O(void) {
	printf("Int_max     : ");
	printint_bits(INT_MAX);
	printf("\nInt_max + 1 : ");
	printint_bits(INT_MAX + 1);
	printf("\nInt_min     : ");
	printint_bits(INT_MIN);
	printf("\nInt_min - 1 : ");
	printint_bits(INT_MIN - 1);
	printf("\n");
}

void INT_arithematics() {
	long x, y;

	printf("Input first decimal number in (0x00000000 ~ 0xFFFFFFFF) : 0x");
	scanf("%x", &x);
	printf("x = %#x = (in decimal) %d = (in octal) %o\n  = (in bits) ", x, x, x, x);
	printint_bits(x);

	printf("Input second decimal number in (0x00000000 ~ 0xFFFFFFFF) : 0x");
	scanf("%x", &y);
	printf("y = %#x = (in decimal) %d = (in octal) %o\n  = (in bits) ", y, y, y, y);
	printint_bits(y);

	printf("\n\n");

	printf("Integer ADD : %#010x + %#010x => %#010x\n      ", x, y, x + y);
	printint_bits(x);
	printf(" + ");
	printint_bits(y);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x + y);
	printf("\n");

	printf("Integer SUB : %#010x - %#010x => %#010x\n      ", x, y, x - y);
	printint_bits(x);
	printf(" - ");
	printint_bits(y);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x - y);
	printf("\n");

	printf("Integer Multipication : %#010x * %#010x => %#010x\n      ", x, y, x * y);
	printint_bits(x);
	printf(" * ");
	printint_bits(y);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x * y);
	printf("\n");

	printf("Integer Division : %#010x / %#010x => %#010x\n      ", x, y, x / y);
	printint_bits(x);
	printf(" / ");
	printint_bits(y);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x / y);
	printf("\n");

	printf("Integer Modulo : %#010x % %#010x => %#010x\n      ", x, y, x % y);
	printint_bits(x);
	printf(" % ");
	printint_bits(y);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x % y);
	printf("\n");
}

void Bitwise_calc() {
	long x, y;

	printf("Input first hexadecimal number in (0x00000000 ~ 0xFFFFFFFF) : 0x");
	scanf("%x", &x);
	printf("x = %#x = (in decimal) %d = (in octal) %o\n  = (in bits) ", x, x, x, x);
	printint_bits(x);

	printf("Input second hexadecimal number in (0x00000000 ~ 0xFFFFFFFF) : 0x");
	scanf("%x", &y);
	printf("y = %#x = (in decimal) %d = (in octal) %o\n  = (in bits) ", y, y, y, y);
	printint_bits(y);

	printf("\n\n");

	printf("Bitwise AND : %#010x & %#010x => %#010x\n      ", x, y, x & y);
	printint_bits(x);
	printf(" & ");
	printint_bits(y);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x & y);
	printf("\n");

	printf("Bitwise OR : %#010x | %#010x => %#010x\n      ", x, y, x | y);
	printint_bits(x);
	printf(" | ");
	printint_bits(y);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x | y);
	printf("\n");

	printf("Bitwise XOR : %#010x ^ %#010x => %#010x\n      ", x, y, x ^ y);
	printint_bits(x);
	printf(" ^ ");
	printint_bits(y);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x ^ y);
	printf("\n");

	printf("Bitwise Shift Left : %#010x << %#010x => %#010x\n      ", x, 1, x << 1);
	printint_bits(x);
	printf("<< ");
	printint_bits(1);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(x << 1);
	printf("\n");

	printf("Bitwise Shift Right : %#010x >> %#010x => %#010x\n      ", x, 1, x >> 1);
	printint_bits(y);
	printf(">> ");
	printint_bits(1);
	printf("-------------------------------------\n");
	printf(" = ");
	printint_bits(y >> 1);
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