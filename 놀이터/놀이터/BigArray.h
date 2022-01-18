#ifndef BIG_ARRAY_H
#define BIG_ARRAY_H

#include <stdio.h>

void printBigArraySample(int* array, int size, int line_size, int num_sample_lines);
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int num_sample_lines);
void genBigRandArray(int* array, int size);
void getArrayStatistics(int* array, int size);
void fgetArrayStatistics(FILE* fout, int* array, int size);
#endif