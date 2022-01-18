/*
* ���ϸ� : BigArray.c
* ���� �� �⺻ ���
*	BigArray.h ��� ���Ͽ��� ������ �Լ� ������ ����
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 4�� 2��
*/
#ifndef BIG_ARRAY_H
#define BIG_ARRAY_H

#define Data_Input_File "Data_input.txt"
#define Data_Output_File "Data_output.txt"
#define QUICK_SELECTION_THRESHOLD 50

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "BigArray.h"

// ����â�� �迭 ���� ���
void printBigArraySample(int* array, int size, int line_size = 10, int num_sample_lines = 2) {
	int count = 0; // ���° ������ Ȯ��
	int brk_temp = 0; // ��Ƽ���� ������ Ż��

	for (int i = 0; i < num_sample_lines; i++) { // �⺻ �迭 ���
		for (int j = 0; j < line_size; j++) {    // line_size�� ��ŭ num_sample_lines�� ���
			if (count > size) { // ������ ũ�� �ʰ��ϸ� Ż��
				printf("\n");
				return;
			}
			if (array[count] == -1) { // ��Ƽ�� ������ Ż��
				brk_temp++;
				break;
			}
			printf("%8d", array[count]);
			count++;
		}
		printf("\n");
		if (brk_temp == 1)break;
	}

	if (20 < size && size < 41) { // 20 �ʰ� 40 ������ ����� �迭 ���
		count = num_sample_lines * line_size; // ù��° ��� ���ķ� �ʱⰪ �缳��
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
	}
	else if (40 < size) { // 40 �ʰ��� ����� �迭 ���
		brk_temp = 0;

		if (count < (size - line_size * num_sample_lines)) // ������ num_sample_lines�� ��ŭ ���
			count = size - (line_size * num_sample_lines); // �ϵ��� �ʱⰪ �缳��
		if (count >= size) return;
		printf("\n   . . . . .\n\n");
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

// ������ ���Ͽ� �迭 ���� ���
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size = 10, int num_sample_lines = 2) {
	int count = 0; // ���° ������ Ȯ��
	int brk_temp = 0; // ��Ƽ�� ������ Ż��

	for (int i = 0; i < num_sample_lines; i++) { // �⺻ �迭 ���
		for (int j = 0; j < line_size; j++) {
			if (count > size) { // ������ ũ�⸦ �ʰ��ϸ� Ż��
				fprintf(fout, "\n");
				return;
			}
			if (array[count] == -1) { // ��Ƽ�� ������ Ż��
				brk_temp++;
				break;
			}
			fprintf(fout, "%8d", array[count]);
			count++;
		}
		fprintf(fout, "\n");
		if (brk_temp == 1)break;
	}

	if (20 < size && size < 41) { // 20 �ʰ� 40 ������ ����� �迭 ���
		count = num_sample_lines * line_size; // ù �迭 ��� ������ ������ �ʱⰪ �缳��
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
	}
	else if (40 < size) { // 40 �ʰ��� ����� �迭 ���
		brk_temp = 0;
		if (count < (size - line_size * num_sample_lines)) // ������ �κ� ����ϵ���
			count = size - (line_size * num_sample_lines); // �ʱⰪ �缳��
		if (count >= size) return;
		fprintf(fout, "\n   . . . . .\n\n");
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

// 30��Ʈ ���� ����
void genBigRandArray(int* array, int size, int offset) {
	char* flag; // ������ �����Ǿ����� Ȯ��
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand; // ������ ������

	flag = (char*)calloc(size, sizeof(char)); // ���� �Ҵ�
	if (flag == NULL) {
		printf("Error in dynamic creation of big_array (size = %d) !!!", size);
	}
	while (count < size) {
		u_int32 = ((long)rand() << 15) | rand();
		bigRand = u_int32 % size;
		if (flag[bigRand] == 1) {
			continue;
		}
		else { // �̹� ������ �������� Ȯ��
			flag[bigRand] = 1;
			array[count++] = bigRand + offset;
		}
	}
	array[count] = -1;
	free(flag); // �Ҵ� ����
}
void suffleArray(int* array, int size) {
	int i1, i2, d;
	srand((unsigned)time(NULL));

	for (int i = 0; i < size / 2; i++) {
		i1 = (((unsigned long)rand() << 15 | rand())) % size;
		i2 = (((unsigned long)rand() << 15 | rand())) % size;
		// suffle
		d = array[i1];
		array[i1] = array[i2];
		array[i2] = d;
	}
}
// �迭�� �Ӽ��� ����â�� ���
void getArrayStatistics(int* array, int size) {
	int data, min, max;
	double sum = 0.0, var, diff, sq_diff_sum = 0.0, avg, std_dev;

	min = INT_MAX;
	max = INT_MIN;
	for (int i = 0; i < size; i++) {
		data = array[i];
		sum += data;
		if (data < min)min = data; // �ּҰ�
		if (data > max)max = data; // �ִ밪
	}
	avg = sum / (double)size; // ���
	for (int i = 0; i < size; i++) {
		diff = array[i] - avg;
		sq_diff_sum += diff * diff;
	}
	var = sq_diff_sum / (double)size; // �л�
	std_dev = sqrt(var); // ǥ������
	printf("min (%3d), max (%3d), ", min, max);
	printf("sum (%8.2lf), average (%8.2lf), ", sum, avg);
	printf("variance (%8.2lf), standard deviation (%8.2lf)\n", var, std_dev);
}

// �迭�� �Ӽ��� ������ ���Ͽ� ���
void fgetArrayStatistics(FILE* fout, int* array, int size) {
	int data, min, max;
	double sum = 0.0, var, diff, sq_diff_sum = 0.0, avg, std_dev;

	min = INT_MAX;
	max = INT_MIN;
	for (int i = 0; i < size; i++) {
		data = array[i];
		sum += data;
		if (data < min)min = data; // �ּҰ�
		if (data > max)max = data; // �ִ밪
	}
	avg = sum / (double)size; // ���
	for (int i = 0; i < size; i++) {
		diff = array[i] - avg;
		sq_diff_sum += diff * diff;
	}
	var = sq_diff_sum / (double)size; // �л�
	std_dev = sqrt(var); // ǥ������
	fprintf(fout, "min (%3d), max (%3d), ", min, max);
	fprintf(fout, "sum (%8.2lf), average (%8.2lf), ", sum, avg);
	fprintf(fout, "variance (%8.2lf), standard deviation (%8.2lf)\n", var, std_dev);
}
void selectionSort(int* array, int size) {
	int temp = 0;
	int min = 0;

	for (int is = 0; is < size; is++) {
		min = is;
		for (int js = is + 1; js < size; js++) {
			if (array[min] > array[js]) {
				min = js;
			}
			if (js == size - 1) {
				temp = array[min];
				array[min] = array[is];
				array[is] = temp;
			}
		}
	}
}
void quickSort(int* array, int size, int left, int right) {
	int pi, new_pi;
	int pivot_value;
	int temp, i;

	if (left >= right) return;
	else if (left < right) pi = (left + right) / 2;

	pivot_value = array[pi];
	
	temp = array[pi];
	array[pi] = array[right];
	array[right] = temp;
	new_pi = left;
	for (i = left; i <= (right - 1); i++) {
		if (array[i] <= pivot_value) {
			temp = array[i];
			array[i] = array[new_pi];
			array[new_pi] = temp;
			new_pi++;
		}
	}

	temp = array[new_pi];
	array[new_pi] = array[right];
	array[right] = temp;

	if (left < (new_pi - 1)) quickSort(array, size, left, new_pi - 1);
	if ((new_pi + 1) < right) quickSort(array, size, new_pi + 1, right);
}

void _hybridQuickSelectionSort(int* array, int size, int left, int right, int level) {
	if (right - left + 1 <= QUICK_SELECTION_THRESHOLD) {
		int temp = 0;
		int min = 0;

		for (int is = 0; is < right - left + 1; is++) {
			min = is;
			for (int js = is + 1; js < right - left + 1; js++) {
				if (array[min] > array[js]) {
					min = js;
				}
				if (js == right - 1) {
					temp = array[min];
					array[min] = array[is];
					array[is] = temp;
				}
			}
		}
		return;
	}
	int pi, new_pi;
	int pivot_value;
	int temp, i;

	pi = (left + right) / 2;

	pivot_value = array[pi];
	
	temp = array[pi];
	array[pi] = array[right];
	array[right] = temp;
	new_pi = left;
	for (i = left; i <= (right - 1); i++) {
		if (array[i] <= pivot_value) {
			temp = array[i];
			array[i] = array[new_pi];
			array[new_pi] = temp;
			new_pi++;
		}
	}

	temp = array[new_pi];
	array[new_pi] = array[right];
	array[right] = temp;

	_hybridQuickSelectionSort(array, size, left, new_pi - 1, 0);
	_hybridQuickSelectionSort(array, size, new_pi + 1, right, 0);
}
void hybridQuickSelectionSort(int* array, int size) {
	_hybridQuickSelectionSort(array, size, 0, size - 1, 0);
}
#endif