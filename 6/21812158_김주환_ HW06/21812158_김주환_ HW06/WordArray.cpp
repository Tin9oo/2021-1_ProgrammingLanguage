// WordArray.cpp
#ifndef WA // ��� �ߺ� ����
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
	char temp[MAX_WORD_LEN] = ""; // ���ۿ���
	int len = 0; // ������ ���ڿ��� ����
	int j;
	
	for (int i = 0; i < num_words; i++) {
		len = rand() % 10 + 5; // ���ڿ� ����
		temp[0] = rand() % 26 + 65; // �빮��
		for (j = 1; j < len; j++) { // �ҹ���
			temp[j] = rand() % 26 + 97;
		}
		temp[j] = NULL; // ��Ƽ��
		strcpy(words[i], temp); // ���ڿ� ����
	}
}
void fprintBigWordArray(FILE* fout, char wordList[][MAX_WORD_LEN], int size, int words_per_line = 10, int sample_lines = 5) {
	int cnt = 0; // ������ ����ߴ��� Ȯ��

	for (int i = 0; i < sample_lines; i++) { // �պκ� 50�ܾ�
		for (int j = 0; j < words_per_line; j++) {
			fprintf(fout, "%-25s", wordList[cnt++]);
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, ". . . . .\n"); // �߰� �ٸ�
	cnt = size - 50;
	for (int i = 0; i < sample_lines; i++) { // �޺κ� 50�ܾ�
		for (int j = 0; j < words_per_line; j++) {
			fprintf(fout, "%-25s", wordList[cnt++]);
		}
		fprintf(fout, "\n");
	}
}
void selectionSortWordArray(char word[][MAX_WORD_LEN], int num_words) {
	char temp[MAX_WORD_LEN]; // ���ۿ���
	int min_pos;

	for (int pos = 0; pos < num_words; pos++) { // ����
		min_pos = pos;
		for (int j = pos + 1; j < num_words; j++) { // �񱳴��
			if (strcmp(word[min_pos], word[j]) > 0) min_pos = j; // ������ �Ǵ�
		}
		if (min_pos != pos) { // ���� �� ��ȯ
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
	else if (left < right)pi = (left + right) / 2; // �ǹ� ����

	strcpy(pi_v, word[pi]); // �ǹ� ��

	strcpy(temp, word[pi]); // ������ ���� ��ȯ
	strcpy(word[pi], word[right]);
	strcpy(word[right], temp);
	n_pi = left; // ó������ ����
	for (i = left; i <= (right - 1); i++) { // �ϳ��� �Űܰ��� �Ǵ�
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