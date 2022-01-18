#ifndef ARRAY
#define ARRAY

#include <stdio.h>
#include <stdlib.h>

void genBigRandArray(int* array, int size, int offset);
void printBigArraySample(int* array, int size, int line_size, int num_sample_lines);

void selectionSorting(int* array, int size);

#endif