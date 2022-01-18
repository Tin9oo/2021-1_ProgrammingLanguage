#ifndef MD
#define MD
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE 5

void inputMtrx(FILE* fin, double M[][SIZE]);
void printMtrx(double M[][SIZE], int size);

void addMtrx(double A[][SIZE], double B[][SIZE], double C[][SIZE], int size);
void subMtrx(double A[][SIZE], double B[][SIZE], double D[][SIZE], int size);
void mulMtrx(double A[][SIZE], double B[][SIZE], double E[][SIZE], int size);

#endif