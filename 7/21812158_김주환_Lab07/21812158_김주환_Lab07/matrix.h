#ifndef BIG_ARRAY_H // 헤더 중복 방지
#define BIG_ARRAY_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MTRXINPUTDATA "mtrxInputData.txt"
#define MTRXNXNINPUTDATA "mtrx_nxn_InputData.txt"

double** create_double_mtrx(int row_size, int col_size);
double** fget_double_mtrx(FILE* fin, double** dm, int row_size, int col_size);
void print_mtrx(double **dm, int row_size, int col_size);
void fprint_mtrx(FILE* fout, double** dm, int row_size, int col_size);
void delete_double_mtrx(double **dm, int row_size, int col_size);
void add_mtrx(double **dm1, double **dm2, double **dm3, int row_size, int col_size);
void sub_mtrx(double **dm1, double **dm2, double **dm3, int row_size, int col_size);
void multiply_mtrx(double** dm1, double** dm2, double** dm3, int row_size, int col_size, int temp);
void average_mtrx(double** dm, int row_size, int col_size);
#endif