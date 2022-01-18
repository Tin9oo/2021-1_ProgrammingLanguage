#ifndef ARRAY
#define ARRAY

#include <stdio.h>
#include <stdlib.h>

void genBigRandArray(int* array, int size, int offset) {
	char* flag; // 난수가 생성되었는지 확인
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand; // 생성된 난수값

	flag = (char*)calloc(size, sizeof(char)); // 동적 할당
	while (count < size) {
		u_int32 = ((long)rand() << 15) | rand();
		bigRand = u_int32 % size;
		if (flag[bigRand] == 1) {
			continue;
		}
		else { // 이미 생성된 난수인지 확인
			flag[bigRand] = 1;
			array[count++] = bigRand + offset;
		}
	}
	free(flag); // 할당 해제
}
void printBigArraySample(int* array, int size, int line_size, int num_sample_lines) {
	int count = 0; // 몇번째 수인지 확인
	int brk_temp = 0; // 센티널을 만나면 탈출

	for (int i = 0; i < num_sample_lines; i++) { // 기본 배열 출력
		for (int j = 0; j < line_size; j++) {    // line_size개 만큼 num_sample_lines줄 출력
			if (count > size) { // 지정한 크기 초과하면 탈출
				printf("\n");
				return;
			}
			printf("%8d", array[count]);
			count++;
		}
		printf("\n");
	}

	if (count < (size - line_size * num_sample_lines)) // 마지막 num_sample_lines줄 만큼 출력
		count = size - (line_size * num_sample_lines); // 하도록 초기값 재설정
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