// GaussJordan.h
#ifndef GJ
#define GJ
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include "Matrix.h"

#define EPSILON 0.000001

// 첨가행렬 데이터 파일로부터 불러오기
double** fGetAugMtrx(FILE* fin, int size_N) {
	double d = 0.0;
	double** augMtrx = createDynamicDoubleMatrix(size_N, size_N + 1);

	if (fin == NULL) {
		printf("Error in getDoubleMatrixData() - file pointer is NULL !!\n");
		exit(-1);
	}
	for (int m = 0; m < size_N; m++)
		for (int n = 0; n <= size_N; n++) {
			if (fscanf(fin, "%lf", &d) != EOF)
				augMtrx[m][n] = d;
		}
	return augMtrx;
}
// pivoting 과정 수행
void pivoting(double** augMtrx, int size_N, int p, int* piv_found) {
	double xmax = 0.0, xtemp;
	int j, k, max_row;

	xmax = fabs(augMtrx[p][p]); // 해당 위치 계수의 절대값 저장
	max_row = p; // 해당 위치 저장
	for (j = p + 1; j < size_N; j++) {
		if (fabs(augMtrx[j][p]) > xmax) { // 저장한 절대값보다 큰 값이 존재할 경우
			xmax = fabs(augMtrx[j][p]); // 더 큰 절대값을 저장
			max_row = j; // 해당 위치 저장
		}
	}
	if (fabs(xmax) < EPSILON) // 값이 0이거나 0에 근접한 경우
		*piv_found = 0; // 해가 없음
	else { // 그 외
		*piv_found = 1; // 해가 있음
		if (max_row != p) {
			for (k = p; k <= size_N; k++) { // swap
				xtemp = augMtrx[p][k];
				augMtrx[p][k] = augMtrx[max_row][k];
				augMtrx[max_row][k] = xtemp;
			}
		}
	}
}
// 대각화 과정 수행
void diagonalize_FileOut(FILE* fout, double** augMtrx, int size_N, int* solExist) {
	int j, k, p = 0;
	double pivWeight, w;
	// Pivoting 그리고 Scaling
	for (p = 0; (*solExist) && (p < size_N); p++) {
		pivoting(augMtrx, size_N, p, solExist);
		if (*solExist) { // 해가 존재
			// 해당 위치의 원소 scaling
			if (augMtrx[p][p] != 1.0) { // 이미 scaling된 값이 아닌 경우
				pivWeight = augMtrx[p][p];
				augMtrx[p][p] = 1.0; // scaling
				for (k = p + 1; k <= size_N; k++) {
					augMtrx[p][k] /= pivWeight; // 이후의 값도 나누기
				}
			}
		}
		else { // 해가 없음
			break;
		}
		// Diagonalize
		for (j = 0; j < size_N; j++) {
			if ((j != p) && (augMtrx[j][p] != 0.0)) {
				w = augMtrx[j][p];
				augMtrx[j][p] = 0.0;
				for (k = p + 1; k <= size_N; k++) {
					augMtrx[j][k] =
						augMtrx[j][k] - w * augMtrx[p][k];
				}
			}
		}
	}
}
// 역행렬 구하기
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