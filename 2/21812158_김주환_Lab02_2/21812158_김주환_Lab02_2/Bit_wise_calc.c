/*
* ���ϸ� : Bit_wise_calc.c
* ���� �� �⺻ ���
* 1. ���� ������ ���� 32��Ʈ ������ ���
* 2. 16���� 2���� �Է¹ް� �̵� ���� 8����, 10����, �� 2���� ���� ���
* 3. �Էµ� 2���� 16���� ���� ������ ������ ����ϰ�,
*    ��� ������� 16���� �� 2���� ���� ���� ���
* 4. 16���� 2���� �Է¹޾� &, |, ^, << 3, >> 3, ~�� ���� ����ϰ�,
*    ��� ��� ���� 16���� �� 2���� ���� ���� ���
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 3�� 10��
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