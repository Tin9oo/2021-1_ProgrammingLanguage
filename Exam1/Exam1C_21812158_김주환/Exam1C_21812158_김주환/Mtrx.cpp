#ifndef MD
#define MD
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE 5

void inputMtrx(FILE* fin, double M[][SIZE]) {
	double data;
	fscanf(fin, "%lf %lf");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			fscanf(fin, "%lf", &data);
			M[i][j] = data;
		}
	}
	//fscanf(fin, "%lf");
}
void printMtrx(double M[][SIZE], int size) {
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((i == 0) && (j == 0)) {
				printf("%c%c%7.2lf", a6, a3, M[i][j]);
			}
			else if ((i == 0) && j == (size - 1)) {
				printf("%7.2lf%c%c", M[i][j], a6, a4);
			}
			else if ((i > 0) && (i < size - 1) && (j == 0)) {
				printf("%c%c%7.2lf", a6, a2, M[i][j]);
			}
			else if ((i > 0) && (i < size - 1) && (j == (size - 1))) {
				printf("%7.2lf%c%c", M[i][j], a6, a2);
			}
			else if ((i == size - 1) && (j == 0)) {
				printf("%c%c%7.2lf", a6, a6, M[i][j]);
			}
			else if ((i == size - 1) && (j == (size - 1))) {
				printf("%7.2lf%c%c", M[i][j], a6, a5);
			}
			else {
				printf("%7.2lf", M[i][j]);
			}
		}
		printf("\n");
	}
}

void addMtrx(double A[][SIZE], double B[][SIZE], double C[][SIZE], int size) {
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			C[row][col] = A[row][col] + B[row][col];
		}
	}
	printMtrx(C, size);
}
void subMtrx(double A[][SIZE], double B[][SIZE], double D[][SIZE], int size) {
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			D[row][col] = A[row][col] - B[row][col];
		}
	}
	printMtrx(D, size);
}
void mulMtrx(double A[][SIZE], double B[][SIZE], double E[][SIZE], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			E[i][j] = 0;
			for (int k = 0; k < size; k++) {
				E[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	printMtrx(E, size);
}

#endif