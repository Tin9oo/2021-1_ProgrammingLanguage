/* main_time.cpp (1) */
/*
* * 파일명 : main_time.cpp
* 목적 및 기본 기능
*	시간의 경과와 정렬
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 5월 11일
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Time.h"
#define NUM_TIMES 5
void main() {
	Time t1, t2;
	Time times[NUM_TIMES];
	int incr_secs, diff_sec;
	t1 = t2 = inputTime();
	printf("Input time t1 = "); printTime(&t1); printf("\n");
	printf("input seconds to increment : ");
	scanf("%d", &incr_secs);
	incrementTime(&t2, incr_secs);
	printf("After incrementing %d secs, t2 = ", incr_secs); printTime(&t2); printf("\n");
	diff_sec = compareTime(&t1, &t2);
	printf("Difference between t1 and t2 is %d secs\n", diff_sec);
	times[0] = initTime(23, 59, 59);
	times[1] = initTime(9, 0, 5);
	times[2] = initTime(13, 30, 0);
	times[3] = initTime(3, 59, 59);
	times[4] = initTime(0, 0, 0);
	printf("\nBefore sorting times : \n");
	for (int i = 0; i < NUM_TIMES; i++) {
		printf("times[%d] = ", i); printTime(&times[i]); printf("\n");
	}
	selectSortTime(times, NUM_TIMES);
	printf("After selection sorting of times : \n");
	for (int i = 0; i < NUM_TIMES; i++) {
		printf("times[%d] = ", i); printTime(&times[i]); printf("\n");
	}
}