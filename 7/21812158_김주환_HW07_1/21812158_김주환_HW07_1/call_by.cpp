/*
* 파일명 : call_by.cpp
* 목적 및 기본 기능
*	2개의 실수 데이터를 함수의 인수로 전달하고, 그 평균값을 계산하여 실수 자료형으로 반환하는
*	간단한 average() 함수를 call-by-value, call-by-pointer, call-by-reference 방식으로 각각 구현하라
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 4월 19일
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