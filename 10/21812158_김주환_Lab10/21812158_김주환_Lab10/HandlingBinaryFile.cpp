// HandlingBinaryFile.cpp
#ifndef HB_H
#define HB_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "HandlingBinaryFile.h"

#define BUFFER_LEN 16
#define MAX_FILE_SIZE 256

void dumpBinaryFile(FILE* fin, FILE* fout) {
	int nbytes;
	unsigned char buffer[BUFFER_LEN] = { '\0' };
	for (int addr = 0; addr < MAX_FILE_SIZE; addr += BUFFER_LEN) {
		nbytes = fread(buffer, sizeof(unsigned char), BUFFER_LEN, fin);
		if (nbytes <= 0)
			break;
		fprintf(fout, "%08X: ", addr);
		for (int i = 0; i < nbytes; i++) {
			if (i == (BUFFER_LEN / 2))
				fprintf(fout, " ");
			fprintf(fout, "%02X ", buffer[i]);
		}
		fprintf(fout, " ");
		for (int i = 0; i < nbytes; i++) {
			if (isprint(buffer[i]))
				fprintf(fout, "%c", buffer[i]);
			else
				fprintf(fout, ".");
		}
		fprintf(fout, "\n");
	}
}
#endif