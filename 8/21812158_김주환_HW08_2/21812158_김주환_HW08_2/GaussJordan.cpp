// GaussJordan.h
#ifndef GJ
#define GJ
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include "Matrix.h"

#define EPSILON 0.000001

// ÷����� ������ ���Ϸκ��� �ҷ�����
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
// pivoting ���� ����
void pivoting(double** augMtrx, int size_N, int p, int* piv_found) {
	double xmax = 0.0, xtemp;
	int j, k, max_row;

	xmax = fabs(augMtrx[p][p]); // �ش� ��ġ ����� ���밪 ����
	max_row = p; // �ش� ��ġ ����
	for (j = p + 1; j < size_N; j++) {
		if (fabs(augMtrx[j][p]) > xmax) { // ������ ���밪���� ū ���� ������ ���
			xmax = fabs(augMtrx[j][p]); // �� ū ���밪�� ����
			max_row = j; // �ش� ��ġ ����
		}
	}
	if (fabs(xmax) < EPSILON) // ���� 0�̰ų� 0�� ������ ���
		*piv_found = 0; // �ذ� ����
	else { // �� ��
		*piv_found = 1; // �ذ� ����
		if (max_row != p) {
			for (k = p; k <= size_N; k++) { // swap
				xtemp = augMtrx[p][k];
				augMtrx[p][k] = augMtrx[max_row][k];
				augMtrx[max_row][k] = xtemp;
			}
		}
	}
}
// �밢ȭ ���� ����
void diagonalize_FileOut(FILE* fout, double** augMtrx, int size_N, int* solExist) {
	int j, k, p = 0;
	double pivWeight, w;
	// Pivoting �׸��� Scaling
	for (p = 0; (*solExist) && (p < size_N); p++) {
		pivoting(augMtrx, size_N, p, solExist);
		if (*solExist) { // �ذ� ����
			// �ش� ��ġ�� ���� scaling
			if (augMtrx[p][p] != 1.0) { // �̹� scaling�� ���� �ƴ� ���
				pivWeight = augMtrx[p][p];
				augMtrx[p][p] = 1.0; // scaling
				for (k = p + 1; k <= size_N; k++) {
					augMtrx[p][k] /= pivWeight; // ������ ���� ������
				}
			}
		}
		else { // �ذ� ����
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
// ����� ���ϱ�
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
		// ������� ���ϰ���� ���
		for (k = 0; k < size_N; k++)
			m_aug[j][k] = Mtrx[j][k];
		// ���� ���
		for (k = size_N; k < size_N * 2; k++)
			m_aug[j][k] = (k == (j + size_N)) ? 1.0 : 0.0;
	}

	for (p = 0; p < size_N; p++) {
		if (m_aug[p][p] != 1.0) { // �ش� ��ġ�� ���� �̹� scaling���� ���� ���
			pivWeight = m_aug[p][p];
			m_aug[p][p] = 1.0; // scaling
			for (k = p + 1; k < size_N * 2; k++) {
				m_aug[p][k] /= pivWeight; // ������ ���� ������
			}
		}
		// diagonalize
		for (j = 0; j < size_N; j++) {
			if ((j != p) && (m_aug[j][p] != 0.0))
			{
				w = m_aug[j][p];
				m_aug[j][p] = 0.0; // �ش� ������ pivot ��ġ �̿��� �ڸ��� 0.0���� �Ұ�
				for (k = p + 1; k < 2 * size_N; k++) {
					m_aug[j][k] -= w * m_aug[p][k];
				}
			}
		}
	}
	// ���� ������� ������ 2���� �迭�� ����
	for (j = 0; j < size_N; j++) {
		for (k = 0; k < size_N; k++) {
			inv_m[j][k] = m_aug[j][k + size_N];
		}
	}
	return inv_m;
}
#endif