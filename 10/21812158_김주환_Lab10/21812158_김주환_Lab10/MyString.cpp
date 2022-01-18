// MyString.cpp
#ifndef MS_H
#define MS_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "MyString.h"

void selectionSortWords(char** words, int num_words) {
	char* temp_word;
	int i, j, min;

	temp_word = (char*)calloc(num_words, sizeof(char));
	if (temp_word == NULL) {
		printf("Error in dynamic allocation of memory for temp_word !!\n");
		exit;
	}

	for (i = 0; i < num_words; i++) {
		strcpy(temp_word, words[i]);
		min = i;
		for (j = i + 1; j < num_words; j++) {
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
}
#endif