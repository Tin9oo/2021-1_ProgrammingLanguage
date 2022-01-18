/*
* ���ϸ� : main.cpp
* ���� �� �⺻ ���
*	������ ó��
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 5�� 17��
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void) {
	FILE* fin, * fout;
	char words[10][16] = { '\0' };
	char temp_word[16] = { '\0' };
	int word_len[10];
	int min;

	fin = fopen("words_input.txt", "r"); // ������ ����
	fout = fopen("words_output.txt", "w"); // ��� ����
	fprintf(fout, "Input word list:\n");
	for (int i = 0; i < 10; i++) {
		fscanf(fin, "%s", words[i]); // ������ �ҷ�����
		word_len[i] = strlen(words[i]); // ���� ����
		fprintf(fout, "(%2d)th-word : %-16s(word_length: %d)\n", i, words[i], word_len[i]);
	}
	for (int i = 0; i < 10; i++) { // ���� ����
		strcpy(temp_word, words[i]);
		min = i;
		for (int j = i + 1; j < 10; j++) {
			if (strcmp(temp_word, words[j]) > 0) {
				min = j;
				strcpy(temp_word, words[j]);
			}
		}
		if (min != i) {
			strcpy(words[min], words[i]);
			strcpy(words[i], temp_word);
		}
	}
	fprintf(fout, "Sorted word list:\n");
	for (int i = 0; i < 10; i++) {
		fprintf(fout, "%-16s", words[i]);
		if (i == 4) fprintf(fout, "\n");
	}
	fclose(fin);
	fclose(fout);
	return 0;
}