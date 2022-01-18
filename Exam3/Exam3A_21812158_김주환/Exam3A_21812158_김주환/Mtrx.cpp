/* Mtrx.cpp */
#ifndef MATRIX_H
#define MATRIX_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Mtrx.h"

typedef struct {
	char* name;
	int n_row;
	int n_col;
	double** dM;
} Mtrx;
void printMtrx(Mtrx* pMtrx) {
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;

	for (int i = 0; i < pMtrx->n_row; i++) {
		for (int j = 0; j < pMtrx->n_col; j++) {
			if ((i == 0) && (j == 0)) {
				printf("%c%c%7.2lf", a6, a3, pMtrx->dM[i][j]);
			}
			else if ((i == 0) && j == (pMtrx->n_col - 1)) {
				printf("%7.2lf%c%c", pMtrx->dM[i][j], a6, a4);
			}
			else if ((i > 0) && (i < pMtrx->n_row - 1) && (j == 0)) {
				printf("%c%c%7.2lf", a6, a2, pMtrx->dM[i][j]);
			}
			else if ((i > 0) && (i < pMtrx->n_row - 1) && (j == (pMtrx->n_col - 1))) {
				printf("%7.2lf%c%c", pMtrx->dM[i][j], a6, a2);
			}
			else if ((i == pMtrx->n_row - 1) && (j == 0)) {
				printf("%c%c%7.2lf", a6, a6, pMtrx->dM[i][j]);
			}
			else if ((i == pMtrx->n_row - 1) && (j == (pMtrx->n_col - 1))) {
				printf("%7.2lf%c%c", pMtrx->dM[i][j], a6, a5);
			}
			else {
				printf("%7.2lf", pMtrx->dM[i][j]);
			}
			if (pMtrx->n_col == 1) {
				if (i == 0)
					printf("%c%c", a6, a4);
				else if (i == pMtrx->n_row - 1)
					printf("%c%c", a6, a5);
				else
					printf("%c%c", a6, a2);
			}
		}
		printf("\n");
	}
}
void fprintMtrx(FILE* fout, Mtrx* pMtrx) {
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;

	for (int i = 0; i < pMtrx->n_row; i++) {
		for (int j = 0; j < pMtrx->n_col; j++) {
			if ((i == 0) && (j == 0)) {
				fprintf(fout, "%c%c%7.2lf", a6, a3, pMtrx->dM[i][j]);
			}
			else if ((i == 0) && j == (pMtrx->n_col - 1)) {
				fprintf(fout, "%7.2lf%c%c", pMtrx->dM[i][j], a6, a4);
			}
			else if ((i > 0) && (i < pMtrx->n_row - 1) && (j == 0)) {
				fprintf(fout, "%c%c%7.2lf", a6, a2, pMtrx->dM[i][j]);
			}
			else if ((i > 0) && (i < pMtrx->n_row - 1) && (j == (pMtrx->n_col - 1))) {
				fprintf(fout, "%7.2lf%c%c", pMtrx->dM[i][j], a6, a2);
			}
			else if ((i == pMtrx->n_row - 1) && (j == 0)) {
				fprintf(fout, "%c%c%7.2lf", a6, a6, pMtrx->dM[i][j]);
			}
			else if ((i == pMtrx->n_row - 1) && (j == (pMtrx->n_col - 1))) {
				fprintf(fout, "%7.2lf%c%c", pMtrx->dM[i][j], a6, a5);
			}
			else {
				fprintf(fout, "%7.2lf", pMtrx->dM[i][j]);
			}
			if (pMtrx->n_col == 1) {
				if (i == 0)
					fprintf(fout, "%c%c", a6, a4);
				else if (i == pMtrx->n_row - 1)
					fprintf(fout, "%c%c", a6, a5);
				else
					fprintf(fout, "%c%c", a6, a2);
			}
		}
		fprintf(fout, "\n");
	}
}
Mtrx* fgetMtrx(FILE* fin, Mtrx* pMtrx) {
	double d = 0.0;
	char temp = 'a';

	pMtrx->name = &temp;
	fscanf(fin, "%d %d", &pMtrx->n_row, &pMtrx->n_col);
	pMtrx->dM = (double**)calloc(pMtrx->n_row, sizeof(double*));
	for (int i = 0; i < pMtrx->n_row; i++) {
		pMtrx->dM[i] = (double*)calloc(pMtrx->n_col, sizeof(double));
	}
	for (int i = 0; i < pMtrx->n_row; i++) {
		for (int j = 0; j < pMtrx->n_col; j++) {
			if (fscanf(fin, "%lf", &d) != EOF) pMtrx->dM[i][j] = d;
		}
	}
	return pMtrx;
}
#endif