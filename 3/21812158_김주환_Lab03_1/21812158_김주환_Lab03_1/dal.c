/*
* 파일명 : get_days_from_0.c
* 목적 및 기본 기능
*	연월일 3개 정수로 지정된 날짜를 입력받아,
*	서기 (AD) 1년 1월 1일로부터 몇 번째 날이며,
*   무슨 요일인가를 계산하여 출력하기 위한
*   함수 bool isLeapYear(int y)와
*   int getDaysFromJan01AD01(int year, int month, int day)를 작성하라.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 3월 18일
*/
#include <stdio.h>
#include <stdbool.h>

#define DAYS_PER_WEEK 7
#define NUM_MONTHS 13

enum MONTH { January = 1, Fabruary, March, April, May, June, July, August, September, October, November, December };
enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT };
const char* month_name[NUM_MONTHS] = { "", "January", "Fabruary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
const char* week_day_name[DAYS_PER_WEEK] = { "SUN", "MON", "TUE", "WED", "THR", "FRI", "SAT" };

bool isLeapYear(int y);
int getDaysFromJan01AD01(int year, int month, int day);
void due_to_cristmas(int year, int month, int day);
void get_after_100days(int year, int month, int day);
void print_days(int year, int month, int day, int all);
void print_cristmas(int year, int month, int day, int all);
void print_after100(int year, int month, int day);


int main(void) {
	int year, month, day;
	int all;

	/*for (int m = January; m <= December; m++) {
		printf("%s\n", month_name[m]);
		for (int w = SUN; w <= SAT; w++) {
			printf("%s ", week_day_name[w]);
		}
		printf("\n\n");
	}*/

	printf("Input year, month, dat to check : ");
	scanf("%d %d %d", &year, &month, &day);

	all = getDaysFromJan01AD01(year, month, day);
	print_days(year, month, day, all);
	printf("\n\n");

	for (int i = 2011; i < 2022; i++) {
		all = getDaysFromJan01AD01(i, 1, 1);
		print_days(i, month, day, all);
	}
	printf("\n\n");

	due_to_cristmas(year, month, day);
	get_after_100days(year, month, day);

	return 0;
}

bool isLeapYear(int y) {
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
		return true;
	else
		return false;
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

void due_to_cristmas(int year, int month, int day) {
	int days_from_0 = 0;
	int month_days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int cristmas = getDaysFromJan01AD01(2021, 12, 25);

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

	cristmas -= days_from_0;

	print_cristmas(year, month, day, cristmas);
	printf("\n\n");
}

void get_after_100days(int year, int month, int day) {
	int after_day = 0;
	int month_days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int ye = 0, mo = 0, da = 0;

	for (int y = 1; y < year; y++) {
		after_day += isLeapYear(y) ? 366 : 365;
	}
	if (isLeapYear(year)) {
		month_days[2] = 29;
	}
	for (int m = 1; m < month; m++) {
		after_day += month_days[m];
	}
	after_day += day + 100;

	int i = -1;
	while (after_day >= (isLeapYear(++i) ? 366 : 365)) {
		after_day -= isLeapYear(i) ? 366 : 365;
		ye++;
	}

	int j = -1;
	while (after_day >= month_days[++j]) {
		if (isLeapYear(year)) {
			month_days[2] = 29;
		}
		else {
			month_days[2] = 28;
		}
		after_day -= month_days[j];
		mo++;
	}
	da = after_day;

	print_after100(ye, mo, da);
}

void print_days(int year, int month, int day, int all) {
	printf("The week day of ");
	switch (month) {
	case 1:
		printf("January ");
		break;
	case 2:
		printf("Fabruary ");
		break;
	case 3:
		printf("March ");
		break;
	case 4:
		printf("April ");
		break;
	case 5:
		printf("May ");
		break;
	case 6:
		printf("June ");
		break;
	case 7:
		printf("July ");
		break;
	case 8:
		printf("August ");
		break;
	case 9:
		printf("September ");
		break;
	case 10:
		printf("October ");
		break;
	case 11:
		printf("November ");
		break;
	case 12:
		printf("December ");
		break;
	default:
		break;
	}
	printf("%d, %d is %d-th day from Jan 1, 1 ", day, year, all);
	switch (all % 7) {
	case 0:
		printf("(SUN)");
		break;
	case 1:
		printf("(MON)");
		break;
	case 2:
		printf("(TUE)");
		break;
	case 3:
		printf("(WED)");
		break;
	case 4:
		printf("(THR)");
		break;
	case 5:
		printf("(FRI)");
		break;
	case 6:
		printf("(SAT)");
		break;
	default:
		break;
	}
	printf("\n");
}

void print_cristmas(int year, int month, int day, int all) {
	printf("The week day of ");
	switch (month) {
	case 1:
		printf("January ");
		break;
	case 2:
		printf("Fabruary ");
		break;
	case 3:
		printf("March ");
		break;
	case 4:
		printf("April ");
		break;
	case 5:
		printf("May ");
		break;
	case 6:
		printf("June ");
		break;
	case 7:
		printf("July ");
		break;
	case 8:
		printf("August ");
		break;
	case 9:
		printf("September ");
		break;
	case 10:
		printf("October ");
		break;
	case 11:
		printf("November ");
		break;
	case 12:
		printf("December ");
		break;
	default:
		break;
	}
	printf("%d, %d due to %d-th day due to cristmas ", day, year, all);
	switch (all % 7) {
	case 0:
		printf("(SUN)");
		break;
	case 1:
		printf("(MON)");
		break;
	case 2:
		printf("(TUE)");
		break;
	case 3:
		printf("(WED)");
		break;
	case 4:
		printf("(THR)");
		break;
	case 5:
		printf("(FRI)");
		break;
	case 6:
		printf("(SAT)");
		break;
	default:
		break;
	}
	printf("\n");
}

void print_after100(int year, int month, int day) {
	printf("After 100 days is ");
	switch (month) {
	case 1:
		printf("January ");
		break;
	case 2:
		printf("Fabruary ");
		break;
	case 3:
		printf("March ");
		break;
	case 4:
		printf("April ");
		break;
	case 5:
		printf("May ");
		break;
	case 6:
		printf("June ");
		break;
	case 7:
		printf("July ");
		break;
	case 8:
		printf("August ");
		break;
	case 9:
		printf("September ");
		break;
	case 10:
		printf("October ");
		break;
	case 11:
		printf("November ");
		break;
	case 12:
		printf("December ");
		break;
	default:
		break;
	}
	printf("%d, %d  ", day, year);

	/*switch (all % 7) {
	case 0:
		printf("(SUN)");
		break;
	case 1:
		printf("(MON)");
		break;
	case 2:
		printf("(TUE)");
		break;
	case 3:
		printf("(WED)");
		break;
	case 4:
		printf("(THR)");
		break;
	case 5:
		printf("(FRI)");
		break;
	case 6:
		printf("(SAT)");
		break;
	default:
		break;
	}*/
	printf("\n");
}