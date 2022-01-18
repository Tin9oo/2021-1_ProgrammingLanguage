/*
* 파일명 : gen_big_rand.c
* 목적 및 기본 기능
*	기존의 rand() 함수보다 큰 크기의 genBigRandArray() 를 구현하라.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 3월 29일
*/
#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 10

void genBigRandArray(int* array, int size);
void printArraySample(int* array, int size, int line_size);

int maina(void) {
	int* array; // pointer for dynamin array

	for (int size = 200000; size <= 1000000; size += 200000) { // size 를 늘려가며 난수 생성
		printf("Testing generation of dynamic array of random numbers ( size : %d )\n", size);
		array = (int*)calloc(size, sizeof(int)); // dynamic array
		if (array == NULL) {
			printf("Error in dynamic memory allocation for integer array of size (%d)\n", size);
			exit(-1); // 바로 프로세스 종료
		}
		genBigRandArray(array, size); // 확장된 난수 생성
		printArraySample(array, size, LINE_SIZE); // 생성된 난수를 출력
												  // LINE_SIZE = 10;
		free(array);
	}

	return 0;
}

void genBigRandArray(int* array, int size) {
	char* flag; // 난수가 이미 지정되었는지 확인
	unsigned int uint_32, bigRand;
	int count = 0; // size 만큼 실행

	srand(time(0));
	flag = (int*)malloc(sizeof(char) * size); // 동적 할당으로 큰 크기의 배열 생성
	while (count < size) {
		uint_32 = ((long)rand() << 15) | rand(); // 15bit 좌로 이동하여 난수 크기를 확장
		bigRand = uint_32 % size;
		if (flag[bigRand] == 1) continue;
		else {
			flag[bigRand] = 1;
			array[count++] = bigRand;
		}
	}
	free(flag); // 할당 해제
}

void printArraySample(int* array, int size, int line_size) {
	for (int i = 0, count = 0; i < 3; i++) { // 앞부분 30개 출력
		for (int j = 0; j < line_size; j++) {
			printf("%8d", array[count++]);
		}
		printf("\n");
	}
	printf("   . . . .\n\n");
	for (int i = 0, count = size-31; i < 3; i++) { // 뒷부분 30개 출력
		for (int j = 0; j < line_size; j++) {
			printf("%8d", array[count++]);
		}
		printf("\n");
	}
	printf("\n");
}