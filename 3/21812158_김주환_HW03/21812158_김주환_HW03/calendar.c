/*
* ���ϸ� : calendar.c
* ���� �� �⺻ ���
*	������ �Է¹ް�, �� ������ 1�� ~ 12�� �޷��� ������ ����ϴ� �˰�����
*   pseudo code�� �ۼ��϶�. �ش� ������ �����ΰ��� Ȯ���Ͽ�, �̿� ����
*   ��Ȯ�� 2�� ����� �� �� �ְ� �� ��.
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 3�� 22��
*/
#include <stdio.h>
#include <stdbool.h>

const char* month_name[13] = { "", "January", "Fabruary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
const char* week_day_name[7] = { "SUN", "MON", "TUE", "WED", "THR", "FRI", "SAT" };

bool isLeapYear(int y);
int getDaysFromJan01AD01(int year, int month, int day);

int main_calendar(void) {
	int year;
	int weekday;
	int day_from_0 = 0;
	int days_in_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	printf("����ΰ� : ");
	scanf("%d", &year);

	printf("> > > > > > Calendar of %d < < < < < <\n", year);
	for (int month = 1; month <= 12; month++) {
		day_from_0 = getDaysFromJan01AD01(year, month, 1);
		weekday = day_from_0 % 7;

		if (isLeapYear(year)) { // ������
			days_in_month[2] = 29;
		}

		printf("%s\n", month_name[month]);
		printf("=========================================\n");
		for (int wk = 0; wk <= 6; wk++) { // ���� ���
			printf("%5s", week_day_name[wk]);
		}
		printf("\n---------------------------------------\n");

		int wd;
		for (wd = 0; wd < weekday; wd++) { // ����� ���
			printf("     ");
		}

		for (int i = 1; i <= days_in_month[month]; i++) { // ��¥ ���
			if (wd == 0) {
				printf("\n");
			}
			wd = (wd + 1) % 7;
			printf("%5d", i);
		}

		printf("\n=========================================\n"); // ��� ���
		if (((month % 3) == 0) && (month != 12)) {
			printf("Hit any key to continue to next 3 months : ");
			_getch();
			printf("\n");
		}
	}

	return 0;
}


bool isLeapYear(int y) {
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
		return true;
	}
	else {
		return false;
	}
}

int getDaysFromJan01AD01(int year, int month, int day) {
	int days_from_0 = 0;
	int month_days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	for (int y = 1; y < year; y++) {
		days_from_0 += isLeapYear(y) ? 366 : 365;
	}
	if (isLeapYear(year)) {
		month_days[2] = 29;
	}
	for (int m = 1; m < month; m++) {
		days_from_0 += month_days[m];
	}
	days_from_0 += day;

	return days_from_0;
}
