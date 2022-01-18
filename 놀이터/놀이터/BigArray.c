#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "BigArray.h"

#define Data_Input_File "Data_input.txt"
#define Data_Output_File "Data_output.txt"

void printBigArraySample(int* array, int size, int line_size, int num_sample_lines) {
	if (size < 21) {
		int count = 0;
		int brk_temp = 0;
		for (int i = 0; i < num_sample_lines; i++) {
			for (int j = 0; j < line_size; j++) {
				if (count > size) {
					printf("\n");
					return;
				}
				if (array[count] == -1) {
					brk_temp++;
					break;
				}
				printf("%8d", array[count]);
				count++;
			}
			if (brk_temp == 1)break;
			printf("\n");
		}
	}
	else if (size < 41) {
		int count = 0;
		int brk_temp = 0;
		for (int i = 0; i < 2 * num_sample_lines; i++) {
			for (int j = 0; j < line_size; j++) {
				if (count > size) {
					printf("\n");
					return;
				}
				if (array[count] == -1) {
					brk_temp++;
					break;
				}
				printf("%8d", array[count]);
				count++;
			}
			if (brk_temp == 1)break;
			printf("\n");
		}
	}
	else {
		int count = 0;
		int brk_temp = 0;
		for (int i = 0; i < num_sample_lines; i++) {
			for (int j = 0; j < line_size; j++) {
				if (count > size) {
					printf("\n");
					return;
				}
				if (array[count] == -1) {
					brk_temp++;
					break;
				}
				printf("%8d", array[count]);
				count++;
			}
			if (brk_temp == 1)break;
			printf("\n");
		}
		if (brk_temp == 1)return;

		if (count < (size - line_size * num_sample_lines))
			count = size - (line_size * num_sample_lines);
		if (count >= size) return;
		printf("\n   . . . . .\n");
		brk_temp = 0;
		for (int i = 0; i < num_sample_lines; i++) {
			for (int j = 0; j < line_size; j++) {
				if (count > size) {
					printf("\n");
					return;
				}
				if (array[count] == -1) {
					brk_temp++;
					break;
				}
				printf("%8d", array[count]);
				count++;
			}
			printf("\n");
			if (brk_temp == 1)break;
		}
		printf("\n");
	}
}
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int num_sample_lines) {
	if (size < 21) {
		int count = 0;
		int brk_temp = 0;
		for (int i = 0; i < num_sample_lines; i++) {
			for (int j = 0; j < line_size; j++) {
				if (count > size) {
					fprintf(fout, "\n");
					return;
				}
				if (array[count] == -1) {
					brk_temp++;
					break;
				}
				fprintf(fout, "%8d", array[count]);
				count++;
			}
			if (brk_temp == 1)break;
			fprintf(fout, "\n");
		}
	}
	else if (size < 41) {
		int count = 0;
		int brk_temp = 0;
		for (int i = 0; i < 2 * num_sample_lines; i++) {
			for (int j = 0; j < line_size; j++) {
				if (count > size) {
					fprintf(fout, "\n");
					return;
				}
				if (array[count] == -1) {
					brk_temp++;
					break;
				}
				fprintf(fout, "%8d", array[count]);
				count++;
			}
			if (brk_temp == 1)break;
			fprintf(fout, "\n");
		}
	}
	else {
		int count = 0;
		int brk_temp = 0;
		for (int i = 0; i < num_sample_lines; i++) {
			for (int j = 0; j < line_size; j++) {
				if (count > size) {
					fprintf(fout, "\n");
					return;
				}
				if (array[count] == -1) {
					brk_temp++;
					break;
				}
				fprintf(fout, "%8d", array[count]);
				count++;
			}
			if (brk_temp == 1)break;
			fprintf(fout, "\n");
		}
		if (brk_temp == 1)return;

		if (count < (size - line_size * num_sample_lines))
			count = size - (line_size * num_sample_lines);
		if (count >= size) return;
		fprintf(fout, "\n   . . . . .\n");
		brk_temp = 0;
		for (int i = 0; i < num_sample_lines; i++) {
			for (int j = 0; j < line_size; j++) {
				if (count > size) {
					fprintf(fout, "\n");
					return;
				}
				if (array[count] == -1) {
					brk_temp++;
					break;
				}
				fprintf(fout, "%8d", array[count]);
				count++;
			}
			fprintf(fout, "\n");
			if (brk_temp == 1)break;
		}
		fprintf(fout, "\n");
	}
}
void genBigRandArray(int* array, int size) {
	char* flag;
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand, bigRand_withOffset;

	flag = (char*)calloc(size, sizeof(char));
	while (count < size) {
		u_int32 = ((long)rand() << 15) | rand();
		bigRand = u_int32 % size;
		if (flag[bigRand] == 1) {
			continue;
		}
		else {
			flag[bigRand] = 1;
			array[count++] = bigRand;
		}
	}
	free(flag);
}
void getArrayStatistics(int* array, int size) {
	int data, min, max;
	double sum = 0.0, var, diff, sq_diff_sum = 0.0, avg, std_dev;

	min = INT_MAX;
	max = INT_MIN;
	for (int i = 0; i < size; i++) {
		data = array[i];
		sum += data;
		if (data < min)min = data;
		if (data > max)max = data;
	}
	avg = sum / (double)size;
	for (int i = 0; i < size; i++) {
		diff = array[i] - avg;
		sq_diff_sum += diff * diff;
	}
	var = sq_diff_sum / (double)size;
	std_dev = sqrt(var);
	printf("min (%3d), max (%3d), ", min, max);
	printf("sum (%8.2lf), average (%8.2lf), ", sum, avg);
	printf("variance (%8.2lf), standard deviation (%8.2lf)\n", var, std_dev);
}
void fgetArrayStatistics(FILE* fout, int* array, int size) {
	int data, min, max;
	double sum = 0.0, var, diff, sq_diff_sum = 0.0, avg, std_dev;

	min = INT_MAX;
	max = INT_MIN;
	for (int i = 0; i < size; i++) {
		data = array[i];
		sum += data;
		if (data < min)min = data;
		if (data > max)max = data;
	}
	avg = sum / (double)size;
	for (int i = 0; i < size; i++) {
		diff = array[i] - avg;
		sq_diff_sum += diff * diff;
	}
	var = sq_diff_sum / (double)size;
	std_dev = sqrt(var);
	fprintf(fout,"min (%3d), max (%3d), ", min, max);
	fprintf(fout, "sum (%8.2lf), average (%8.2lf), ", sum, avg);
	fprintf(fout, "variance (%8.2lf), standard deviation (%8.2lf)\n", var, std_dev);
}