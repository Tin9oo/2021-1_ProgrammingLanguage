// Matrix.cpp
#ifndef M
#define M
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// ���ϴ� ũ���� 2���� �迭 ���� �Ҵ�
double** createDynamicDoubleMatrix(int row_size, int col_size) {
	double** ppdm = NULL;

	ppdm = (double**)calloc(row_size, sizeof(double*));
	for (int i = 0; i < row_size; i++) {
		ppdm[i] = (double*)calloc(col_size, sizeof(double));
	}
	return ppdm;
}
// ���Ϸκ��� ���ϴ� ũ���� ��� ������ �ҷ��ͼ� ����
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
// ������ 2���� ���� �迭 ����
void deleteDynMtrx(double** dm, int row_size, int col_size) {
	for (int i = 0; i < row_size; i++) free(dm[i]);
	free(dm);
}
// ��� �����͸� ����â�� ���
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
// ��� �����͸� ������ ���Ͽ� ���
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
// ��� ����
double** addMatrix(double** dm1, double** dm2, int row_size, int col_size) {
	double** dm3 = createDynamicDoubleMatrix(row_size, col_size);

	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			dm3[i][j] = dm1[i][j] + dm2[i][j];
		}
	}
	return dm3;
}
// ��� ����
double** subtractMatrix(double** dm1, double** dm2, int row_size, int col_size) {
	double** dm3 = createDynamicDoubleMatrix(row_size, col_size);

	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			dm3[i][j] = dm1[i][j] - dm2[i][j];
		}
	}
	return dm3;
}
// ��� ����
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