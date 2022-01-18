/* Matrix.cpp */
#define _CRT_SECURE_NO_WARNINGS

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

double** fGetMtrx(FILE* fin, int* row_size, int* col_size) {
	double d = 0.0;
	double** dm = NULL;

	fscanf(fin, "%d %d", row_size, col_size);
	dm = (double**)calloc(*row_size, sizeof(double*));
	for (int i = 0; i < *row_size; i++) {
		dm[i] = (double*)calloc(*col_size, sizeof(double));
	}

	for (int i = 0; i < *row_size; i++) {
		for (int j = 0; j < *col_size; j++) {
			if (fscanf(fin, "%lf", &d) != EOF) dm[i][j] = d;
		}
	}
	return dm;
}
double** addMtrx(double** A, double** B, int row_size, int col_size) {
	double** D = (double**)calloc(row_size, sizeof(double*));
	for (int i = 0; i < row_size; i++) {
		D[i] = (double*)calloc(col_size, sizeof(double));
	}

	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			D[i][j] = A[i][j] + B[i][j];
		}
	}
	return D;
}
double** subtractMtrx(double** A, double** B, int row_size, int col_size) {
	double** E = (double**)calloc(row_size, sizeof(double*));
	for (int i = 0; i < row_size; i++) {
		E[i] = (double*)calloc(col_size, sizeof(double));
	}

	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			E[i][j] = A[i][j] - B[i][j];
		}
	}
	return E;
}
double** multiplyMtrx(double** A, double** B, int row_size, int k_size, int col_size) {
	double** F = (double**)calloc(row_size, sizeof(double*));
	for (int i = 0; i < row_size; i++) {
		F[i] = (double*)calloc(col_size, sizeof(double));
	}

	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			for (int k = 0; k < k_size; k++) {
				F[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return F;
}
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
double** inverseMtrx(double** Mtrx, int size_N) {
	int j, k, p = 0;
	double pivWeight, w;
	double** m_aug, ** inv_m;

	m_aug = (double**)calloc(size_N, sizeof(double*));
	inv_m = (double**)calloc(size_N, sizeof(double*));
	for (int i = 0; i < size_N; i++) {
		m_aug[i] = (double*)calloc(size_N * 2, sizeof(double));
		inv_m[i] = (double*)calloc(size_N, sizeof(double));
	}

	for (j = 0; j < size_N; j++) {
		// 역행렬을 구하고싶은 행렬
		for (k = 0; k < size_N; k++)
			m_aug[j][k] = Mtrx[j][k];
		// 단위 행렬
		for (k = size_N; k < size_N * 2; k++)
			m_aug[j][k] = (k == (j + size_N)) ? 1.0 : 0.0;
	}

	for (p = 0; p < size_N; p++) {
		if (m_aug[p][p] != 1.0) { // 해당 위치의 값이 이미 scaling되지 않은 경우
			pivWeight = m_aug[p][p];
			m_aug[p][p] = 1.0; // scaling
			for (k = p + 1; k < size_N * 2; k++) {
				m_aug[p][k] /= pivWeight; // 이후의 값도 나누기
			}
		}
		// diagonalize
		for (j = 0; j < size_N; j++) {
			if ((j != p) && (m_aug[j][p] != 0.0))
			{
				w = m_aug[j][p];
				m_aug[j][p] = 0.0; // 해당 열에서 pivot 위치 이외의 자리에 0.0으로 소거
				for (k = p + 1; k < 2 * size_N; k++) {
					m_aug[j][k] -= w * m_aug[p][k];
				}
			}
		}
	}
	// 구한 역행렬을 생성한 2차원 배열에 복사
	for (j = 0; j < size_N; j++) {
		for (k = 0; k < size_N; k++) {
			inv_m[j][k] = m_aug[j][k + size_N];
		}
	}
	return inv_m;
}
#endif