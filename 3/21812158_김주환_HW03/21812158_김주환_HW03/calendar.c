/*
* 파일명 : calendar.c
* 목적 및 기본 기능
*	연도를 입력받고, 이 연도의 1월 ~ 12월 달력을 월별로 출력하는 알고리즘의
*   pseudo code를 작성하라. 해당 연도가 윤년인가를 확인하여, 이에 따라
*   정확한 2월 출력이 될 수 있게 할 것.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 3월 22일
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

	printf("몇년인가 : ");
	scanf("%d", &year);

	printf("> > > > > > Calendar of %d < < < < < <\n", year);
	for (int month = 1; month <= 12; month++) {
		day_from_0 = getDaysFromJan01AD01(year, month, 1);
		weekday = day_from_0 % 7;

		if (isLeapYear(year)) { // 윤년계산
			days_in_month[2] = 29;
		}

		printf("%s\n", month_name[month]);
		printf("=========================================\n");
		for (int wk = 0; wk <= 6; wk++) { // 요일 출력
			printf("%5s", week_day_name[wk]);
		}
		printf("\n---------------------------------------\n");

		int wd;
		for (wd = 0; wd < weekday; wd++) { // 빈공간 출력
			printf("     ");
		}

		for (int i = 1; i <= days_in_month[month]; i++) { // 날짜 출력
			if (wd == 0) {
				printf("\n");
			}
			wd = (wd + 1) % 7;
			printf("%5d", i);
		}

		printf("\n=========================================\n"); // 끊어서 출력
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
