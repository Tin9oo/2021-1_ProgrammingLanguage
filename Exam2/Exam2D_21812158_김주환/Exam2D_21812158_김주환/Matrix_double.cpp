#ifndef BIG_ARRAY_H // 헤더 중복 방지
#define BIG_ARRAY_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double** create_double_mtrx(int row_size, int col_size) {
	double** ppdm = NULL;

	ppdm = (double**)calloc(row_size, sizeof(double*));
	for (int i = 0; i < row_size; i++) {
		ppdm[i] = (double*)calloc(col_size, sizeof(double));
	}
	return ppdm;
}
double** fGetMtrx_double(FILE* fin, int* row_size, int* col_size) {
	double d = 0.0;

	fscanf(fin, "%d %d", row_size, col_size);
	double** dm = create_double_mtrx(*row_size, *col_size);

	for (int i = 0; i < *row_size; i++) {
		for (int j = 0; j < *col_size; j++) {
			if (fscanf(fin, "%lf", &d) != EOF) dm[i][j] = d;
		}
	}
	return dm;
}
void printMtrx_double(const char* name, double** dm, int row_size, int col_size) {
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;

	printf("%s =\n", name);
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
void fprintMtrx_double(FILE* fout, const char* name, double** dm, int row_size, int col_size) {
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;

	fprintf(fout, "%s =\n", name);
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
}
double** CalcRowColAvg_double(double** dm, int row_size, int col_size) {
	double sum_h = 0.0, sum_v = 0.0, sum = 0.0;
	double avg_h = 0.0, avg_v = 0.0, avg = 0.0;
	double** dm_avg = create_double_mtrx(row_size + 1, col_size + 1);

	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			dm_avg[i][j] = dm[i][j];
		}
	}

	for (int i = 0; i < row_size; i++) {
		sum_h = 0;
		for (int j = 0; j < col_size; j++) {
			sum_h += dm[i][j];
			sum += dm[i][j];
		}
		avg_h = sum_h / col_size;
		dm_avg[i][col_size] = avg_h;
	}
	for (int i = 0; i < col_size; i++) {
		sum_v = 0;
		for (int j = 0; j < row_size; j++) {
			sum_v += dm[i][j];
		}
		avg_v = sum_v / row_size;
		dm_avg[row_size][i] = avg_v;
	}
	avg = sum / ((double)row_size * (double)col_size);
	dm_avg[row_size][col_size] = avg;

	return dm_avg;
}
double** addMtrx_double(double** dm1, double** dm2, int row_size, int col_size) {
	double** dm3 = create_double_mtrx(row_size, col_size);

	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			dm3[i][j] = dm1[i][j] + dm2[i][j];
		}
	}
	return dm3;
}
double** subtractMtrx_double(double** dm1, double** dm2, int row_size, int col_size) {
	double** dm3 = create_double_mtrx(row_size, col_size);

	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			dm3[i][j] = dm1[i][j] - dm2[i][j];
		}
	}
	return dm3;
}
double** multiplyMtrx_double(double** dm1, double** dm2, int row_size, int col_size, int temp) {
	double** dm3 = create_double_mtrx(row_size, col_size);

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