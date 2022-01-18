// Date.h
#ifndef DATE_H
#define DATE_H
#include <stdio.h>
#include "Date.h"
typedef struct {
	int year;
	int month;
	int day;
} Date;
void printDate(Date date);
int compareDate(Date d1, Date d2);
#endif