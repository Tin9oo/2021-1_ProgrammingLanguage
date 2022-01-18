/*
* ���ϸ� : main.c
* ���� �� �⺻ ���
*	ū ũ���� �Ǽ� ������ �迭 ���� �� ���
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 4�� 23��
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "BigDoubleArray.h"

void main() {
	int size;
	double d_offset;
	double* bigArray_double;

	while (1) {
		printf("\nTesting big random double array generation and hybrid sorting.\n");
		printf(" Input array size(bigger than 100000; 0 to quit) = ");
		scanf("%d", &size);
		if (size == 0)
			break;
		bigArray_double = (double*)calloc(size, sizeof(double));
		d_offset = -(double)size / 200.0;
		printf("Generating big double array (size = %8d) . . . . ", size);
		bigArray_double = genBigRandArray_double(size, d_offset);
		printf("\nGenerated big array of double Data (size = %8d, offset = %10.2lf)\n", size, d_offset);
		printBigArraySample_double(bigArray_double, size, 10, 2);
		free(bigArray_double);
	}
}