/*
* ���ϸ� : power_compare.c
* ���� �� �⺻ ���
*	��� a �� �������� �ݺ����� ��� �Լ��� �����ϰ� ������ ������ �ð��� �ٸ��� ��Ÿ�����
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 3�� 29��
*/
#include <stdio.h>
#include <time.h>
#include <windows.h>

double powerIter(double base, int exponent);
double powerRecur(double base, int exponent);


int main(void) {
	time_t t_before, t_after;
	int t_diff; // �ɸ� sec �� ����
	LONGLONG t_diff_pc;
	LARGE_INTEGER freq, t1, t2;
	double t_elapse_us;
	double result_i, result_r;
	double base = 1.015;

	QueryPerformanceFrequency(&freq); // ���ļ� �� ���
	for (int expo = 1000; expo <= 4000; expo += 1000) {
		time(&t_before); // �Լ� ȣ�� ���� �ð�
		QueryPerformanceCounter(&t1); // ���� performance counter ���� ���
		result_i = powerIter(base, expo); // ��� �� ����
		QueryPerformanceCounter(&t2);// ���� performance counter ���� ���
		time(&t_after); // �Լ� ȣ�� �� �ð�
		t_diff = difftime(t_after, t_before); // ����� �ð�
		t_diff_pc = t2.QuadPart - t1.QuadPart;
		t_elapse_us = ((double)t_diff_pc / (double)freq.QuadPart) * 1000000; // micro �� ���
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
	for (int i = 0; i < exponent; i++) buf *= base; // �ݺ������� �¼���ŭ ���Ѵ�
	return buf;
}

double powerRecur(double base, int exponent) {
	if (exponent == 0) return 1.0; // ������ �¼����� �Լ� ȣ�� ����
	else return base * powerRecur(base, exponent - 1); // ����Լ��� �¼��� ����
}