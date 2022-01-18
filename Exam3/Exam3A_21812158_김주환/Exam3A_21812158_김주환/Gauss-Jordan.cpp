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

	xmax = fabs(pMtrx->dM[p][p]); // 해당 위치 계수의 절대값 저장
	max_row = p; // 해당 위치 저장
	for (j = p + 1; j < pMtrx->n_col - 1; j++) {
		if (fabs(pMtrx->dM[j][p]) > xmax) { // 저장한 절대값보다 큰 값이 존재할 경우
			xmax = fabs(pMtrx->dM[j][p]); // 더 큰 절대값을 저장
			max_row = j; // 해당 위치 저장
		}
	}
	if (fabs(xmax) < EPSILON) // 값이 0이거나 0에 근접한 경우
		*piv_found = 0; // 해가 없음
	else { // 그 외
		*piv_found = 1; // 해가 있음
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
	// Pivoting 그리고 Scaling
	for (p = 0; (*solExist) && (p < pMtrx->n_col); p++) {
		if (p == pMtrx->n_row)
			break;
		fprintf(fout, "\nPivoting at p = %d\n", p);
		pivoting(pMtrx, p, solExist);
		fprintMtrx(fout, pMtrx);
		if (*solExist) { // 해가 존재
			// 해당 위치의 원소 scaling
			if (pMtrx->dM[p][p] != 1.0) { // 이미 scaling된 값이 아닌 경우
				pivWeight = pMtrx->dM[p][p];
				pMtrx->dM[p][p] = 1.0; // scaling
				for (k = p + 1; k <= pMtrx->n_row; k++) {
					pMtrx->dM[p][k] /= pivWeight; // 이후의 값도 나누기
				}
			}
		}
		else { // 해가 없음
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