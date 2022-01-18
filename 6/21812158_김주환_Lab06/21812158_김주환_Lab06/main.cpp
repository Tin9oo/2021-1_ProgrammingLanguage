/*
* 파일명 : main.c
* 목적 및 기본 기능
*	기본 배열, 외부 배열, 파일 데이터, 입력 배열, 무작위 배열 중 하나를 선택하여
*   원소 데이터와 배열의 통계 정보를 형식에 맞춰 실행창과 파일에 출력한다.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 4월 2일
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "BigArray.h"

#define ESC 0x1B

void Compare_Sorting_Algorithms_SmallIntArray(FILE* fout);
void testBigRandArray(FILE* fout);
void PM_Hybrid_QS_SS_IntArray(FILE* fout);

int main(void) {
	FILE* fout;
	int menu;
	fout = fopen("output.txt", "w");
	if (fout == NULL) {
		printf("Error in creation of array_output.txt !!\n");
		return -1;
	}
	while (1) {
		fprintf(fout, "\nTest Array Algorithms :\n");
		printf("\nTest Array Algorithms :\n");
		fprintf(fout, "   1: Performance Comparison of Selection Sort and Quick Sort for Small Integer Array\n");
		printf("   1: Performance Comparison of Selection Sort and Quick Sort for Small Integer Array\n");
		fprintf(fout, "   2: Test Big Rand Array (Array Size : 1,000,000 ~ 10,000,000)\n");
		printf("   2: Test Big Rand Array (Array Size : 1,000,000 ~ 10,000,000)\n");
		fprintf(fout, "   3: Performance Measurements of hybrid_QS_SS for Integer Array\n");
		printf("   3: Performance Measurements of hybrid_QS_SS for Integer Array\n");
		fprintf(fout, "Input menu (-1 to terminate) : ");
		printf("Input menu (-1 to terminate) : ");
		scanf("%d", &menu);
		printf("\n");
		fprintf(fout, "%d\n", menu);
		if (menu == -1) break;
		switch (menu) {
		case 1:
			Compare_Sorting_Algorithms_SmallIntArray(fout);
			break;
		case 2:
			testBigRandArray(fout);
			break;
		case 3:
			PM_Hybrid_QS_SS_IntArray(fout);
			break;
		default:
			break;
		}
		fflush(fout);
	}
	fclose(fout);
	return 0;
}


void Compare_Sorting_Algorithms_SmallIntArray(FILE* fout) {
	int* array;
	LARGE_INTEGER freq, t1, t2;
	LONGLONG t_diff;
	double elapsed_time;

	QueryPerformanceFrequency(&freq);
	srand(time(NULL));
	for (int size = 5; size <= 200; size += 5) {
		array = (int*)calloc(size + 1, sizeof(int));
		if (array == NULL) {
			fprintf(fout, "Error in memory allocation for big_array of size (%d) !!!\n", size);
			printf("Error in memory allocation for big_array of size (%d) !!!\n", size);
			return;
		}
		genBigRandArray(array, size, 0);
		fprintf(fout, "Sorting of an integer array (size : %3d) : ", size);
		printf("Sorting of an integer array (size : %3d) : ", size);
		QueryPerformanceCounter(&t1);
		quickSort(array, size, 0, size - 1);
		QueryPerformanceCounter(&t2);
		t_diff = t2.QuadPart - t1.QuadPart;
		elapsed_time = (double)t_diff / freq.QuadPart;
		fprintf(fout, "Quick_Sort took %10.2lf [milliseconds], ", elapsed_time * 1000.0);
		printf("Quick_Sort took %10.2lf [milliseconds], ", elapsed_time * 1000.0);

		suffleArray(array, size);
		// printf("Quick sorting of an integer array (size : %7d) . . . .", size);
		QueryPerformanceCounter(&t1);
		selectionSort(array, size);
		QueryPerformanceCounter(&t2);
		t_diff = t2.QuadPart - t1.QuadPart;
		elapsed_time = (double)t_diff / freq.QuadPart;
		fprintf(fout, "Selection_Sort took %10.2lf [milliseconds]\n", elapsed_time * 1000.0);
		printf("Selection_Sort took %10.2lf [milliseconds]\n", elapsed_time * 1000.0);
		free(array);
	}
}
void testBigRandArray(FILE* fout) {
	int size = 5000000;
	int* array = NULL;

	for (; size <= 10000000; size += 5000000) {
		array = (int*)calloc(size + 1, sizeof(int));
		if (array == NULL) {
			printf("Error in dynamic creation of big_array (size = %d) !!!", size);
		}
		fprintf(fout, "Testing Big integer Random Arrays(size = 1,000,000 ~ 10,000,000) :\n");
		printf("Testing Big integer Random Arrays(size = 1,000,000 ~ 10,000,000) :\n");
		fprintf(fout, "Generating Big Integer array (size = %d) . . . .\n", size);
		printf("Generating Big Integer array (size = %d) . . . .\n", size);
		fprintf(fout, "Generated Big Integer array (size = %d) :\n", size);
		printf("Generated Big Integer array (size = %d) :\n", size);
		genBigRandArray(array, size, 0);
		printBigArraySample(array, size);
		fprintf(fout, "Sorted Big Integer array (size = %d) :\n", size);
		printf("Sorted Big Integer array (size = %d) :\n", size);
		quickSort(array, size, 0, size - 1);
		printBigArraySample(array, size);
		free(array);
	}
}
void PM_Hybrid_QS_SS_IntArray(FILE* fout) {
	int size = 1000000;

	int* array;
	LARGE_INTEGER freq, t1, t2;
	LONGLONG t_diff;
	double elapsed_time;

	QueryPerformanceFrequency(&freq);
	srand(time(NULL));
	for (; size <= 10000000; size += 1000000) {
		array = (int*)calloc(size + 1, sizeof(int));
		if (array == NULL) {
			fprintf(fout, "Error in memory allocation for big_array of size (%d) !!!\n", size);
			printf("Error in memory allocation for big_array of size (%d) !!!\n", size);
			return;
		}
		genBigRandArray(array, size, 0);
		fprintf(fout, "hybrid_QS_SS sorting of an integer array (size : %3d) : ", size);
		printf("hybrid_QS_SS sorting of an integer array (size : %3d) : ", size);
		QueryPerformanceCounter(&t1);
		hybridQuickSelectionSort(array, size);
		QueryPerformanceCounter(&t2);
		t_diff = t2.QuadPart - t1.QuadPart;
		elapsed_time = (double)t_diff / freq.QuadPart;
		fprintf(fout, "hybrid_QS_SS sort took %11.2lf [milliseconds], ", elapsed_time * 1000.0);
		printf("hybrid_QS_SS sort took %11.2lf [milliseconds], ", elapsed_time * 1000.0);

		suffleArray(array, size);
		QueryPerformanceCounter(&t1);
		quickSort(array, size, 0, size - 1);
		QueryPerformanceCounter(&t2);
		t_diff = t2.QuadPart - t1.QuadPart;
		elapsed_time = (double)t_diff / freq.QuadPart;
		fprintf(fout, "Quick_Sort took %10.2lf [milliseconds]\n", elapsed_time * 1000.0);
		printf("Quick_Sort took %10.2lf [milliseconds]\n", elapsed_time * 1000.0);

		free(array);
	}
}