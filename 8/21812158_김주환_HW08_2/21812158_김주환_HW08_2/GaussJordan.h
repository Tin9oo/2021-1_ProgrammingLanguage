// GaussJordan.h
#ifndef GJ
#define GJ
#include <stdio.h>
#include <math.h>
#include "Matrix.h"

#define EPSILON 0.000001

double** fGetAugMtrx(FILE* fin, int size_N);
void pivoting(double** augMtrx, int size_N, int p, int* piv_found);
void diagonalize_FileOut(FILE* fout, double** augMtrx, int size_N, int* solExist);
double** inverseMtrx(double** Mtrx, int size_N);
#endif