/*
* 파일명 : main.cpp
* 목적 및 기본 기능
*	주어진 회로를 키르히호프 법칙을 사용하여 첨가행렬로 구성하고
*	가우스-조단 소거법을 통해 해를 구한다.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 5월 3일
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Matrix.h"
#include "GaussJordan.h"
const char* augMtrx_file = "ElectronicCircuit_B_5x6.txt";
int main(void) {
	FILE* fin, * fout;
	int size_N, row_size, col_size;
	double** solution;
	double** augMtrx = NULL;
	double** augtemp = NULL;
	double** inv_dm, **mE;
	int i, j, solExist = 1, error = 0;
	double d;
	fin = fopen(augMtrx_file, "r");
	if (fin == NULL) {
		printf("Error in opening input.txt file (%s)!!\n", augMtrx_file);
		exit(-1);
	}
	fout = fopen("Output.txt", "w");
	if (fout == NULL) {
		printf("Error in creation of output.txt file !!\n");
		exit(-1);
	}
	fscanf(fin, "%d", &size_N);
	augMtrx = fGetAugMtrx(fin, size_N);
	fprintMtrx(fout, "Augmented Matrix", augMtrx, size_N, size_N + 1);
	printMtrx("Augmented Matrix", augMtrx, size_N, size_N + 1);
	solution = (double**)calloc(size_N, sizeof(double*));
	mE = (double**)calloc(size_N, sizeof(double*));
	augtemp = (double**)calloc(size_N, sizeof(double*));
	for (int i = 0; i < size_N; i++) {
		solution[i] = (double*)calloc(size_N, sizeof(double));
		mE[i] = (double*)calloc(size_N, sizeof(double));
		augtemp[i] = (double*)calloc(size_N, sizeof(double));
	}
	for (int i = 0; i < size_N; i++) {
		for (int j = 0; j < size_N + 1; j++) {
			if (j == size_N) {
				mE[i][0] = augMtrx[i][j];
			}
			else {
				augtemp[i][j] = augMtrx[i][j];
			}
		}
	}
	diagonalize_FileOut(fout, (double**)augMtrx, size_N, &solExist);
	if (solExist) {
		fprintf(fout, "The solution of the given linear system:\n");
		for (i = 0; i < size_N; i++) {
			solution[i][0] = augMtrx[i][size_N];
			fprintf(fout, " x[%d] : %4f\n", i, solution[i][0]);
			printf(" x[%d] : %4f\n", i, solution[i][0]);
		}
	}
	else {
		printf("No unique solution\n");
		fprintf(fout, "No unique solution\n");
	}
	 // 검증
	free(solution);
	augMtrx = fGetAugMtrx(fin, size_N);
	solution = (double**)calloc(size_N, sizeof(double*));
	for (int i = 0; i < size_N; i++) {
		solution[i] = (double*)calloc(size_N, sizeof(double));
	}
	fprintf(fout, "Verification\n");
	printf("Verification\n");
	inv_dm = inverseMtrx(augtemp, size_N); // 역행렬
	printMtrx((const char*)"inv_mAug", inv_dm, size_N, size_N);
	fprintMtrx(fout, (const char*)"inv_mAug", inv_dm, size_N, size_N);
	solution = multiplyMatrix(inv_dm, mE, size_N, size_N, 1);
	printMtrx((const char*)"X = (A^-1) x B =", solution, size_N, 1);
	fprintMtrx(fout, (const char*)"X = (A^-1) x B =", solution, size_N, 1);

	for (int i = 0; i < size_N; i++)
		free(augMtrx[i]);
	free(augMtrx);
	free(solution);
	fclose(fin);
	fclose(fout);
}