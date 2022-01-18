/*
* 파일명 : main_Matrix_Operations.cpp
* 목적 및 기본 기능
*	주어진 행렬에 기본 연산을 실행
*	역행렬을 구하고 검증
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 5월 3일
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

void main() {
	FILE* fin_ABC, * fout;
	const char* input_file_ABC = "mtrx_AB_6x7_C_7x6.txt"; // 파일 이름
	const char* output_file = "mtrx_operations_results.txt";
	double** mA, ** mB, ** mC, ** mD, ** mE, ** mF, ** inv_mF, ** mI;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	int c_row_size, c_col_size;
	int d_row_size, d_col_size;
	int e_row_size, e_col_size, k_size;
	int f_row_size, f_col_size;
	fin_ABC = fopen(input_file_ABC, "r"); // 입력받을 파일 열기
	if (fin_ABC == NULL) {
		printf("Error in opening input data file (%s) !!", input_file_ABC);
		exit;
	}
	fout = fopen(output_file, "w"); // 입력할 파일 열기
	if (fout == NULL) {
		printf("Error in opening output data file (%s) !!", output_file);
		exit;
	}
	mA = fGetMtrx(fin_ABC, &a_row_size, &a_col_size); // 기본 배열 읽고 출력
	printMtrx((const char*)"mA", mA, a_row_size, a_col_size);
	fprintMtrx(fout, (const char*)"mA", mA, a_row_size, a_col_size);
	mB = fGetMtrx(fin_ABC, &b_row_size, &b_col_size);
	printMtrx((const char*)"mB", mB, b_row_size, b_col_size);
	fprintMtrx(fout, (const char*)"mB", mB, b_row_size, b_col_size);
	mC = fGetMtrx(fin_ABC, &c_row_size, &c_col_size);
	printMtrx((const char*)"mC", mC, c_row_size, c_col_size);
	fprintMtrx(fout, (const char*)"mC", mC, c_row_size, c_col_size);
	d_row_size = a_row_size;
	d_col_size = b_col_size;
	mD = addMtrx(mA, mB, a_row_size, a_col_size); // 덧셈
	printMtrx((const char*)"mC", mC, c_row_size, c_col_size);
	fprintMtrx(fout, (const char*)"mC", mC, c_row_size, c_col_size);
	e_row_size = a_row_size;
	e_col_size = b_col_size;
	mE = subtractMtrx(mA, mB, e_row_size, e_col_size); // 뺄셈
	printMtrx((const char*)"mE = mA - mB", mE, e_row_size, e_col_size);
	fprintMtrx(fout, (const char*)"mE = mA - mB", mE, e_row_size, e_col_size);
	f_row_size = a_row_size;
	f_col_size = c_col_size;
	k_size = a_col_size;
	mF = multiplyMtrx(mA, mC, f_row_size, k_size, f_col_size); // 곱셈
	printMtrx((const char*)"mF = mA * mC", mF, f_row_size, f_col_size);
	fprintMtrx(fout, (const char*)"mF = mA * mC", mF, f_row_size, f_col_size);
	inv_mF = inverseMtrx(mF, f_row_size); // 역행렬
	printMtrx((const char*)"inv_mF", inv_mF, f_row_size, f_col_size);
	fprintMtrx(fout, (const char*)"inv_mF", inv_mF, f_row_size, f_col_size);
	mI = multiplyMtrx(mF, inv_mF, f_row_size, f_col_size, f_col_size); // 검증
	printMtrx((const char*)"mI = mF * inv_mF", mI, f_row_size, f_col_size);
	fprintMtrx(fout, (const char*)"mI = mF * inv_mF", mI, f_row_size, f_col_size);
	fclose(fin_ABC);
	fclose(fout);
}