/*
* ���ϸ� : BigArray.h
* ���� �� �⺻ ���
*	�迭�� ���� ������ ����â�� ���Ͽ� ����ϱ����� �Լ� ������ ��ȣ���
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 4�� 2��
*/
#ifndef BIG_ARRAY_H // ��� �ߺ� ����
#define BIG_ARRAY_H

#define Data_Input_File "Data_input.txt"
#define Data_Output_File "Data_output.txt"

#include <stdio.h>
#include <math.h>
#include <time.h>

void printBigArraySample(int* array, int size, int line_size = 10, int num_sample_lines = 2);
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size = 10, int num_sample_lines = 2);
void genBigRandArray(int* array, int size);
void suffleArray(int* array, int size);
void getArrayStatistics(int* array, int size);
void fgetArrayStatistics(FILE* fout, int* array, int size);
 void sortArray(int* array, int size);
#endif