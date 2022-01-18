#ifndef BIG_ARRAY_H // 헤더 중복 방지
#define BIG_ARRAY_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double** create_double_mtrx(int row_size, int col_size);
double** fGetMtrx_double(FILE* fin, int* row_size, int* col_size);
void printMtrx_double(const char* name, double** dM, int row_size, int col_size);
void fprintMtrx_double(FILE* fout, const char* name, double** dM, int row_size, int col_size);
double** CalcRowColAvg_double(double** dM, int row_size, int col_size);
#endif