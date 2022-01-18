// WordArray.h
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

void genRandWordArray(char words[][MAX_WORD_LEN], int num_words);
void fprintBigWordArray(FILE* fout, char wordList[][MAX_WORD_LEN], int size, int words_per_line = 10, int sample_lines = 5);
void selectionSortWordArray(char word[][MAX_WORD_LEN], int num_words);
void quickSortWordArray(char word[][MAX_WORD_LEN], int num_words, int left, int right);
void shuffleWordArray(char word[][MAX_WORD_LEN], int num_words, int cnt);
#endif