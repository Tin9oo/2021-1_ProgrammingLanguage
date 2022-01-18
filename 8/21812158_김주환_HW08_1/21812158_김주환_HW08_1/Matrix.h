/* Matrix.h */
#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <stdlib.h>
double** fGetMtrx(FILE* fin, int* row_size, int* col_size);
double** addMtrx(double** A, double** B, int row_size, int col_size);
double** subtractMtrx(double** A, double** B, int row_size, int col_size);
double** multiplyMtrx(double** A, double** B, int row_size, int k_size, int col_size);
void printMtrx(const char* name, double** mA, int row_size, int col_size);
void fprintMtrx(FILE* fout, const char* name, double** mA, int row_size, int col_size);
double** inverseMtrx(double** mA, int size_N);
#endif