#ifndef M
#define M
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Mtrx.h"

#define EPSILON 0.000001

double** fGetMtrx(FILE* fin, int* row_size, int* col_size);
void deleteDynMtrx(double** dm, int row_size, int col_size);
void printMtrx(double** dm, int row_size, int col_size);
void fprintMtrx(FILE* fout, double** dm, int row_size, int col_size);
void addMatrix(double** dm1, double** dm2, double** dm3, int row_size, int col_size);
void subtractMatrix(double** dm1, double** dm2, double** dm3, int row_size, int col_size);
void multiplyMatrix(double** dm1, double** dm2, double** dm3, int row_size, int temp, int col_size);
void getAugmentedMatrixData(FILE* fin, double** augMtrx, int size_N);
void pivoting(double** augMtrx, int size_N, int p, int* piv_found);
void diagonalize_FileOut(FILE* fout, double** augMtrx, int size_N, int* solExist);
void inverseMtrx(double** Mtrx, double** inv_Mtrx, int size_N);
#endif