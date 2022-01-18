/*
* ���ϸ� : find_max_min_avg.c
* ���� �� �⺻ ��� : �Է¹��� ���� �������� �ִ밪, �ּҰ�, ��հ��� ����
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 3�� 4��
*/
#include <stdio.h>

int main(void) {
	int nums[5] = { 0 };

	printf("5���� ������ �Է��ϼ��� : ");
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