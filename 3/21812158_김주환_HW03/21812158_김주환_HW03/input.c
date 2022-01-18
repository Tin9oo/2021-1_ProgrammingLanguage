/*
* 파일명 : seeparate.c
* 목적 및 기본 기능
*	표준입력장치에서 문자 1개를 입력받고 이 문자가 대문자, 소문자, 모음, 자음
*   숫자, 기호인지 구분
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 3월 22일
*/
#include <stdio.h>

int main_separate(void) {
	char input;

	// 입력
	printf("Input character : ");
	scanf("%c", &input);

	// 판단
	if (65 <= input && input <= 90) {
		printf("대문자 ");
		if (input == 65 || input == 69 || input == 73 || input == 81 || input == 85) {
			printf("모음");
		}
		else {
			printf("자음");
		}
	}
	else if (97 <= input && input <= 122) {
		printf("소문자 ");
		if (input == 97 || input == 101 || input == 105 || input == 111 || input == 117) {
			printf("모음");
		}
		else {
			printf("자음");
		}
	}
	else if (48 <= input && input <= 57) {
		printf("숫자");
	}
	else if (33 <= input && input <= 47 || 58 <= input && input <= 64
		|| 91 <= input && input <= 96
		|| 123 <= input && input <= 126) {
		printf("기호");
	}
	else {
		printf("대/소문자, 숫자, 기호가 아니다");
	}

	return 0;
}