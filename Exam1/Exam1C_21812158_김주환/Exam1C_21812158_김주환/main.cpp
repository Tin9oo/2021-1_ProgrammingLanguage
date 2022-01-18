/*
* 파일명 : main.c
* 목적 및 기본 기능
*	행렬을 파일로부터 입력받고 덧셈, 뺄셈, 곱셈 계산 후 출력한다.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 4월 3일
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Mtrx.h"

int main(void) {
	double A[SIZE][SIZE] = { 0 };
	double B[SIZE][SIZE] = { 0 };
	double C[SIZE][SIZE] = { 0 };
	double D[SIZE][SIZE] = { 0 };
	double E[SIZE][SIZE] = { 0 };

	FILE* fin;

	fin = fopen("input_data.txt", "r");

	inputMtrx(fin, A);
	printf("Mtrx A :\n");
	printMtrx(A, SIZE);
	inputMtrx(fin, B);
	printf("Mtrx B :\n");
	printMtrx(B, SIZE);
	fclose(fin);

	printf("Mtrx C = A + B :\n");
	addMtrx(A, B, C, SIZE);
	printf("Mtrx D = A - B :\n");
	subMtrx(A, B, D, SIZE);
	printf("Mtrx E = A * B :\n");
	mulMtrx(A, B, E, SIZE);

	return 0;
}