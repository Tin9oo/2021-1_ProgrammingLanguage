#ifndef GJ
#define GJ
#include <stdio.h>
#include <math.h>
#include "Mtrx.h"

#define EPSILON 0.000001

void getAugmentedMatrixData(FILE* fin, double** augMtrx, int size_N);
void pivoting(double** augMtrx, int size_N, int p, int* piv_found);
void diagonalize_FileOut(FILE* fout, double** augMtrx, int size_N, int* solExist);
void invMtrxGaussJordanElim_FileOut(FILE* fout, double** Mtrx, double** inv_Mtrx, int size_N);
#endif