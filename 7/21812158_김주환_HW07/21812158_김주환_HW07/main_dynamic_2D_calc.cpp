/*
* 파일명 : main_dynammic_2D_calc.cpp
* 목적 및 기본 기능
*	2차원 배열을 동적 할당을 통해 생성하고 행렬 덧셈, 뺄셈, 곱셈, 평균을 구하는 계산
*   을 실행하고 실행창과 파일에 출력한다.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 4월 19일
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

#define MTRXINPUTDATA "input_data.txt" // 사용하는 파일 이름

int main(void) {
	FILE* fin;

	double** dma = NULL, ** dmb = NULL, ** dmc = NULL; // 사용할 2차원 배열 포인터
	int a_row_size = 0, a_col_size = 0; // 행렬 크기
	int b_row_size = 0, b_col_size = 0;
	int c_row_size = 0, c_col_size = 0;
	int temp = 0; // 행렬의 곱 연산 보조

	fin = fopen(MTRXINPUTDATA, "r"); // 파일 읽기 모드로 열기
	if (fin == NULL) {
		printf("Error in openning input.txt file !!\n");
		exit(-1);
	}

	dma = input_mtrx(fin, dma, &a_row_size, &a_col_size); // 기본 행렬
	printf("Input Matrix_A (%d x %d) : \n", a_row_size, a_col_size);
	print_mtrx(dma, a_row_size, a_col_size);
	printf("\n");

	dmb = input_mtrx(fin, dmb, &b_row_size, &b_col_size);
	printf("Input Matrix_B (%d x %d) : \n", b_row_size, b_col_size);
	print_mtrx(dmb, b_row_size, b_col_size);
	printf("\n");

	c_row_size = a_row_size;
	c_col_size = b_col_size;
	dmc = input_mtrx(fin, dmc, &c_row_size, &c_col_size); // 연산의 결과를 담을 배열 생성

	dmc = add_mtrx(dma, dmb, dmc, a_row_size, a_col_size); // 행렬 덧셈
	printf("Matrix_C (%d x %d) = Matrix_A + Matrix_B :\n", c_row_size, c_col_size);
	print_mtrx(dmc, c_row_size, c_col_size);
	printf("\n");

	dmc = sub_mtrx(dma, dmb, dmc, a_row_size, a_col_size); // 행렬 뺄셈
	printf("Matrix_D (%d x %d) = Matrix_A - Matrix_B :\n", c_row_size, c_col_size);
	print_mtrx(dmc, c_row_size, c_col_size);
	printf("\n");

	temp = c_row_size;
	dmc = multiply_mtrx(dma, dmb, dmc, c_row_size, c_col_size, temp); // 행렬 곱셈
	printf("Matrix_C (%d x %d) = Matrix_A x Matrix_B :\n", c_row_size, c_col_size);
	print_mtrx(dmc, c_row_size, c_col_size);
	printf("\n");

	delete_double_mtrx(dma, a_row_size, a_col_size); // 동적 생성한 배열 해제
	delete_double_mtrx(dmb, b_row_size, b_col_size);
	delete_double_mtrx(dmc, c_row_size, c_col_size);
	fclose(fin); // 파일 닫기
	return 0;
}