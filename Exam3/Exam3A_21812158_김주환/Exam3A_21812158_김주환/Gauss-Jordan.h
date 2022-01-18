/* Gauss-Jordan.h*/
#ifndef GAUSS_JORDAN_H
#define GAUSS_JORDAN_H
#include <stdio.h>
#include <math.h>
#include "Mtrx.h"
#define EPSILON 0.000001

void pivoting(Mtrx * pMtrx, int p, int* piv_found);
void diagonalize_FileOut(FILE * fout, Mtrx * pMtrx, int* solExist);
#endif