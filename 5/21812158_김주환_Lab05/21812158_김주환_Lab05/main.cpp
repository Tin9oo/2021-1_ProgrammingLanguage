/*
* ���ϸ� : main.c
* ���� �� �⺻ ���
*	�⺻ �迭, �ܺ� �迭, ���� ������, �Է� �迭, ������ �迭 �� �ϳ��� �����Ͽ�
*   ���� �����Ϳ� �迭�� ��� ������ ���Ŀ� ���� ����â�� ���Ͽ� ����Ѵ�.
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 4�� 2��
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include "BigArray.h"

#define ESC 0x1B
#define MAX_NUM_DATA 100

// #define TEST_WITH_INPUT_DATA
void arrayStatistics_basicArray(FILE* fout);
void arrayStatistics_externArray(FILE* fout);
void arrayStatistics_fileDataArray(FILE* fout);
void arrayStatistics_inputArray(FILE* fout);
void arrayStatistics_genBigRandArray(FILE* fout);

#define Data_Input_File "Data_input.txt" // ������ �ۼ��� ���ϸ�
#define Data_Output_File "Data_output.txt" // ����� ǥ���� ���ϸ�

int main(int argc, char argv[]) {
	FILE* fout;
	char menu;

	fout = fopen(Data_Output_File, "w"); // ���� ������� ����
	if (fout == NULL) { // ����ó��
		printf("Error in creation of %s !!\n", Data_Output_File);
		return -1;
	}

	while (1) {
		printf("\nTest Array Handling (1 : data_array; 2 : extern_array; \
3 : data_file; 4 : data_input; 5 : genBigRandArray; Esc : terminate) : ");
		menu = _getche();
		if (menu == ESC) break;
		switch (menu) {
		case '1':
			arrayStatistics_basicArray(fout); // �⺻ �迭�� ���� ����
			break;
		case '2':
			arrayStatistics_externArray(fout); // �ܺ� �迭�� ���� ����
			break;
		case '3':
			arrayStatistics_fileDataArray(fout); // �̹� ������ ���� ������ �迭�� ���� ����
			break;
		case '4':
			arrayStatistics_inputArray(fout); // �ǽð����� �Է��� �迭�� ���� ����
			break;
		case '5':
			arrayStatistics_genBigRandArray(fout); // �������� ������ �迭�� ���� ����
			break;
		default:
			break;
		}
	}
	fclose(fout); // ���� �ݱ�
	return 0;
}

void arrayStatistics_basicArray(FILE* fout) { // �⺻ �迭
	int num_data = 10;
	int data_array[MAX_NUM_DATA] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, -1 };

	printf("\nArrayStatistics_basicArray .....\n");
	fprintf(fout, "\nArrayStatistics_basicArray .....\n");
	printBigArraySample(data_array, num_data, 10, 2);
	fprintBigArraySample(fout, data_array, num_data, 10, 2);
	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
	printf("\narrayStatistics_basicArray - completed. Result is also stored in output file(%s).\n", Data_Output_File);
}
void arrayStatistics_externArray(FILE* fout) { // �ܺ� �迭
	int num_data = 0;
	extern int data_array[MAX_NUM_DATA];

	printf("\nArrayStatistics_externArray .....\n");
	fprintf(fout, "\nArrayStatistics_externArray .....\n");

	for (int i = 0; i < MAX_NUM_DATA; i++) {
		if (data_array[i] == -1) break;
		else num_data++;
	}

	printBigArraySample(data_array, num_data, 10, 2);
	fprintBigArraySample(fout, data_array, num_data, 10, 2);
	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
	printf("\narrayStatistics_externArray - completed. Result is also stored in output file(%s).\n", Data_Output_File);
}
void arrayStatistics_fileDataArray(FILE* fout) { // ������ ������ �迭
	FILE* fin;
	int data, num_data = 0;
	int data_array[MAX_NUM_DATA] = { 0 };

	printf("\nArrayStatistics_fileDataArray .....\n");
	fprintf(fout, "\nArrayStatistics_fileDataArray .....\n");

	fin = fopen(Data_Input_File, "r"); // �б� ���� ���� ����
	for (int i = 0; i < MAX_NUM_DATA; i++) {
		if (data_array[i] == -1) break;
		fprintf(fin, "%d", data_array[i]);
	}

	while (fscanf(fin, "%d", &data) != EOF) { // ������ �迭�� �о�´�
		if (data == -1) break;
		data_array[num_data] = data;
		num_data++;
	}
	fclose(fin);
	printBigArraySample(data_array, num_data, 10, 2);
	fprintBigArraySample(fout, data_array, num_data, 10, 2);
	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
	printf("\narrayStatistics_fileDataArray - completed. Result is also stored in output file(%s).\n", Data_Output_File);
}
void arrayStatistics_inputArray(FILE* fout) {
	int num_data, data;
	int data_array[MAX_NUM_DATA] = { 0 };

	printf("\nArrayStatistics_inputArray .....\n");
	fprintf(fout, "\nArrayStatistics_inputArray .....\n");
	printf("Please input the number of integers (less than %d) = ", MAX_NUM_DATA);
	scanf("%d", &num_data);
	printf("Input %d integer data : ", num_data);

	for (int i = 0; i < num_data; i++) {
		scanf("%d", &data);
		data_array[i] = data;
		data_array[i + 1] = -1;
	}

	printBigArraySample(data_array, num_data, 10, 2);
	fprintBigArraySample(fout, data_array, num_data, 10, 2);
	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
	printf("\narrayStatistics_inputArray - completed. Result is also stored in output file(%s).\n", Data_Output_File);
}
void arrayStatistics_genBigRandArray(FILE* fout) {
	int num_data = 0;
	int* dyn_array = NULL;

	printf("\nArrayStatistics_genBigRandArray .....\n");
	fprintf(fout, "\nArrayStatistics_genBigRandArray .....\n");
	printf("Big Array Size (more than 50000) = ");
	scanf("%d", &num_data);
	printf("Creating big random integer array (size : %d)\n", num_data);

	dyn_array = (int*)calloc(num_data, sizeof(int));
	if (dyn_array == NULL) {
		printf("Error in dynamic creation of big_array (size = %d) !!!", num_data);
		exit(1);
	}
	genBigRandArray(dyn_array, num_data);
	//sortArray(dyn_array, num_data);
	printBigArraySample(dyn_array, num_data, 10, 2);
	fprintBigArraySample(fout, dyn_array, num_data, 10, 2);
	getArrayStatistics(dyn_array, num_data);
	fgetArrayStatistics(fout, dyn_array, num_data);
	printf("\narrayStatistics_genBigRandArray - completed. Result is also stored in output file(%s).\n", Data_Output_File);
}