/*
* 파일명 : find_max_min_avg.c
* 목적 및 기본 기능 : 입력받은 정수 데이터의 최대값, 최소값, 평균값을 산출
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 3월 4일
*/
#include <stdio.h>

int main(void) {
	int nums[5] = { 0 };

	printf("5개의 정수를 입력하세요 : ");
	scanf_s("%d %d %d %d %d", &nums[0], &nums[1], &nums[2], &nums[3], &nums[4]);

	int max = nums[0];
	int min = nums[0];
	double avg = nums[0];

	int i = 0;
	while (++i < 5) {
		if (max < nums[i]) max = nums[i];
		if (min > nums[i]) min = nums[i];
		avg += (double)nums[i];
	}
	avg /= 5;

	printf("\nMAX : %d\nMIN : %d\nAVG : %lf\n", max, min, avg);

	return 0;
}