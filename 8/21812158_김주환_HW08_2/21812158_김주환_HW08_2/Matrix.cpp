// Matrix.cpp
#ifndef M
#define M
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// 원하는 크기의 2차원 배열 동적 할당
double** createDynamicDoubleMatrix(int row_size, int col_size) {
	double** ppdm = NULL;

	ppdm = (double**)calloc(row_size, sizeof(double*));
	for (int i = 0; i < row_size; i++) {
		ppdm[i] = (double*)calloc(col_size, sizeof(double));
	}
	return ppdm;
}
// 파일로부터 원하는 크기의 행렬 데이터 불러와서 저장
double** fGetMtrx(FILE* fin, int* row_size, int* col_size) {
	double d = 0.0;

	fscanf(fin, "%d %d", row_size, col_size);
	double** dm = createDynamicDoubleMatrix(*row_size, *col_size);

	for (int i = 0; i < *row_size; i++) {
		for (int j = 0; j < *col_size; j++) {
			if (fscanf(fin, "%lf", &d) != EOF) dm[i][j] = d;
		}
	}
	return dm;
}
// 생성한 2차원 동적 배열 해제
void deleteDynMtrx(double** dm, int row_size, int col_size) {
	for (int i = 0; i < row_size; i++) free(dm[i]);
	free(dm);
}
// 행렬 데이터를 실행창에 출력
void printMtrx(const char* name, double** dm, int row_size, int col_size) {
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;

	printf(name);
	printf("\n");
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			if ((i == 0) && (j == 0)) {
				printf("%c%c%7.2lf", a6, a3, dm[i][j]);
			}
			else if ((i == 0) && j == (col_size - 1)) {
				printf("%7.2lf%c%c", dm[i][j], a6, a4);
			}
			else if ((i > 0) && (i < row_size - 1) && (j == 0)) {
				printf("%c%c%7.2lf", a6, a2, dm[i][j]);
			}
			else if ((i > 0) && (i < row_size - 1) && (j == (col_size - 1))) {
				printf("%7.2lf%c%c", dm[i][j], a6, a2);
			}
			else if ((i == row_size - 1) && (j == 0)) {
				printf("%c%c%7.2lf", a6, a6, dm[i][j]);
			}
			else if ((i == row_size - 1) && (j == (col_size - 1))) {
				printf("%7.2lf%c%c", dm[i][j], a6, a5);
			}
			else {
				printf("%7.2lf", dm[i][j]);
			}
			if (col_size == 1) {
				if (i == 0)
					printf("%c%c", a6, a4);
				else if (i == row_size - 1)
					printf("%c%c", a6, a5);
				else
					printf("%c%c", a6, a2);
			}
		}
		printf("\n");
	}
}
// 행렬 데이터를 지정된 파일에 출력
void fprintMtrx(FILE* fout, const char* name, double** dm, int row_size, int col_size) {
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;

	fprintf(fout, name);
	fprintf(fout, "\n");
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			if ((i == 0) && (j == 0)) {
				fprintf(fout, "%c%c%7.2lf", a6, a3, dm[i][j]);
			}
			else if ((i == 0) && j == (col_size - 1)) {
				fprintf(fout, "%7.2lf%c%c", dm[i][j], a6, a4);
			}
			else if ((i > 0) && (i < row_size - 1) && (j == 0)) {
				fprintf(fout, "%c%c%7.2lf", a6, a2, dm[i][j]);
			}
			else if ((i > 0) && (i < row_size - 1) && (j == (col_size - 1))) {
				fprintf(fout, "%7.2lf%c%c", dm[i][j], a6, a2);
			}
			else if ((i == row_size - 1) && (j == 0)) {
				fprintf(fout, "%c%c%7.2lf", a6, a6, dm[i][j]);
			}
			else if ((i == row_size - 1) && (j == (col_size - 1))) {
				fprintf(fout, "%7.2lf%c%c", dm[i][j], a6, a5);
			}
			else {
				fprintf(fout, "%7.2lf", dm[i][j]);
			}
			if (col_size == 1) {
				if (i == 0)
					fprintf(fout, "%c%c", a6, a4);
				else if (i == row_size - 1)
					fprintf(fout, "%c%c", a6, a5);
				else
					fprintf(fout, "%c%c", a6, a2);
			}
		}
		fprintf(fout, "\n");
	}
}
// 행렬 덧셈
double** addMatrix(double** dm1, double** dm2, int row_size, int col_size) {
	double** dm3 = createDynamicDoubleMatrix(row_size, col_size);

	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			dm3[i][j] = dm1[i][j] + dm2[i][j];
		}
	}
	return dm3;
}
// 행렬 뺄셈
double** subtractMatrix(double** dm1, double** dm2, int row_size, int col_size) {
	double** dm3 = createDynamicDoubleMatrix(row_size, col_size);

	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			dm3[i][j] = dm1[i][j] - dm2[i][j];
		}
	}
	return dm3;
}
// 행렬 곱셈
double** multiplyMatrix(double** dm1, double** dm2, int row_size, int temp, int col_size) {
	double** dm3 = createDynamicDoubleMatrix(row_size, col_size);

	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			for (int k = 0; k < temp; k++) {
				dm3[i][j] += dm1[i][k] * dm2[k][j];
			}
		}
	}
	return dm3;
}
#endif