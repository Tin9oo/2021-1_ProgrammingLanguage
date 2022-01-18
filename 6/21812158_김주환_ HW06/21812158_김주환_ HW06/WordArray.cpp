// WordArray.cpp
#ifndef WA // 헤더 중복 방지
#define WA

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string.h>

#define MAX_WORD_LEN 16
#define MAX_NUM_WORDS 100000
#define WORDS_PER_LINE 10
#define SAMPLE_LINES 5

void genRandWordArray(char words[][MAX_WORD_LEN], int num_words) {
	char temp[MAX_WORD_LEN] = ""; // 버퍼역할
	int len = 0; // 생성할 문자열의 길이
	int j;
	
	for (int i = 0; i < num_words; i++) {
		len = rand() % 10 + 5; // 문자열 길이
		temp[0] = rand() % 26 + 65; // 대문자
		for (j = 1; j < len; j++) { // 소문자
			temp[j] = rand() % 26 + 97;
		}
		temp[j] = NULL; // 센티널
		strcpy(words[i], temp); // 문자열 복사
	}
}
void fprintBigWordArray(FILE* fout, char wordList[][MAX_WORD_LEN], int size, int words_per_line = 10, int sample_lines = 5) {
	int cnt = 0; // 어디까지 출력했는지 확인

	for (int i = 0; i < sample_lines; i++) { // 앞부분 50단어
		for (int j = 0; j < words_per_line; j++) {
			fprintf(fout, "%-25s", wordList[cnt++]);
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, ". . . . .\n"); // 중간 다리
	cnt = size - 50;
	for (int i = 0; i < sample_lines; i++) { // 뒷부분 50단어
		for (int j = 0; j < words_per_line; j++) {
			fprintf(fout, "%-25s", wordList[cnt++]);
		}
		fprintf(fout, "\n");
	}
}
void selectionSortWordArray(char word[][MAX_WORD_LEN], int num_words) {
	char temp[MAX_WORD_LEN]; // 버퍼역할
	int min_pos;

	for (int pos = 0; pos < num_words; pos++) { // 기준
		min_pos = pos;
		for (int j = pos + 1; j < num_words; j++) { // 비교대상
			if (strcmp(word[min_pos], word[j]) > 0) min_pos = j; // 작은지 판단
		}
		if (min_pos != pos) { // 작을 때 교환
			strcpy(temp, word[pos]);
			strcpy(word[pos], word[min_pos]);
			strcpy(word[min_pos], temp);
		}
	}
}
void quickSortWordArray(char word[][MAX_WORD_LEN], int num_words, int left, int right) {
	int pi, n_pi;
	char pi_v[MAX_WORD_LEN] = "";
	char temp[MAX_WORD_LEN] = "";
	int i;

	if (left >= right)return;
	else if (left < right)pi = (left + right) / 2; // 피벗 설정

	strcpy(pi_v, word[pi]); // 피벗 값

	strcpy(temp, word[pi]); // 마지막 값과 교환
	strcpy(word[pi], word[right]);
	strcpy(word[right], temp);
	n_pi = left; // 처음부터 시작
	for (i = left; i <= (right - 1); i++) { // 하나씩 옮겨가며 판단
		if (strcmp(word[i], pi_v) <= 0) {
			strcpy(temp, word[i]);
			strcpy(word[i], word[n_pi]);
			strcpy(word[n_pi], temp);
			n_pi++;
		}
	}
	strcpy(temp, word[n_pi]);
	strcpy(word[n_pi], word[right]);
	strcpy(word[right], temp);

	if (left < (n_pi - 1))quickSortWordArray(word, num_words, left, n_pi - 1);
	if ((n_pi + 1) < right)quickSortWordArray(word, num_words, n_pi + 1, right);
}
void shuffleWordArray(char word[][MAX_WORD_LEN], int num_words, int cnt) {
	int t1, t2;
	char t3[MAX_WORD_LEN] = "";
	
	for (int i = 0; i < num_words/2; i++) {
		t1 = rand() % cnt;
		t2 = rand() % cnt;

		strcpy(t3, word[t1]);
		strcpy(word[t1], word[t2]);
		strcpy(word[t2], t3);
	}
}
#endif