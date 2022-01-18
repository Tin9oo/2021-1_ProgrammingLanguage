#ifndef BIG_ARRAY_H // 헤더 중복 방지
#define BIG_ARRAY_H

#define Data_Input_File "Data_input.txt"
#define Data_Output_File "Data_output.txt"
#define QUICK_SELECTION_THRESHOLD 50

#include <stdio.h>
#include <math.h>
#include <time.h>

void printBigArraySample(int* array, int size, int line_size = 10, int num_sample_lines = 2);
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size = 10, int num_sample_lines = 2);
void genBigRandArray(int* array, int size, int offset);
void suffleArray(int* array, int size);
void getArrayStatistics(int* array, int size);
void fgetArrayStatistics(FILE* fout, int* array, int size);
void selectionSort(int* array, int size);
void quickSort(int* array, int size, int left, int right);
void _hybridQuickSelectionSort(int* array, int size, int left, int right, int level);
void hybridQuickSelectionSort(int* array, int size);
#endif