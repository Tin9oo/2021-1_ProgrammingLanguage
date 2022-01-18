/* Time.h */
#ifndef TIME_H
#define TIME_H
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int hour;
	int min;
	int sec;
} Time;
Time inputTime();
Time initTime(int h, int m, int s);
void printTime(const Time* t);
void incrementTime(Time* t, int incr_sec);
int elapsedSeconds(const Time* t);
int compareTime(const Time* t1, const Time* t2);
void selectSortTime(Time* times, int size);
#endif