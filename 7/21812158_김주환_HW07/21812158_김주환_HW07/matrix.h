// matrix.h
#ifndef M // 헤더 중복 방지
#define M

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MTRXINPUTDATA "input_data.txt"
double** input_mtrx(FILE* fin, double** dm, int* row_size, int* col_size);
void print_mtrx(double** dm, int row_size, int col_size);
void delete_double_mtrx(double** dm, int row_size, int col_size);
double** add_mtrx(double** dm1, double** dm2, double** dm3, int row_size, int col_size);
double** sub_mtrx(double** dm1, double** dm2, double** dm3, int row_size, int col_size);
double** multiply_mtrx(double** dm1, double** dm2, double** dm3, int row_size, int col_size, int temp);
#endif