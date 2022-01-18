/*
* ���ϸ� : main.cpp
* ���� �� �⺻ ���
*	������ ���ڿ��� �����ϰ� �������İ� �������� ���� �����Ͽ� �ӵ��� ���ϰ� ���Ͽ� ����϶�
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 4�� 12��
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

	fout = fopen("output.txt", "w"); // ���� ������� ����
	if (fout == NULL) {
		printf("Error in creation of output.txt file !!\n");
		exit(-1);
	}

	srand(time(NULL)); // �õ尪 ����
	QueryPerformanceFrequency(&freq); // ���ļ� ��
	printf("Performance Analysis of Sorting Algorithms\n");
	for (int num_words = 10000; num_words <= 100000; num_words += 10000) {
		printf("Word array(size : %7d) : ", num_words);
		fprintf(fout, "\n=================================================================================\n");
		genRandWordArray(words, num_words); // ������ ���ڿ� ����
		fprintf(fout, "Randomly generated Word Array (size : %d)\n", num_words);
		fprintBigWordArray(fout, words, num_words, WORDS_PER_LINE, SAMPLE_LINES);

		fprintf(fout, "\nQuick sorting for Word Array (size : %d) .....\n", num_words);
		QueryPerformanceCounter(&t1); // �����ð�
		quickSortWordArray(words, num_words, 0, num_words - 1); // ������
		QueryPerformanceCounter(&t2); // ���Ľð�

		t_diff = t2.QuadPart - t1.QuadPart;
		elapsed_t = ((double)t_diff / freq.QuadPart);
		fprintf(fout, "QuickSort_WordArray (size : %d) took %10.3lf[millisecond], ", num_words, elapsed_t * 1000.0); // �и��� ������ ���
		printf("QuickSort (%10.3lf ms), ", elapsed_t * 1000.0);

		fprintf(fout, "\nAfter sorting word array (size : %d)\n", num_words);
		fprintBigWordArray(fout, words, num_words, WORDS_PER_LINE, SAMPLE_LINES);
		fprintf(fout, "\n");

		shuffleWordArray(words, num_words, num_words); // ���ڿ� ����
		fprintf(fout, "Word Array (size : %d) after Shuffling\n", num_words);
		fprintBigWordArray(fout, words, num_words, WORDS_PER_LINE, SAMPLE_LINES);

		fprintf(fout, "\nSelection sorting for Word Array (size : %d) .....\n", num_words);
		QueryPerformanceCounter(&t1); // �����ð�
		selectionSortWordArray(words, num_words); // ��������
		QueryPerformanceCounter(&t2); // ���Ľð�
		t_diff = t2.QuadPart - t1.QuadPart;
		elapsed_t = ((double)t_diff / freq.QuadPart);
		fprintf(fout, "SelectionSort_WordArray (size : %d) took %10.3lf [millisecond]\n", num_words, elapsed_t * 1000.0); // �и��� ������ ���
		printf("Select_Sort (%10.3lf ms)\n", elapsed_t * 1000.0);
		fprintf(fout, "\nAfter sorting word array (size : %d)\n", num_words);
		fprintBigWordArray(fout, words, num_words, WORDS_PER_LINE, SAMPLE_LINES);
		fprintf(fout, "\n");
	}
	fclose(fout); // ���� �ݱ�
}