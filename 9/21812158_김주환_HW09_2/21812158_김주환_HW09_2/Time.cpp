/* Time.h */
#ifndef TIME_H
#define TIME_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Time.h"
typedef struct {
	int hour;
	int min;
	int sec;
} Time;
Time inputTime() {
	Time create;
	create.hour = 0;
	create.min = 0;
	create.sec = 0;
	while (1) {
		printf("input hour minute sec : ");
		scanf_s("%d %d %d", &create.hour, &create.min, &create.sec);
		if ((create.hour < 24) && (create.hour >= 0) &&
			(create.min < 60) && (create.min >= 0) &&
			(create.sec < 60) && (create.sec >= 0))
			break;
	}

	return create;
}
Time initTime(int h, int m, int s) {
	Time create;
	create.hour = h;
	create.min = m;
	create.sec = s;
	return create;
}
void printTime(const Time* t) {
	printf("(%02d:%02d:%02d)\n", t->hour, t->min, t->sec);
}
void incrementTime(Time* t, int incr_sec) {
	for (int i = 1; i <= incr_sec; i++) {
		t->sec += 1;
		if (t->sec == 60) {
			t->sec = 0;
			t->min += 1;
			if (t->min == 60) {
				t->min = 0;
				t->hour += 1;
				if (t->hour == 24)
					t->hour = 0;
			}
		}
	}
}
int compareTime(const Time* t1, const Time* t2) {
	int f, s;
	int diff = 0;
	f = t1->hour * 3600 + t1->min * 60 + t1->sec;
	s = t2->hour * 3600 + t2->min * 60 + t2->sec;
	if (diff < 0)
		diff = 3600 * 24 - f + s;

	return s - f;
}
void selectSortTime(Time* times, int size) {
	int* secA, sec, min, temp;
	Time temp_st;
	secA = (int*)calloc(size, sizeof(int));
	if (secA == NULL)
		exit(-1);

	for (int i = 0; i < size; i++)
	{
		sec = 3600 * times[i].hour + 60 * times[i].min + times[i].sec;
		secA[i] = sec;
	}
	for (int i = 0; i < size - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (secA[j] < secA[min])
				min = j;
		}
		if (min != i)
		{
			temp_st = times[i];
			times[i] = times[min];
			times[min] = temp_st;

			temp = secA[i];
			secA[i] = secA[min];
			secA[min] = temp;
		}
	}
	free(secA);

}
#endif