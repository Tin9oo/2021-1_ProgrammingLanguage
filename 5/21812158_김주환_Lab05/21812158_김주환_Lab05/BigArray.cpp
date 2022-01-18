/*
* 파일명 : BigArray.c
* 목적 및 기본 기능
*	BigArray.h 헤더 파일에서 선언한 함수 원형의 정보
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 4월 2일
*/
#ifndef BIG_ARRAY_H
#define BIG_ARRAY_H

#define Data_Input_File "Data_input.txt"
#define Data_Output_File "Data_output.txt"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "BigArray.h"

// 실행창에 배열 정보 출력
void printBigArraySample(int* array, int size, int line_size = 10, int num_sample_lines = 2) {
	int count = 0; // 몇번째 수인지 확인
	int brk_temp = 0; // 센티널을 만나면 탈출

	for (int i = 0; i < num_sample_lines; i++) { // 기본 배열 출력
		for (int j = 0; j < line_size; j++) {    // line_size개 만큼 num_sample_lines줄 출력
			if (count > size) { // 지정한 크기 초과하면 탈출
				printf("\n");
				return;
			}
			if (array[count] == -1) { // 센티널 만나면 탈출
				brk_temp++;
				break;
			}
			printf("%8d", array[count]);
			count++;
		}
		printf("\n");
		if (brk_temp == 1)break;
	}

	if (20 < size && size < 41) { // 20 초과 40 이하인 경우의 배열 출력
		count = num_sample_lines * line_size; // 첫번째 출력 이후로 초기값 재설정
		brk_temp = 0;
		for (int i = 0; i < num_sample_lines; i++) {
			for (int j = 0; j < line_size; j++) {
				if (count > size) {
					printf("\n");
					return;
				}
				if (array[count] == -1) {
					brk_temp++;
					break;
				}
				printf("%8d", array[count]);
				count++;
			}
			printf("\n");
			if (brk_temp == 1)break;
		}
	}
	else if (40 < size) { // 40 초과인 경우의 배열 출력
		brk_temp = 0;

		if (count < (size - line_size * num_sample_lines)) // 마지막 num_sample_lines줄 만큼 출력
			count = size - (line_size * num_sample_lines); // 하도록 초기값 재설정
		if (count >= size) return;
		printf("\n   . . . . .\n\n");
		brk_temp = 0;
		for (int i = 0; i < num_sample_lines; i++) {
			for (int j = 0; j < line_size; j++) {
				if (count > size) {
					printf("\n");
					return;
				}
				if (array[count] == -1) {
					brk_temp++;
					break;
				}
				printf("%8d", array[count]);
				count++;
			}
			printf("\n");
			if (brk_temp == 1)break;
		}
		printf("\n");
	}
}

// 지정된 파일에 배열 정보 출력
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size = 10, int num_sample_lines = 2) {
	int count = 0; // 몇번째 수인지 확인
	int brk_temp = 0; // 센티널 만나면 탈출

	for (int i = 0; i < num_sample_lines; i++) { // 기본 배열 출력
		for (int j = 0; j < line_size; j++) {
			if (count > size) { // 지정된 크기를 초과하면 탈출
				fprintf(fout, "\n");
				return;
			}
			if (array[count] == -1) { // 센티널 만나면 탈출
				brk_temp++;
				break;
			}
			fprintf(fout, "%8d", array[count]);
			count++;
		}
		fprintf(fout, "\n");
		if (brk_temp == 1)break;
	}

	if (20 < size && size < 41) { // 20 초과 40 이하인 경우의 배열 출력
		count = num_sample_lines * line_size; // 첫 배열 출력 이후의 값으로 초기값 재설정
		brk_temp = 0;
		for (int i = 0; i < num_sample_lines; i++) {
			for (int j = 0; j < line_size; j++) {
				if (count > size) {
					fprintf(fout, "\n");
					return;
				}
				if (array[count] == -1) {
					brk_temp++;
					break;
				}
				fprintf(fout, "%8d", array[count]);
				count++;
			}
			fprintf(fout, "\n");
			if (brk_temp == 1)break;
		}
	}
	else if (40 < size) { // 40 초과인 경우의 배열 출력
		brk_temp = 0;
		if (count < (size - line_size * num_sample_lines)) // 마지막 부분 출력하도록
			count = size - (line_size * num_sample_lines); // 초기값 재설정
		if (count >= size) return;
		fprintf(fout, "\n   . . . . .\n\n");
		brk_temp = 0;
		for (int i = 0; i < num_sample_lines; i++) {
			for (int j = 0; j < line_size; j++) {
				if (count > size) {
					fprintf(fout, "\n");
					return;
				}
				if (array[count] == -1) {
					brk_temp++;
					break;
				}
				fprintf(fout, "%8d", array[count]);
				count++;
			}
			fprintf(fout, "\n");
			if (brk_temp == 1)break;
		}
		fprintf(fout, "\n");
	}
}

