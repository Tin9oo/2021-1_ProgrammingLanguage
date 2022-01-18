/*
* ���ϸ� : main.cpp
* ���� �� �⺻ ���
*	30bit ũ���� ������ �迭�� �����ϰ� ���ϴ� �������� ����Ѵ�.
*   ������ �迭�� ���������� ���� ������������ �����ϰ� ����Ѵ�.
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 4�� 3��
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Array.h"

int main(void) {
	int size;
	int* array_br = NULL;

	printf("Input array size (bigger than 50000) : ");
	scanf("%d", &size);

	array_br = (int*)calloc(size, sizeof(int));
	if (array_br == NULL) {
		printf("Error in dynamic creation of big_array (size = %d) !!!", size);
		exit(1);
	}
	printf("Generating Big Integer array (size = %d). . . .\n", size);
	genBigRandArray(array_br, size, -(size / 2));
	printBigArraySample(array_br, size, 10, 2);
	printf("Sorted Big Integer array (size = %d, offset = %d) : \n", size, -(size / 2));
	selectionSorting(array_br, size);
	printBigArraySample(array_br, size, 10, 2);

	return 0;
}