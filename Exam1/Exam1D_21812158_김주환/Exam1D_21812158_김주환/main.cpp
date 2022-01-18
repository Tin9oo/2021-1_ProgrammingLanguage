/*
* 파일명 : main.cpp
* 목적 및 기본 기능
*	30bit 크기의 무작위 배열을 생성하고 원하는 포멧으로 출력한다.
*   생성한 배열을 선택정렬을 통해 오름차순으로 정렬하고 출력한다.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 4월 3일
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