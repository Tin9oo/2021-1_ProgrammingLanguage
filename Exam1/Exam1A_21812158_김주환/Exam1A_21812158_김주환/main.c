/*
* 파일명 : main.c
* 목적 및 기본 기능
*	피보나치 수열을 5단위로 실행하고 시간을 마이크로초 단위로 측정하고 출력하라.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 4월 3일
*/
#include <stdio.h>
#include <time.h>
#include <Windows.h>

double dynProg_Fibo(int n); // 동적 프로그래밍 기법을 사용한 피보나치 함수

void main() {
	LONGLONG t_diff_pc;
	LARGE_INTEGER freq, t1, t2;
	double t_elapsed;

	QueryPerformanceFrequency(&freq); // 주파수 값 기록
	for (int i = 5; i <= 100; i += 5) {
		QueryPerformanceCounter(&t1); // 이전 performance counter 값을 기록
		printf("dynProg_fibo(%3d) = %25.0lf, ", i, dynProg_Fibo(i)); // 함수 실행
		QueryPerformanceCounter(&t2);// 이후 performance counter 값을 기록
		t_diff_pc = t2.QuadPart - t1.QuadPart;
		t_elapsed = ((double)t_diff_pc / (double)freq.QuadPart);
		printf(" ===> processing time %10.2lf micro-seconds\n", t_elapsed * 1000000); // micro 초 계산
	}
}

double dynProg_Fibo(int n) {
	double fibo_rst;
	static double fibo_series[101] = { 0 };

	if (n == 0 || n == 1) {
		return n;
	}
	else if (fibo_series[n] != 0) { // 이전에 계산 했다면 빠르게 불러올 수 있다.
		fibo_rst = fibo_series[n];
		return fibo_rst;
	}
	else {
		fibo_rst = dynProg_Fibo(n - 2) + dynProg_Fibo(n - 1); // 이전에 계산 하지 않아서
		fibo_series[n] = fibo_rst;                            // 계산 후 배열에 추가
		return fibo_rst;
	}
}