// 30비트 난수 생성
void genBigRandArray(int* array, int size) {
	char* flag; // 난수가 생성되었는지 확인
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand; // 생성된 난수값

	flag = (char*)calloc(size, sizeof(char)); // 동적 할당
	while (count < size) {
		u_int32 = ((long)rand() << 15) | rand();
		bigRand = u_int32 % size;
		if (flag[bigRand] == 1) {
			continue;
		}
		else { // 이미 생성된 난수인지 확인
			flag[bigRand] = 1;
			array[count++] = bigRand;
		}
	}
	free(flag); // 할당 해제
}
void suffleArray(int* array, int size) {
	int i1, i2, d;
	srand((unsigned)time(NULL));

	for (int i = 0; i < size / 2; i++) {
		i1 = (((unsigned long)rand() << 15 | rand())) % size;
		i2 = (((unsigned long)rand() << 15 | rand())) % size;
		// suffle
		d = array[i1];
		array[i1] = array[i2];
		array[i2] = d;
	}
}
// 배열의 속성을 실행창에 출력
void getArrayStatistics(int* array, int size) {
	int data, min, max;
	double sum = 0.0, var, diff, sq_diff_sum = 0.0, avg, std_dev;

	min = INT_MAX;
	max = INT_MIN;
	for (int i = 0; i < size; i++) {
		data = array[i];
		sum += data;
		if (data < min)min = data; // 최소값
		if (data > max)max = data; // 최대값
	}
	avg = sum / (double)size; // 평균
	for (int i = 0; i < size; i++) {
		diff = array[i] - avg;
		sq_diff_sum += diff * diff;
	}
	var = sq_diff_sum / (double)size; // 분산
	std_dev = sqrt(var); // 표준편차
	printf("min (%3d), max (%3d), ", min, max);
	printf("sum (%8.2lf), average (%8.2lf), ", sum, avg);
	printf("variance (%8.2lf), standard deviation (%8.2lf)\n", var, std_dev);
}

// 배열의 속성을 지정된 파일에 출력
void fgetArrayStatistics(FILE* fout, int* array, int size) {
	int data, min, max;
	double sum = 0.0, var, diff, sq_diff_sum = 0.0, avg, std_dev;

	min = INT_MAX;
	max = INT_MIN;
	for (int i = 0; i < size; i++) {
		data = array[i];
		sum += data;
		if (data < min)min = data; // 최소값
		if (data > max)max = data; // 최대값
	}
	avg = sum / (double)size; // 평균
	for (int i = 0; i < size; i++) {
		diff = array[i] - avg;
		sq_diff_sum += diff * diff;
	}
	var = sq_diff_sum / (double)size; // 분산
	std_dev = sqrt(var); // 표준편차
	fprintf(fout, "min (%3d), max (%3d), ", min, max);
	fprintf(fout, "sum (%8.2lf), average (%8.2lf), ", sum, avg);
	fprintf(fout, "variance (%8.2lf), standard deviation (%8.2lf)\n", var, std_dev);
}
void sortArray(int* array, int size) {
	int temp = 0, counts = 0;
	int min = 0;

	for (int is = 0; is < size; is++) {
		min = is;
		for (int js = is + 1; js < size; js++) {
			if (array[min] > array[js]) {
				min = js;
			}
			if (js == size - 1) {
				temp = array[min];
				array[min] = array[is];
				array[is] = temp;
			}
		}
	}
}
#endif