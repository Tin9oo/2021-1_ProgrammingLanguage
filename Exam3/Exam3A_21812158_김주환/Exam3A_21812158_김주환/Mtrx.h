/* Mtrx.h */
#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
typedef struct {
	char* name;
	int n_row;
	int n_col;
	double** dM;
} Mtrx;
void printMtrx(Mtrx * pMtrx);
void fprintMtrx(FILE * fout, Mtrx * pMtrx);
Mtrx * fgetMtrx(FILE* fin, Mtrx * pMtrx);
#endif