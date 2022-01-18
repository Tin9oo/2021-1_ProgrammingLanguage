/*
* 파일명 : main.cpp
* 목적 및 기본 기능
*	2차원 동적 배열을 생성하고 파일의 행렬 데이터를 알맞게 입/출력 가능한지 확인하고
*	주어진 행렬의 덧셈, 뺄셈, 곱셈 연산을 실행한다.
*	Gauss-Jordan 소거법을 수행하고 이를 이용하여 역행렬을 구하고 이를 검증한다.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 5월 3일
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Mtrx.h"

const char* A2I = "Array_2D_input.txt";

int main(void) {
	FILE* fin, * fout;
	double** mA, ** mB, ** mC;
	double** mD, ** mE, ** mF;
	double** inv_mA;
	int* a_row_size, * a_col_size;
	int* b_row_size, * b_col_size;
	int* c_row_size, * c_col_size;
	int* d_row_size, * d_col_size;
	int* e_row_size, * e_col_size;
	int* f_row_size, * f_col_size;
	int* temp;
	fout = fopen("output", "w");
	if (fout == NULL) {
		printf("Error in opening output.txt file !!\n");
		exit(-1);
	}
	fout = fopen(A2I, "r");
	if (fout == NULL) {
		printf("Error in opening Array_2D_input.txt file !!\n");
		exit(-1);
	}

	// 파일로부터 행렬 데이터 불러오기
	mA = fGetMtrx(fin, a_row_size, a_col_size);
	printf("Input Matrix_A (%d x %d) : \n", a_row_size, a_col_size);
	printMtrx(mA, *a_row_size, *a_col_size);
	printf("\n");
	fprintf(fin, "Input Matrix_A (%d x %d) : \n", a_row_size, a_col_size);
	fprintMtrx(fin, mA, *a_row_size, *a_col_size);
	fprintf(fin, "\n");
	mB = fGetMtrx(fin, b_row_size, b_col_size);
	printf("Input Matrix_B (%d x %d) : \n", b_row_size, b_col_size);
	printMtrx(mB, *b_row_size, *b_col_size);
	printf("\n");
	fprintf(fin, "Input Matrix_B (%d x %d) : \n", b_row_size, b_col_size);
	fprintMtrx(fin, mB, *b_row_size, *b_col_size);
	fprintf(fin, "\n");
	mC = fGetMtrx(fin, c_row_size, c_col_size);
	printf("Input Matrix_C (%d x %d) : \n", c_row_size, c_col_size);
	printMtrx(mC, *c_row_size, *c_col_size);
	printf("\n");
	fprintf(fin, "Input Matrix_C (%d x %d) : \n", c_row_size, c_col_size);
	fprintMtrx(fin, mC, *c_row_size, *c_col_size);
	fprintf(fin, "\n");
	
	if ((a_row_size != b_row_size) || (a_col_size != b_col_size)) {
		printf("Error in input matrix dimension: row_size and/or col_size are not equal !!\n");
		fclose(fin);
		return;
	}

	// 연산
	// 덧셈
	d_row_size = a_row_size;
	d_col_size = b_col_size;
	mD = (double**)calloc(*d_row_size, sizeof(double*));
	for (int i = 0; i < *d_row_size; i++) {
		mD[i] = (double*)calloc(*d_col_size, sizeof(double));
	}
	addMatrix(mA, mB, mD, *d_row_size, *a_col_size);
	printf("Matrix_D (%d x %d) = Matrix_A + Matrix_B : \n", d_row_size, d_col_size);
	printMtrx(mD, *d_row_size, *d_col_size);
	printf("\n");
	// 뺄셈
	e_row_size = a_row_size;
	e_col_size = b_col_size;
	subtractMatrix(mA, mB, mD, *e_row_size, *e_col_size);
	printf("Matrix_E (%d x %d) = Matrix_A - Matrix_B : \n", e_row_size, e_col_size);
	printMtrx(mE, *e_row_size, *e_col_size);
	printf("\n");
	// 곱셈
	f_row_size = a_row_size;
	f_col_size = c_col_size;
	temp = a_col_size;
	multiplyMatrix(mA, mC, mF, *f_row_size, *f_col_size, *f_col_size);
	printf("Matrix_F (%d x %d) = Matrix_A x Matrix_C : \n", f_row_size, f_col_size);
	printMtrx(mC, *f_row_size, *f_col_size);
	printf("\n");
	
	inv_mA = (double**)calloc(size_N, sizeof(double*));
	for (int i = 0; i < size_N; i++) {
		inv_mA[i] = (double*)calloc(size_N, sizeof(double));
	}

	deleteDynMtrx(mA, *a_row_size, *a_col_size);
	deleteDynMtrx(mB, *b_row_size, *b_col_size);
	deleteDynMtrx(mC, *c_row_size, *c_col_size);
	deleteDynMtrx(mD, *d_row_size, *d_col_size);
	deleteDynMtrx(mE, *e_row_size, *e_col_size);
	deleteDynMtrx(mF, *f_row_size, *f_col_size);
	fclose(fin);
	fclose(fout);
}
void test_InvMtrx_GaussJordanElimination_LinearSystem(FILE* fout) {
	FILE* fin;
	double** mA, ** inv_A, ** res, ** mE;
	int size_N;
	double data;

	mA = (double**)calloc(size_N, sizeof(double*));
	inv_A = (double**)calloc(size_N, sizeof(double*));
	mE = (double**)calloc(size_N, sizeof(double*));
	res = (double**)calloc(size_N, sizeof(double*));
	for (int i = 0; i < size_N; i++) {
		mA[i] = (double*)calloc(size_N, sizeof(double));
		mE[i] = (double*)calloc(size_N, sizeof(double));
		inv_A[i] = (double*)calloc(size_N, sizeof(double));
		res[i] = (double*)calloc(size_N, sizeof(double));
	}
	for (int r = 0; r < size_N; r++)
		for (int c = 0; c < size_N; c++) {
			fscanf(fin, "%lf", &data);
			mA[r][c] = data;
		}
	for (int i = 0; i < size_N; i++) {
		fscanf(fin, "%lf", &data);
		mE[i][0] = data;
	}
	fprintf(fout, "Matrix A: \n");
	fprintMtrx(fout, mA, size_N, size_N);
	printf("Matrix A: \n");
	printMtrx(mA, size_N, size_N);
	invMtrxGaussJordanElim_FileOut(fout, mA, inv_A, size_N); // 역행렬 구하기
	fprintf(fout, " Inverse A: \n");
	fprintMtrx(fout, inv_A, size_N, size_N);
	printf(" Inverse A: \n");
	printMtrx(inv_A, size_N, size_N);
	fprintf(fout, " mE: \n");
	fprintMtrx(fout, mE, size_N, 1);
	printf(" mE: \n");
	printMtrx(mE, size_N, 1);
	res = multiplyMatrix(inv_A, mE, size_N, size_N, 1);
	fprintf(fout, " Res = Inv_A x mE: \n");
	fprintMtrx(fout, res, size_N, 1);
	printf(" Res = Inv_A x mE: \n");
	printMtrx(res, size_N, 1);
	fprintf(fout, "\n");

	// 역행렬이 맞는지 검증
	mA = multiplyMatrix(inv_A, mA, size_N, size_N, size_N);
	printf(" I = Inv_A x mA: \n");
	printMtrx(mA, size_N, size_N);

	// 동적 할당 해제
	for (int i = 0; i < size_N; i++) {
		free(mA[i]); free(mE[i]);
		free(inv_A[i]); free(res[i]);
	}
	free(mA); free(mE);
	free(inv_A); free(res);
	fclose(fin);
}