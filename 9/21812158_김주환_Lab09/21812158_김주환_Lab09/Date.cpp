// Date.cpp
#ifndef DATE_H
#define DATE_H
#include <stdio.h>
#include "Date.h"
typedef struct {
	int year;
	int month;
	int day;
} Date;
void printDate(Date date) {
	printf("(%04d, %2d, %2d)",
		date.year, date.month, date.day);
}
int compareDate(Date d1, Date d2) {
	if (d1.year > d2.year)
		return 1;
	else if (d1.year < d2.year)
		return -1;
	else {
		if (d1.month > d2.month)
			return 1;
		else if (d1.month < d2.month)
			return -1;
		else {
			if (d1.day > d2.day)
				return 1;
			else if (d1.day < d2.day)
				return -1;
			else
				return 0;
		}
	}
}
#endif