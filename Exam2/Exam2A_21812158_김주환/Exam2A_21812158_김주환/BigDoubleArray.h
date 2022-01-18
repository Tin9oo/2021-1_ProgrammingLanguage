#ifndef BIG_ARRAY_H // 헤더 중복 방지
#define BIG_ARRAY_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void printBigArraySample_double(double* dA, int size, int items_per_line, int num_sample_lines);
double* genBigRandArray_double(int bigRandSize, double offset);
#endif