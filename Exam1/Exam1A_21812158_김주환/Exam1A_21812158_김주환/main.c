/*
* ���ϸ� : main.c
* ���� �� �⺻ ���
*	�Ǻ���ġ ������ 5������ �����ϰ� �ð��� ����ũ���� ������ �����ϰ� ����϶�.
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 4�� 3��
*/
#include <stdio.h>
#include <time.h>
#include <Windows.h>

double dynProg_Fibo(int n); // ���� ���α׷��� ����� ����� �Ǻ���ġ �Լ�

void main() {
	LONGLONG t_diff_pc;
	LARGE_INTEGER freq, t1, t2;
	double t_elapsed;

	QueryPerformanceFrequency(&freq); // ���ļ� �� ���
	for (int i = 5; i <= 100; i += 5) {
		QueryPerformanceCounter(&t1); // ���� performance counter ���� ���
		printf("dynProg_fibo(%3d) = %25.0lf, ", i, dynProg_Fibo(i)); // �Լ� ����
		QueryPerformanceCounter(&t2);// ���� performance counter ���� ���
		t_diff_pc = t2.QuadPart - t1.QuadPart;
		t_elapsed = ((double)t_diff_pc / (double)freq.QuadPart);
		printf(" ===> processing time %10.2lf micro-seconds\n", t_elapsed * 1000000); // micro �� ���
	}
}

double dynProg_Fibo(int n) {
	double fibo_rst;
	static double fibo_series[101] = { 0 };

	if (n == 0 || n == 1) {
		return n;
	}
	else if (fibo_series[n] != 0) { // ������ ��� �ߴٸ� ������ �ҷ��� �� �ִ�.
		fibo_rst = fibo_series[n];
		return fibo_rst;
	}
	else {
		fibo_rst = dynProg_Fibo(n - 2) + dynProg_Fibo(n - 1); // ������ ��� ���� �ʾƼ�
		fibo_series[n] = fibo_rst;                            // ��� �� �迭�� �߰�
		return fibo_rst;
	}
}