#ifndef ARRAY
#define ARRAY

#include <stdio.h>
#include <stdlib.h>

void genBigRandArray(int* array, int size, int offset) {
	char* flag; // ������ �����Ǿ����� Ȯ��
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand; // ������ ������

	flag = (char*)calloc(size, sizeof(char)); // ���� �Ҵ�
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
	free(flag); // �Ҵ� ����
}
void printBigArraySample(int* array, int size, int line_size, int num_sample_lines) {
	int count = 0; // ���° ������ Ȯ��
	int brk_temp = 0; // ��Ƽ���� ������ Ż��

	for (int i = 0; i < num_sample_lines; i++) { // �⺻ �迭 ���
		for (int j = 0; j < line_size; j++) {    // line_size�� ��ŭ num_sample_lines�� ���
			if (count > size) { // ������ ũ�� �ʰ��ϸ� Ż��
				printf("\n");
				return;
			}
			printf("%8d", array[count]);
			count++;
		}
		printf("\n");
	}

	if (count < (size - line_size * num_sample_lines)) // ������ num_sample_lines�� ��ŭ ���
		count = size - (line_size * num_sample_lines); // �ϵ��� �ʱⰪ �缳��
	if (count >= size) return;
	printf("\n   . . . . .\n\n");
	for (int i = 0; i < num_sample_lines; i++) {
		for (int j = 0; j < line_size; j++) {
			if (count > size) {
				printf("\n");
				return;
			}
			printf("%8d", array[count]);
			count++;
		}
		printf("\n");
	}
	printf("\n");
}

void selectionSorting(int* array, int size) {
	int temp = 0, counts = 0;
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

#endif