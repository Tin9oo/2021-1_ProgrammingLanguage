/* Cmplx.h */
#ifndef CMPLX_H
#define CMPLX_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
	double real;
	double imag; // imaginary
} Cmplx;
Cmplx inputCmplx();
double compareCmplx(const Cmplx c1, const Cmplx c2);
void printCmplx(const Cmplx c);
Cmplx cmplxAdd(const Cmplx c1, const Cmplx c2);
Cmplx cmplxSub(const Cmplx c1, const Cmplx c2);
Cmplx cmplxMul(const Cmplx c1, const Cmplx c2);
Cmplx cmplxDiv(const Cmplx c1, const Cmplx c2);
void _sortCmplx(Cmplx cmplxs[], int start, int end);
void sortCmplx(Cmplx cmplxs[], int size);
#endif