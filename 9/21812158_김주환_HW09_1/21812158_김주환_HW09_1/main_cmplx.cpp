/* main_cmplx.cpp (1) */
/*
* * 파일명 : main_cmplx.cpp
* 목적 및 기본 기능
*	복소수의 사칙연산과 정렬
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 5월 11일
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>.
#include <stdlib.h>
#include <math.h>
#include "Cmplx.h"

void main() {
	Cmplx cmplxs[7];
	cmplxs[0] = inputCmplx();
	cmplxs[1] = inputCmplx();
	printf("cmplxs[0] = "); printCmplx(cmplxs[0]); printf("\n");
	printf("cmplxs[1] = "); printCmplx(cmplxs[1]); printf("\n");
	cmplxs[2] = cmplxAdd(cmplxs[0], cmplxs[1]);
	printf("cmplxs[2] = cmplxs[0] + cmplxs[1] = \n ");
	printCmplx(cmplxs[0]); printf(" + ");
	printCmplx(cmplxs[1]); printf(" = ");
	printCmplx(cmplxs[2]); printf("\n");
cmplxs[3] = cmplxSub(cmplxs[0], cmplxs[1]);
	printf("cmplxs[3] = cmplxs[0] - cmplxs[1] = \n ");
	printCmplx(cmplxs[0]); printf(" - ");
	printCmplx(cmplxs[1]); printf(" = ");
	printCmplx(cmplxs[3]); printf("\n");
	cmplxs[4] = cmplxMul(cmplxs[0], cmplxs[1]);
	printf("cmplxs[4] = cmplxs[0] * cmplxs[1] = \n ");
	printCmplx(cmplxs[0]); printf(" * ");
	printCmplx(cmplxs[1]); printf(" = ");
	printCmplx(cmplxs[4]); printf("\n");
	cmplxs[5] = cmplxDiv(cmplxs[0], cmplxs[1]);
	printf("cmplxs[5] = cmplxs[0] / cmplxs[1] = \n ");
	printCmplx(cmplxs[0]); printf(" / ");
	printCmplx(cmplxs[1]); printf(" = ");
	printCmplx(cmplxs[5]); printf("\n");
	cmplxs[6] = cmplxMul(cmplxs[1], cmplxs[5]);
	printf("cmplxs[6] = cmplxs[1] * cmplxs[5] = \n ");
	printCmplx(cmplxs[1]); printf(" * ");
	printCmplx(cmplxs[5]); printf(" = ");
	printCmplx(cmplxs[6]); printf("\n");
	printf("Before sorting complexs: \n");
	for (int i = 0; i < 7; i++) {
		printf("cmplxs[%d] = ", i); printCmplx(cmplxs[i]);
		printf("\n");
	}
	sortCmplx(cmplxs, 7);
	printf("Sorted complexs: \n");
	for (int i = 0; i < 7; i++) {
		printf("cmplxs[%d] = ", i); printCmplx(cmplxs[i]);
		printf("\n");
	}
}