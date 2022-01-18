/*
* 파일명 : decimal_reverse.c
* 목적 및 기본 기능 : 최대 10자리수이내의 10진수를 입력 받고,
*                     그 10진수 숫자를 역순으로 출력
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 3월 10일
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