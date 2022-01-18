/*
* ���ϸ� : call_by.cpp
* ���� �� �⺻ ���
*	2���� �Ǽ� �����͸� �Լ��� �μ��� �����ϰ�, �� ��հ��� ����Ͽ� �Ǽ� �ڷ������� ��ȯ�ϴ�
*	������ average() �Լ��� call-by-value, call-by-pointer, call-by-reference ������� ���� �����϶�
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 4�� 19��
*/
#include <stdio.h>

double avg_v(double x, double y);
void avg_p(double* x, double* y, double* avg);
void avg_r(double& x, double& y, double& avg);

int main(void) {
	double x = 10.0, y = 20.0;
	double avg = 0.0;

	avg = avg_v(x, y);
	printf("Average of call-by-value method : %lf\n", avg);
	avg_p(&x, &y, &avg);
	printf("Average of call-by-pointer method : %lf\n", avg);
	avg_r(x, y, avg);
	printf("Average of call-by-reference method : %lf\n", avg);
	return 0;
}
double avg_v(double x, double y) {
	double avg = 0.0;

	avg = (x + y) / 2.0;
	return avg;
}
void avg_p(double* x, double* y, double* avg) {
	*avg = (*x + *y) / 2.0;
}
void avg_r(double& x, double& y, double& avg) {
	avg = (x + y) / 2.0;
}