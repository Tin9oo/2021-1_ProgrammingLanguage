/*
* 파일명 : main.cpp
* 목적 및 기본 기능
*	무작위 문자열을 생성하고 선택정렬과 퀵정렬을 각각 실행하여 속도를 비교하고 파일에 출력하라
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 4월 12일
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include "WordArray.h"

void main() {
	extern char words[][MAX_WORD_LEN];
	LARGE_INTEGER freq, t1, t2;
	LONGLONG t_diff;
	double elapsed_t;
	FILE* fout;

	fout = fopen("output.txt", "w"); // 파일 쓰기모드로 열기
	if (fout == NULL) {
		printf("Error in creation of output.txt file !!\n");
		exit(-1);
	}

	srand(time(NULL)); // 시드값 설정
	QueryPerformanceFrequency(&freq); // 주파수 값
	printf("Performance Analysis of Sorting Algorithms\n");
	for (int num_words = 10000; num_words <= 100000; num_words += 10000) {
		printf("Word array(size : %7d) : ", num_words);
		fprintf(fout, "\n=================================================================================\n");
		genRandWordArray(words, num_words); // 무작위 문자열 생성
		fprintf(fout, "Randomly generated Word Array (size : %d)\n", num_words);
		fprintBigWordArray(fout, words, num_words, WORDS_PER_LINE, SAMPLE_LINES);

		fprintf(fout, "\nQuick sorting for Word Array (size : %d) .....\n", num_words);
		QueryPerformanceCounter(&t1); // 이전시간
		quickSortWordArray(words, num_words, 0, num_words - 1); // 퀵정렬
		QueryPerformanceCounter(&t2); // 이후시간

		t_diff = t2.QuadPart - t1.QuadPart;
		elapsed_t = ((double)t_diff / freq.QuadPart);
		fprintf(fout, "QuickSort_WordArray (size : %d) took %10.3lf[millisecond], ", num_words, elapsed_t * 1000.0); // 밀리초 단위로 출력
		printf("QuickSort (%10.3lf ms), ", elapsed_t * 1000.0);

		fprintf(fout, "\nAfter sorting word array (size : %d)\n", num_words);
		fprintBigWordArray(fout, words, num_words, WORDS_PER_LINE, SAMPLE_LINES);
		fprintf(fout, "\n");

		shuffleWordArray(words, num_words, num_words); // 문자열 섞기
		fprintf(fout, "Word Array (size : %d) after Shuffling\n", num_words);
		fprintBigWordArray(fout, words, num_words, WORDS_PER_LINE, SAMPLE_LINES);

		fprintf(fout, "\nSelection sorting for Word Array (size : %d) .....\n", num_words);
		QueryPerformanceCounter(&t1); // 이전시간
		selectionSortWordArray(words, num_words); // 선택정렬
		QueryPerformanceCounter(&t2); // 이후시간
		t_diff = t2.QuadPart - t1.QuadPart;
		elapsed_t = ((double)t_diff / freq.QuadPart);
		fprintf(fout, "SelectionSort_WordArray (size : %d) took %10.3lf [millisecond]\n", num_words, elapsed_t * 1000.0); // 밀리초 단위로 출력
		printf("Select_Sort (%10.3lf ms)\n", elapsed_t * 1000.0);
		fprintf(fout, "\nAfter sorting word array (size : %d)\n", num_words);
		fprintBigWordArray(fout, words, num_words, WORDS_PER_LINE, SAMPLE_LINES);
		fprintf(fout, "\n");
	}
	fclose(fout); // 파일 닫기
}