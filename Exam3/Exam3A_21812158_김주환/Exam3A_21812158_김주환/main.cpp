/* main() - (Gauss-Jordan Elimination for Linear System) */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Mtrx.h"
#include "Gauss-Jordan.h"

int main()
{
	int menu;
	FILE * fin, * fout;
	const char* mtrx_file_name = "augMtrx_data.txt";
	const char* fout_name = "output.txt";
	int solExist = 1;
	double* pSolution;
	Mtrx augMtrx, * pMtrx = NULL;
	
	 fin = fopen(mtrx_file_name, "r");
	if (fin == NULL)
	{
	printf("Error in opening %s input data file !!\n", mtrx_file_name);
	exit(-1);
	}
	// augMtrx.n_col = 0; augMtrx.n_row = 0;
	pMtrx = fgetMtrx(fin, &augMtrx);
	strcpy(pMtrx->name, "AugMtrx");
	printMtrx(pMtrx);
	fout = fopen(fout_name, "w");
	if (fout == NULL)
	{
	printf("Error in opening output file (%s) !!\n", fout_name);
	return -1;
	}
	if (pMtrx == NULL)
	{
	printf("Error in GaussJordanElimination() :: pMtrx is NULL !!\n");
	return -1;
	}
	pSolution = (double*)calloc(pMtrx->n_row, sizeof(double));
	printf("Calling diagonalize_FileOut() ... \n");
	diagonalize_FileOut(fout, pMtrx, &solExist);
	if (solExist) {
		printf("The solution of the given linear system:\n");
		for (int r = 0; r < pMtrx->n_row; r++) {
			pSolution[r] = pMtrx->dM[r][pMtrx->n_row];
			printf(" i_%d = %7.2lf\n", r + 1, pSolution[r]);
		}
	}
	else {
		printf("No unique solution\n");
	}
	fclose(fin);
	fclose(fout);
	return 0;
}