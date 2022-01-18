/*
* 파일명 : BigArray.h
* 목적 및 기본 기능
*	배열에 관한 정보를 실행창과 파일에 출력하기위한 함수 원형과 기호상수
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 4월 2일
*/
#ifndef BIG_ARRAY_H // 헤더 중복 방지
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