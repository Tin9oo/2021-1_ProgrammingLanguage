#ifndef BIG_ARRAY_H // ��� �ߺ� ����
#define BIG_ARRAY_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "BigDoubleArray.h"

void printBigArraySample_double(double* dA, int size, int items_per_line, int num_sample_lines) {
	int count = 0; // ���° ������ Ȯ��
	int brk_temp = 0; // ��Ƽ���� ������ Ż��

	size = size / 100 - size / 200 + 1;

	printf("\n");
	for (int i = 0; i < num_sample_lines; i++) { // �⺻ �迭 ���
		for (int j = 0; j < items_per_line; j++) {    // line_size�� ��ŭ num_sample_lines�� ���
			printf("%10.2lf", dA[count]);
			count++;
		}
		printf("\n");
	}

	brk_temp = 0;

	count = size - (items_per_line * num_sample_lines); // �ϵ��� �ʱⰪ �缳��
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
	char* flag; // ������ �����Ǿ����� Ȯ��
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand; // ������ ������
	double* array;

	bigRandSize = (bigRandSize / 100.0) + offset + 1.0;

	array = (double*)calloc(bigRandSize, sizeof(double));
	flag = (char*)calloc(bigRandSize, sizeof(char)); // ���� �Ҵ�
	if (flag == NULL) {
		printf("Error in dynamic creation of big_array (size = %d) !!!", bigRandSize);
	}
	while (count < bigRandSize) {
		u_int32 = ((long)rand() << 15) | rand();
		bigRand = u_int32 % bigRandSize;
		if (flag[bigRand] == 'a') {
			continue;
		}
		else { // �̹� ������ �������� Ȯ��
			flag[bigRand] = 'a';
			array[count++] = (double)bigRand + offset;
		}
	}
	//array[count] = -1.0;
	free(flag); // �Ҵ� ����

	return array;
}
#endif