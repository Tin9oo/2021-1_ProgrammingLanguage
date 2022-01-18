/*
* 파일명 : main.cpp
* 목적 및 기본 기능
*	무작위 실수 배열을 생성하고 해당 배열의 퀵, 선택 정렬의 실행시간을 측정하라
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 4월 23일
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "BigDoubleArray.h"

void main() {
	int size;
	double d_offset;
	double* dA;
	LARGE_INTEGER freq, t1, t2;
	LONGLONG t_diff;
	double t_elapsed_ms;

	QueryPerformanceFrequency(&freq);
	while (1)
	{
		printf("\nTesting big random double array generation and hybrid sorting.\n");
		printf(" Input array size(bigger than 100000; 0 to quit) = ");
		scanf("%d", &size);
		if (size == 0)
			break;
		d_offset = 0.0;
		printf("Generating Big Integer array (size = %8d) . . . . ", size);
		dA = genBigRandArray_double(size, d_offset);
		printf("\nGenerated Big Array of Double Data (size = %8d, offset = %10.2lf):\n", size, d_offset);
		printBigArraySample_double(dA, size, 10, 2);

		QueryPerformanceCounter(&t1);
		hybridSort_QS_SS_double(dA, size);
		QueryPerformanceCounter(&t2);
		t_diff = t2.QuadPart - t1.QuadPart;
		t_elapsed_ms = (double)t_diff / freq.QuadPart;
		printf("Sorted Big Integer array (size = %8d, offset = %8d): \n", size, d_offset);
		printBigArraySample_double(dA, size, 10, 2);
		printf("Hybrid_Selection_QuickSorting took %10.2lf [milli-second] to sort array of %d double - type elements\n", t_elapsed_ms * 1000.0, size);
		free(dA);
	}
}