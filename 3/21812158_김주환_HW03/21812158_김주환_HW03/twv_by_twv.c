/*
* 파일명 : twlv_by_twlv.c
* 목적 및 기본 기능
*	중첩 반복문을 사용하여 12 X 12 곱셈표를 출력하라.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 3월 22일
*/
#include <stdio.h>

int main(void) {
	printf("> > > 12 X 12 Multiplication Table < < <\n\n");
	
	printf("    |");
	for (int i = 1; i <= 12; i++) { // 윗부분 출력
		printf("%5d", i);
	}
	printf("\n");
	printf("====+============================================================\n");

	for (int j = 1; j <= 12; j++) { // 2중 반복으로 곱셈표 출력
		printf("%3d |", j);
		for (int k = 1; k <= 12; k++) {
			printf("%5d", j * k);
		}
		printf("\n");
	}

	printf("계속하려면 아무 키나 누르십시오 . . .\n\n");

	return 0;
}