/*
* ���ϸ� : gen_big_rand.c
* ���� �� �⺻ ���
*	������ rand() �Լ����� ū ũ���� genBigRandArray() �� �����϶�.
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 3�� 29��
*/
#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 10

void genBigRandArray(int* array, int size);
void printArraySample(int* array, int size, int line_size);

int maina(void) {
	int* array; // pointer for dynamin array

	for (int size = 200000; size <= 1000000; size += 200000) { // size �� �÷����� ���� ����
		printf("Testing generation of dynamic array of random numbers ( size : %d )\n", size);
		array = (int*)calloc(size, sizeof(int)); // dynamic array
		if (array == NULL) {
			printf("Error in dynamic memory allocation for integer array of size (%d)\n", size);
			exit(-1); // �ٷ� ���μ��� ����
		}
		genBigRandArray(array, size); // Ȯ��� ���� ����
		printArraySample(array, size, LINE_SIZE); // ������ ������ ���
												  // LINE_SIZE = 10;
		free(array);
	}

	return 0;
}

void genBigRandArray(int* array, int size) {
	char* flag; // ������ �̹� �����Ǿ����� Ȯ��
	unsigned int uint_32, bigRand;
	int count = 0; // size ��ŭ ����

	srand(time(0));
	flag = (int*)malloc(sizeof(char) * size); // ���� �Ҵ����� ū ũ���� �迭 ����
	while (count < size) {
		uint_32 = ((long)rand() << 15) | rand(); // 15bit �·� �̵��Ͽ� ���� ũ�⸦ Ȯ��
		bigRand = uint_32 % size;
		if (flag[bigRand] == 1) continue;
		else {
			flag[bigRand] = 1;
			array[count++] = bigRand;
		}
	}
	free(flag); // �Ҵ� ����
}

void printArraySample(int* array, int size, int line_size) {
	for (int i = 0, count = 0; i < 3; i++) { // �պκ� 30�� ���
		for (int j = 0; j < line_size; j++) {
			printf("%8d", array[count++]);
		}
		printf("\n");
	}
	printf("   . . . .\n\n");
	for (int i = 0, count = size-31; i < 3; i++) { // �޺κ� 30�� ���
		for (int j = 0; j < line_size; j++) {
			printf("%8d", array[count++]);
		}
		printf("\n");
	}
	printf("\n");
}