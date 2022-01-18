/*
* 파일명 : main.c
* 목적 및 기본 기능
*
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 4월 3일
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Bit_Operation.h"



int main(void) {
	const char* bitOp_sign[] = { "&", "|", "^", "~", "<<", ">>" };

	int x, y;

	printf("Input hexadecimal number in (0x00000000 ~ 0xFFFFFFFF) : ");
	scanf("0x%X 0x%X", &x, &y);
	printf("x = %#0X = (in decimal) %d = (in bits) ", x, x);
	printint_bits(x);
	printf("y = %#0X = (in decimal) %d = (in bits) ", y, y);
	printint_bits(y);

	printf("\n\n");

	printIntOper_Bits(BIT_AND, x, y);
	printIntOper_Bits(BIT_OR, x, y);
	printIntOper_Bits(BIT_XOR, x, y);
	printIntOper_Bits(SHIFT_LEFT, x, 3);
	printIntOper_Bits(SHIFT_RIGHT, x, 3);
	printIntOper_Bits(SHIFT_RIGHT, y, 3);

	return 0;
}