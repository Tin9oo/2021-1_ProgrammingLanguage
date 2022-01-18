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

	size = size / 100 - size / 200 + 1;

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

	bigRandSize = (bigRandSize / 100.0) + offset + 1.0;

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
			array[count++] = (double)bigRand + offset;
		}
	}
	//array[count] = -1.0;
	free(flag); // 할당 해제

	return array;
}
#endif