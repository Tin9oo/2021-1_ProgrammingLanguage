#ifndef BIG_ARRAY_H // 헤더 중복 방지
#define BIG_ARRAY_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "BigDoubleArray.h"

void printBigArraySample_double(double* dA, int size, int items_per_line, int num_sample_lines) {
	int count = 0; // 몇번째 수인지 확인
	int brk_temp = 0; // 센티널을 만나면 탈출

	size = size - size / 200 + 1;

	printf("\n");
	for (int i = 0; i < num_sample_lines; i++) { // 기본 배열 출력
		for (int j = 0; j < items_per_line; j++) {    // line_size개 만큼 num_sample_lines줄 출력
			printf("%10.2lf", dA[count]);
			count++;
		}
		printf("\n");
	}

	brk_temp = 0;

	count = size - (items_per_line * num_sample_lines); // 하도록 초기값 재설정
	printf("\n   . . . . .\n\n");
	brk_temp = 0;
	for (int i = 0; i < num_sample_lines; i++) {
		for (int j = 0; j < items_per_line; j++) {
			printf("%10.2lf", dA[count]);
			count++;
		}
		printf("\n");
	}
	printf("\n");
}
double* genBigRandArray_double(int bigRandSize, double offset) {
	char* flag; // 난수가 생성되었는지 확인
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand; // 생성된 난수값
	double* array;

	bigRandSize = (bigRandSize) + offset + 1.0;

	srand(time(NULL));
	array = (double*)calloc(bigRandSize, sizeof(double));
	flag = (char*)calloc(bigRandSize, sizeof(char)); // 동적 할당
	if (flag == NULL) {
		printf("Error in dynamic creation of big_array (size = %d) !!!", bigRandSize);
	}
	while (count < bigRandSize) {
		u_int32 = ((long)rand() << 15) | rand();
		bigRand = u_int32 % bigRandSize;
		if (flag[bigRand] == 'a') {
			continue;
		}
		else { // 이미 생성된 난수인지 확인
			flag[bigRand] = 'a';
			array[count++] = ((double)bigRand + offset) / 100.0;
		}
	}
	//array[count] = -1.0;
	free(flag); // 할당 해제

	return array;
}
void _hybridSort_QS_SS_double(double* array, int size, int left, int right) {
	if (right - left + 1 <= 50) {
		double temp = 0.0;
		int min = 0;

		for (int is = 0; is < right - left + 1; is++) {
			min = is;
			for (int js = is + 1; js < right - left + 1; js++) {
				if (array[min] > array[js]) {
					min = js;
				}
				if (js == right - 1) {
					temp = array[min];
					array[min] = array[is];
					array[is] = temp;
				}
			}
		}
		return;
	}
	int pi, new_pi, i;
	double pivot_value;
	double temp;

	pi = (left + right) / 2;

	pivot_value = array[pi];

	temp = array[pi];
	array[pi] = array[right];
	array[right] = temp;
	new_pi = left;
	for (i = left; i <= (right - 1); i++) {
		if (array[i] <= pivot_value) {
			temp = array[i];
			array[i] = array[new_pi];
			array[new_pi] = temp;
			new_pi++;
		}
	}

	temp = array[new_pi];
	array[new_pi] = array[right];
	array[right] = temp;

	_hybridSort_QS_SS_double(array, size, left, new_pi - 1);
	_hybridSort_QS_SS_double(array, size, new_pi + 1, right);
}
void hybridSort_QS_SS_double(double* dA, int size) {
	_hybridSort_QS_SS_double(dA, size, 0, size - 1);
}
#endif