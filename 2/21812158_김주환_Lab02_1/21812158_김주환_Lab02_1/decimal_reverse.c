/*
* ���ϸ� : decimal_reverse.c
* ���� �� �⺻ ��� : �ִ� 10�ڸ����̳��� 10������ �Է� �ް�,
*                     �� 10���� ���ڸ� �������� ���
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 3�� 10��
*/
#include <stdio.h>

int main(void) {
	long num = 0;
	int buf = 0;

	printf("Input positive decimal number (upto 10 digits) : ");
	scanf("%d", &num);

	printf("Digits in revers order : ");
	while (num > 0) {
		buf = num % 10;
		num /= 10;
		printf("%d ", buf);
	}

	return 0;
}