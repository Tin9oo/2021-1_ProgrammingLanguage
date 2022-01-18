/*
* 파일명 : calc_matrix.c
* 목적 및 기본 기능
*	2개의 5 X 5 크기의 행렬 A, B의 덧셈, 뺄셈, 곱셈을 계산하여
*   그 결과를 C, D, E에 저장하는 핼렬 연산 함수 3개를 작성하라.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 3월 18일
*/
#include <stdio.h>

#define SIZE 5
#define ROW 5
#define COL 5

void addMtrx(double A[][SIZE], double B[][SIZE], double X[][SIZE], int size);
void subMtrx(double A[][SIZE], double B[][SIZE], double X[][SIZE], int size);
void mulMtrx(double A[][SIZE], double B[][SIZE], double X[][SIZE], int size);
void printMtrx(double M[][SIZE], int size);

int main(void) {
	double A[ROW][COL] = { 0 };
	double B[ROW][COL] = { 0 };
	double X[ROW][COL] = { 0 };

	int num = 1;

	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			if (row == col) {
				B[row][col] = 1.0;
			}
			A[row][col] = num;
			num += 1;
		}
	}
	printf("Mtrx A :\n");
	printMtrx(A, SIZE);
	printf("Mtrx B :\n");
	printMtrx(B, SIZE);

	printf("Mtrx A + B :\n");
	addMtrx(A, B, X, SIZE);
	printf("Mtrx A - B :\n");
	subMtrx(A, B, X, SIZE);
	printf("Mtrx A * B :\n");
	mulMtrx(A, B, X, SIZE);

	return 0;
}
void addMtrx(double A[][SIZE], double B[][SIZE], double X[][SIZE], int size) {
	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			X[row][col] = A[row][col] + B[row][col];
		}
	}
	printMtrx(X, size);
}
void subMtrx(double A[][SIZE], double B[][SIZE], double X[][SIZE], int size) {
	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			X[row][col] = A[row][col] - B[row][col];
		}
	}
	printMtrx(X, size);
}
void mulMtrx(double A[][SIZE], double B[][SIZE], double X[][SIZE], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			X[i][j] = 0;
			for (int k = 0; k < size; k++) {
				X[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	printMtrx(X, size);
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