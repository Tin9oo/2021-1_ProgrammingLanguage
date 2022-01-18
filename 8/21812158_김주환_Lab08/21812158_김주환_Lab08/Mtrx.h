#ifndef M
#define M
#include <stdio.h>

double** createDynamicDoubleMatrix(int row_size, int col_size);
double** fGetMtrx(FILE* fin, int* row_size, int* col_size);
void deleteDynMtrx(double** dm, int row_size, int col_size);
void printMtrx(double** dm, int size_row, int size_col);
void fprintMtrx(FILE* fout, double** dm, int row_size, int col_size);
double** addMatrix(double** dm1, double** dm2, int row_size, int col_size);
double** subtractMatrix(double** dm1, double** dm2, int row_size, int col_size);
double** multiplyMatrix(double** dm1, double** dm2, int row_size, int temp, int col_size);
#endif