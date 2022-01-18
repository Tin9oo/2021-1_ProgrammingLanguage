/* Gauss-Jordan.cpp*/
#ifndef GAUSS_JORDAN_H
#define GAUSS_JORDAN_H
#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include "Mtrx.h"
#define EPSILON 0.000001

void pivoting(Mtrx* pMtrx, int p, int* piv_found) {
	double xmax = 0.0, xtemp;
	int j, k, max_row;

	xmax = fabs(pMtrx->dM[p][p]); // �ش� ��ġ ����� ���밪 ����
	max_row = p; // �ش� ��ġ ����
	for (j = p + 1; j < pMtrx->n_col - 1; j++) {
		if (fabs(pMtrx->dM[j][p]) > xmax) { // ������ ���밪���� ū ���� ������ ���
			xmax = fabs(pMtrx->dM[j][p]); // �� ū ���밪�� ����
			max_row = j; // �ش� ��ġ ����
		}
	}
	if (fabs(xmax) < EPSILON) // ���� 0�̰ų� 0�� ������ ���
		*piv_found = 0; // �ذ� ����
	else { // �� ��
		*piv_found = 1; // �ذ� ����
		if (max_row != p) {
			for (k = p; k <= pMtrx->n_col; k++) { // swap
				xtemp = pMtrx->dM[p][k];
				pMtrx->dM[p][k] = pMtrx->dM[max_row][k];
				pMtrx->dM[max_row][k] = xtemp;
			}
		}
	}
}
void diagonalize_FileOut(FILE* fout, Mtrx* pMtrx, int* solExist) {
	int j, k, p = 0;
	double pivWeight, w;
	// Pivoting �׸��� Scaling
	for (p = 0; (*solExist) && (p < pMtrx->n_col); p++) {
		if (p == pMtrx->n_row)
			break;
		fprintf(fout, "\nPivoting at p = %d\n", p);
		pivoting(pMtrx, p, solExist);
		fprintMtrx(fout, pMtrx);
		if (*solExist) { // �ذ� ����
			// �ش� ��ġ�� ���� scaling
			if (pMtrx->dM[p][p] != 1.0) { // �̹� scaling�� ���� �ƴ� ���
				pivWeight = pMtrx->dM[p][p];
				pMtrx->dM[p][p] = 1.0; // scaling
				for (k = p + 1; k <= pMtrx->n_row; k++) {
					pMtrx->dM[p][k] /= pivWeight; // ������ ���� ������
				}
			}
		}
		else { // �ذ� ����
			break;
		}
		fprintf(fout, "\nAfter scaling at p = %d\n", p);
		fprintMtrx(fout, pMtrx);
		// Diagonalize
		for (j = 0; j < pMtrx->n_col - 1; j++) {
			if ((j != p) && (pMtrx->dM[j][p] != 0.0)) {
				w = pMtrx->dM[j][p];
				pMtrx->dM[j][p] = 0.0;
				for (k = p + 1; k <= pMtrx->n_col; k++) {
					pMtrx->dM[j][k] =
						pMtrx->dM[j][k] - w * pMtrx->dM[p][k];
				}
			}
		}
		fprintf(fout, "\nAfter diagonalizing at p = %d\n", p);
		fprintMtrx(fout, pMtrx);
	}
}
#endif