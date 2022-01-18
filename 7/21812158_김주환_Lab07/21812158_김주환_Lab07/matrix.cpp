#ifndef BIG_ARRAY_H // 헤더 중복 방지
#define BIG_ARRAY_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

#define MTRXINOUTDATA "mtrxInputData.txt"
#define MTRXNXNINPUTDATA "mtrx_nxn_InputData.txt"

double** create_double_mtrx(int row_size, int col_size) {
	double** ppdm = NULL;

	ppdm = (double**)calloc(row_size, sizeof(double*));
	for (int i = 0; i < row_size; i++) {
		ppdm[i] = (double*)calloc(col_size, sizeof(double));
	}
	return ppdm;
}
double** fget_double_mtrx(FILE* fin, double** dm, int row_size, int col_size) {
	double d = 0.0;

	dm = create_double_mtrx(row_size, col_size);
#ifdef AM
	row_size--;
	col_size--;
#endif
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			if (fscanf(fin, "%lf", &d) != EOF) dm[i][j] = d;
		}
	}
	return dm;
}
void print_mtrx(double** dm, int row_size, int col_size) {
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;

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
		}
		printf("\n");
	}
}
void fprint_mtrx(FILE* fout, int cal, double** dm, int row_size, int col_size) {
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;

	if (cal == 0) {
		fout = fopen(MTRXNXNINPUTDATA, "w");
		if (fout == NULL) {
			printf("Error");
			return;
		}
	}
	else if (cal == 1) {
		fout = fopen(MTRXINOUTDATA, "w");
		if (fout == NULL) {
			printf("Error");
			return;
		}
	}

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
		}
		fprintf(fout, "\n");
	}
	fclose(fout);
}
void delete_double_mtrx(double** dm, int row_size, int col_size) {
	for (int i = 0; i < row_size; i++) free(dm[i]);
	free(dm);
}
void add_mtrx(double** dm1, double** dm2, double** dm3, int row_size, int col_size) {
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			dm3[i][j] = dm1[i][j] + dm2[i][j];
		}
	}
}
void sub_mtrx(double** dm1, double** dm2, double** dm3, int row_size, int col_size) {
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			dm3[i][j] = dm1[i][j] - dm2[i][j];
		}
	}
}
void multiply_mtrx(double** dm1, double** dm2, double** dm3, int row_size, int col_size, int temp) {
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			for (int k = 0; k < temp; k++) {
				dm3[i][j] += dm1[i][k] * dm2[k][j];
			}
		}
	}
}
void average_mtrx(double** dm, int row_size, int col_size) {
	double sum_h = 0.0, sum_v = 0.0, sum = 0.0;
	double avg_h = 0.0, avg_v = 0.0, avg = 0.0;

	for (int i = 0; i < row_size; i++) {
		sum_h = 0;
		for (int j = 0; j < col_size; j++) {
			sum_h += dm[i][j];
			sum += dm[i][j];
		}
		avg_h = sum_h / col_size;
		dm[i][col_size] = avg_h;
	}
	for (int i = 0; i < col_size; i++) {
		sum_v = 0;
		for (int j = 0; j < row_size; j++) {
			sum_v += dm[i][j];
		}
		avg_v = sum_v / row_size;
		dm[row_size][i] = avg_v;
	}
	avg = sum / ((double)row_size * (double)col_size);
	dm[row_size][col_size] = avg;
}
#endif