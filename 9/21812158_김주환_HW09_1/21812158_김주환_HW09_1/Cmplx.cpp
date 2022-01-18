/* Cmplx.cpp */
#ifndef CMPLX_H
#define CMPLX_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Cmplx.h"

typedef struct {
	double real;
	double imag; // imaginary
} Cmplx;
Cmplx inputCmplx() {
	Cmplx create;
	double temp1, temp2;
	printf("Input complex number (rrr.ddd iii.ddd) : ");
	scanf("%lf %lf", &temp1, &temp2);
	create.real = temp1;
	create.imag = temp2;
	return create;
}
double compareCmplx(const Cmplx c1, const Cmplx c2) {
	double mag1, mag2;
	mag1 = (double)sqrt(pow(c1.real, 2) + pow(c1.imag, 2));
	mag2 = (double)sqrt(pow(c2.real, 2) + pow(c2.imag, 2));
	return mag1 - mag2;
}
void printCmplx(const Cmplx c) {
	double mag;
	mag = (double)sqrt(pow(c.real, 2) + pow(c.imag, 2));
	if (c.imag >= 0) {
		printf("(%3.3f + j%3.3f (magnitude %3.3f))", c.real, c.imag, mag);
	}
	else {
		printf("(%3.3f - j%3.3f (magnitude %3.3f))", c.real, -c.imag, mag);
	}
}
Cmplx cmplxAdd(const Cmplx c1, const Cmplx c2) {
	Cmplx c_add;
	c_add.real = c1.real + c2.real;
	c_add.imag = c1.imag + c2.imag;
	return c_add;
}
Cmplx cmplxSub(const Cmplx c1, const Cmplx c2) {
	Cmplx c_sub;
	c_sub.real = c1.real - c2.real;
	c_sub.imag = c1.imag - c2.imag;
	return c_sub;
}
Cmplx cmplxMul(const Cmplx c1, const Cmplx c2) {
	Cmplx c_mul;
	c_mul.real = c1.real * c2.real - c1.imag * c2.imag;
	c_mul.imag = c1.real * c2.imag + c1.imag * c2.real;
	return c_mul;
}
Cmplx cmplxDiv(const Cmplx c1, const Cmplx c2) {
	Cmplx c_div;
	c_div.real = (c1.real * c2.real + c1.imag * c2.imag) / (pow(c2.real, 2) + pow(c2.imag, 2));
	c_div.imag = (c1.imag * c2.real - c1.real * c2.imag) / (pow(c2.real, 2) + pow(c2.imag, 2));
	return c_div;
}
void _sortCmplx(Cmplx cmplxs[], int start, int end) {
	int pivot = (end + start) / 2; // 가운데 값을 pivot으로 설정
	int j = start, key = end;
	Cmplx temp;

	if (end <= start) // 원소가 1개인 경우
		return;
	// pivot을 오른쪽으로 이동
	temp = cmplxs[pivot];
	cmplxs[pivot] = cmplxs[end];
	cmplxs[end] = temp;
	// 왼쪽에서 오른쪽으로 검사를 하면서 key값보다 작은값과 큰값을 서로 바꿔 준다
	for (int i = start; i < end; i++)
		if (compareCmplx(cmplxs[i], cmplxs[key]) <= 0)
		{
			temp = cmplxs[i];
			cmplxs[i] = cmplxs[j];
			cmplxs[j] = temp;
			j++;
		} // 반복문이 끝나면 j번째 인덱스 왼쪽에는 key값보다 작은값들이 집합되어 있음
	 // key값과 j번째 인데스의 값을 바꾸면 key값은 정렬 완료
	temp = cmplxs[j];
	cmplxs[j] = cmplxs[key];
	cmplxs[key] = temp;
	_sortCmplx(cmplxs, start, j - 1); // 정렬된 값 왼쪽 부분
	_sortCmplx(cmplxs, j + 1, end); // 정렬된 값 오른쪽 부분
}
void sortCmplx(Cmplx cmplxs[], int size)
{
	_sortCmplx(cmplxs, 0, size - 1);
}
#endif