/*
* 파일명 : Bit_wise_calc.c
* 목적 및 기본 기능
* 1. 정수 데이터 값을 32비트 단위로 출력
* 2. 16진수 2개를 입력받고 이들 값의 8진수, 10진수, 및 2진수 값을 출력
* 3. 입력된 2개의 16진수 값의 덧셈과 뺄셈을 계산하고,
*    계산 결과값의 16진수 및 2진수 값을 각각 출력
* 4. 16진수 2개를 입력받아 &, |, ^, << 3, >> 3, ~를 각각 계산하고,
*    계산 결과 값의 16진수 및 2진수 값을 각각 출력
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 3월 10일
*/
#include <stdio.h>

#define bit_mask 0x01
#define num_bits_int 33

void printint_bits(int d);

int main(void) {
	long x, y;

	printf("Input first hexadecimal number in (0x00000000 ~ 0xFFFFFFFF) : 0x");
	scanf("%x", &x);
	printf("x = %#x = (in decimal) %d = (in octal) %o\n  = (in bits) ", x, x, x, x);
	printint_bits(x);

	printf("Input second hexadecimal number in (0x00000000 ~ 0xFFFFFFFF) : 0x");
	scanf("%x", &y);
	printf("y = %#x = (in decimal) %d = (in octal) %o\n  = (in bits) ", y, y, y, y);
	printint_bits(y);

	printf("\n");

	printf("Bitwise ADD : %#010x + %#010x => %#010x\n      ", x, y, x + y);
	printint_bits(x);
	printf("    + ");
	printint_bits(y);
	printf("    -------------------------------------\n      ");
	printint_bits(x + y);
	printf("\n");

	printf("Bitwise SUB : %#010x - %#010x => %#010x\n      ", x, y, x - y);
	printint_bits(x);
	printf("    - ");
	printint_bits(y);
	printf("    -------------------------------------\n      ");
	printint_bits(x - y);
	printf("\n");

	printf("Bitwise AND : %#010x & %#010x => %#010x\n      ", x, y, x & y);
	printint_bits(x);
	printf("    & ");
	printint_bits(y);
	printf("    -------------------------------------\n      ");
	printint_bits(x & y);
	printf("\n");

	printf("Bitwise OR : %#010x | %#010x => %#010x\n      ", x, y, x | y);
	printint_bits(x);
	printf("    | ");
	printint_bits(y);
	printf("    -------------------------------------\n      ");
	printint_bits(x | y);
	printf("\n");

	printf("Bitwise XOR : %#010x ^ %#010x => %#010x\n      ", x, y, x ^ y);
	printint_bits(x);
	printf("    ^ ");
	printint_bits(y);
	printf("    -------------------------------------\n      ");
	printint_bits(x ^ y);
	printf("\n");

	printf("Bitwise Shift Left : %#010x << 0x3 => %#010x\n      ", x, x << 3);
	printint_bits(x);
	printf("   << ");
	printint_bits(3);
	printf("    -------------------------------------\n      ");
	printint_bits(x << 3);
	printf("\n");

	printf("Bitwise Shift Right : %#010x >> 0x3 => %#010x\n      ", y, y >> 3);
	printint_bits(y);
	printf("   >> ");
	printint_bits(3);
	printf("    -------------------------------------\n      ");
	printint_bits(y >> 3);
	printf("\n");

	printf("Bitwise Shift NOT : ~%#010x => %#010x\n", y, ~y);
	printf("    ~ ");
	printint_bits(y);
	printf("    -------------------------------------\n      ");
	printint_bits(~y);
	printf("\n");

	return 0;
}

void printint_bits(long long d) {
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