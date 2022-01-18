#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include "BigArray.h"

#define ESC 0x1B
#define MAX_NUM_DATA 100

void arrayStatistics_basicArray(FILE* fout);
void arrayStatistics_externArray(FILE* fout);
void arrayStatistics_fileDataArray(FILE* fout);
void arrayStatistics_inputArray(FILE* fout);
void arrayStatistics_genBigRandArray(FILE* fout);

#define Data_Input_File "Data_input.txt"
#define Data_Output_File "Data_output.txt"

int main(int argc, char argv[]) {
	FILE* fout;
	char menu;

	fout = fopen(Data_Output_File, "w");
	if (fout == NULL) {
		printf("Error in creation of %s !!\n", Data_Output_File);
		exit(1);
	}

	while (1) {
		printf("\nTest Array Handling (1 : data_array; 2 : extern_array; \
3 : data_file; 4 : data_input; 5 : genBigRandArray; Esc : terminate) : ");
		menu = _getche();
		if (menu == ESC) break;
		switch (menu) {
		case '1':
			arrayStatistics_basicArray(fout);
			break;
		case '2':
			arrayStatistics_externArray(fout);
			break;
		case '3':
			arrayStatistics_fileDataArray(fout);
			break;
		case '4':
			arrayStatistics_inputArray(fout);
			break;
		case '5':
			arrayStatistics_genBigRandArray(fout);
			break;
		default:
			break;
		}
	}
	fclose(fout);
	return 0;
}
void arrayStatistics_basicArray(FILE* fout) {
	int num_data = 10;
	int data_array[MAX_NUM_DATA] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, -1 };
	printf("\n");
	printBigArraySample(data_array, num_data, 10, 2);
	fprintBigArraySample(fout, data_array, num_data, 10, 2);
	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
}
void arrayStatistics_externArray(FILE* fout) {
	int num_data = 0;
	extern int data_array[MAX_NUM_DATA];

	for (int i = 0; i < MAX_NUM_DATA; i++) {
		if (data_array[i] == -1)break;
		else num_data++;
	}
	printf("\n");
	printBigArraySample(data_array, num_data, 10, 2);
	fprintBigArraySample(fout, data_array, num_data, 10, 2);
	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
}
void arrayStatistics_fileDataArray(FILE* fout) {
	FILE* fin;
	int data, num_data = 0;
	int data_array[MAX_NUM_DATA] = { 0 };
	
	fin = fopen(Data_Input_File, "r");
	if (fin == NULL) {
		return 0;
	}
	while (fscanf(fin, "%d", &data) != EOF) {
		if ((data == -1) || (num_data >= MAX_NUM_DATA)) break;
		data_array[num_data] = data;
		num_data++;
	}
	fclose(fin);
	printBigArraySample(data_array, num_data, 10, 2);
	fprintBigArraySample(fout, data_array, num_data, 10, 2);
	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
}
void arrayStatistics_inputArray(FILE* fout) {
	int num_data, data;
	int data_array[MAX_NUM_DATA] = { 0 };
	scanf("%d", &num_data);

	for (int i = 0; i < num_data; i++) {
		scanf("%d", &data);
		data_array[i] = data;
	}
	printBigArraySample(data_array, num_data, 10, 2);
	fprintBigArraySample(fout, data_array, num_data, 10, 2);
	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
}
void arrayStatistics_genBigRandArray(FILE* fout) {
	int* bigArray;
	int bigArray_size;

	scanf("%d", &bigArray_size);
	bigArray = (int*)calloc(bigArray_size, sizeof(int));
	genBigRandArray(bigArray, bigArray_size);
	printBigArraySample(bigArray, bigArray_size, 10, 2);
	fprintBigArraySample(fout, bigArray, bigArray_size, 10, 2);
	getArrayStatistics(bigArray, bigArray_size);
	fgetArrayStatistics(fout, bigArray, bigArray_size);
}