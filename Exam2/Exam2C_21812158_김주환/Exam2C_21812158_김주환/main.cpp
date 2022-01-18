#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Matrix_double.h"

void main() {
	FILE* fin, * fout;
	const char* input_file = "mtrx_5x5.txt";
	const char* output_file = "mtrx_5x5_row_col_avgs.txt";
	int row_size, col_size;

	double** dM;
	double** dM_avg;

	fin = fopen(input_file, "r");
	if (fin == NULL)
	{
		printf("Error in opening input data file (%s) !!", input_file);
		exit;
	}

	fout = fopen(output_file, "w");
	if (fout == NULL)
	{
		printf("Error in opening output data file (%s) !!", output_file);
		exit;
	}

	dM = fGetMtrx_double(fin, &row_size, &col_size);
	printMtrx_double((const char*)"Matrix M", dM, row_size, col_size);
	dM_avg = CalcRowColAvg_double(dM, row_size, col_size);
	printMtrx_double((const char*)"Matrix M with row/col averages", dM_avg,
		row_size + 1, col_size + 1);
	fprintMtrx_double(fout, (const char*)"Matrix M with row/col averages",
		dM_avg, row_size + 1, col_size + 1);

	fclose(fin);
	fclose(fout);
	free(dM);
	free(dM_avg);
}