/*
* 파일명 : power_compare.c
* 목적 및 기본 기능
*	상수 a 의 지수승을 반복문과 재귀 함수로 구현하고 각각의 측정된 시간이 다름을 나타내어라
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 3월 29일
*/
#include <stdio.h>
#include <time.h>
#include <windows.h>

double powerIter(double base, int exponent);
double powerRecur(double base, int exponent);


int main(void) {
	time_t t_before, t_after;
	int t_diff; // 걸린 sec 의 차이
	LONGLONG t_diff_pc;
	LARGE_INTEGER freq, t1, t2;
	double t_elapse_us;
	double result_i, result_r;
	double base = 1.015;

	QueryPerformanceFrequency(&freq); // 주파수 값 기록
	for (int expo = 1000; expo <= 4000; expo += 1000) {
		time(&t_before); // 함수 호출 이전 시간
		QueryPerformanceCounter(&t1); // 이전 performance counter 값을 기록
		result_i = powerIter(base, expo); // 계산 값 도출
		QueryPerformanceCounter(&t2);// 이후 performance counter 값을 기록
		time(&t_after); // 함수 호출 후 시간
		t_diff = difftime(t_after, t_before); // 경과한 시간
		t_diff_pc = t2.QuadPart - t1.QuadPart;
		t_elapse_us = ((double)t_diff_pc / (double)freq.QuadPart) * 1000000; // micro 초 계산
		printf("PowerItera(1.015, %d) by iterative = %40.5lf, took(%3d) sec, (%10.2lf) micro-second\n", expo, result_i, t_diff, t_elapse_us);
		
		time(&t_before);
		QueryPerformanceCounter(&t1);
		result_r = powerRecur(base, expo);
		QueryPerformanceCounter(&t2);
		time(&t_after);
		t_diff = difftime(t_after, t_before);
		t_diff_pc = t2.QuadPart - t1.QuadPart;
		t_elapse_us = ((double)t_diff_pc / (double)freq.QuadPart) * 1000000;
		printf("PowerRecur(1.015, %d) by recursive = %40.5lf, took(%3d) sec, (%10.2lf) micro-second\n\n", expo, result_r, t_diff, t_elapse_us);
	}
	return 0;
}

double powerIter(double base, int exponent) {
	double buf = 1.0;
	for (int i = 0; i < exponent; i++) buf *= base; // 반복문으로 승수만큼 곱한다
	return buf;
}

double powerRecur(double base, int exponent) {
	if (exponent == 0) return 1.0; // 마지막 승수에서 함수 호출 종료
	else return base * powerRecur(base, exponent - 1); // 재귀함수로 승수를 구현
}