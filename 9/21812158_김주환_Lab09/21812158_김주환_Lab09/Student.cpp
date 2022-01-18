// Student.cpp
#ifndef STUDENT_H
#define STUDENT_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Student.h"
#include "Date.h"
#include "Telephone_number.h"
#define MAX_NAME_LEN 20
#define NUM_STUDENTS 10
typedef struct {
	int st_id;
	char name[MAX_NAME_LEN];
	Date birth_date;
	Tel_Number tel_number;
	double GPA; // Grade Point Average
} Student;
void printStudent(Student* pST) {
	printf("Student [ID: %08d, %-10s", pST->st_id, pST->name);
	printf(", GPA: %5.2lf", pST->GPA);
	printf(", ");
	printDate(pST->birth_date);
	printf(", ");
	printTelephoneNumber(pST->tel_number);
	printf("]");
}
void printStudents(Student* stArr, int num) {
	Student* st = stArr;
	for (int i = 0; i < num; i++) {
		printStudent(st);
		printf("\n");
		st++;
	}
}
void shuffleStudents(Student stArray[], int num_students) {
	int st_1, st_2;
	Student st_temp;
	srand(time(0));
	for (int i = 0; i < num_students; i++) {
		st_1 = rand() % num_students;
		st_2 = rand() % num_students;
		st_temp = stArray[st_1];
		stArray[st_1] = stArray[st_2];
		stArray[st_2] = st_temp;
	}
}
void statisticsGPA(Student students[], int num_students) {
	/* Calculate the statistics of students' GPA : max, min, avg */
	Student* pST, * pST_max, * pST_min;
	pST_max = pST_min = pST = students;
	double GPA_max, GPA_min, GPA_avg, GPA_sum = 0.0;
	GPA_max = GPA_min = pST->GPA;
	GPA_sum = pST->GPA;
	for (int i = 1; i < num_students; i++) {
		pST = &students[i];
		if (GPA_max < pST->GPA)
			GPA_max = pST->GPA;
		if (GPA_min > pST->GPA)
			GPA_min = pST->GPA;
			GPA_sum += pST->GPA;
	} // end for
	GPA_avg = GPA_sum / (double)num_students;
	printf("GPA_max (%5.2lf), GPA_min (%5.2lf), GPA_avg (%5.2lf)\n",
		GPA_max, GPA_min, GPA_avg);
}
Student* searchBestGPAStudent(Student students[], int num) {
	/* Search the student with highest GPA */
	Student* pST, * pST_max;
	pST_max = pST = students;
	double GPA_max;
	GPA_max = pST->GPA;
	for (int i = 1; i < num; i++) {
		pST = &students[i];
		if (GPA_max < pST->GPA) {
			GPA_max = pST->GPA;
			pST_max = pST;
		}
	}
	return pST_max;
}
Student* searchWorstGPAStudent(Student students[], int num) {
	/* Search the student with highest GPA */
	Student* pST, * pST_min;
	pST_min = pST = students;
	double GPA_min;
	GPA_min = pST->GPA;
	for (int i = 1; i < num; i++) {
		pST = &students[i];
		if (GPA_min > pST->GPA) {
			GPA_min = pST->GPA;
			pST_min = pST;
		}
	}
	return pST_min;
}
void sortStudents_by_GPA(Student students[], int num) {
	/* Selection Sorting student array by GPA in decreasing order */
	Student* pST, * pST_max;
	Student temp;
	int st_max_id;
	for (int i = 0; i < num; i++) {
		pST_max = pST = &students[i];
		st_max_id = i;
		for (int j = i + 1; j < num; j++) {
			pST = &students[j];
			if (pST_max->GPA < pST->GPA) {
				pST_max = pST;
				st_max_id = j;
			}
		} // end for
		if (st_max_id != i) {
			temp = students[st_max_id];
			students[st_max_id] = students[i];
			students[i] = temp;
		}
	}
}
void sortStudents_by_ST_ID(Student students[], int num) {
	/* Selection Sorting student array by ST_ID in increasing order */
	Student* pST, * pST_min;
	Student temp;
	int st_id_min;
	for (int i = 0; i < num; i++) {
		pST_min = pST = &students[i];
		st_id_min = i;
		for (int j = i + 1; j < num; j++) {
			pST = &students[j];
			if (pST_min->st_id > pST->st_id) {
				pST_min = pST;
				st_id_min = j;
			}
		} // end for
		if (st_id_min != i) {
			temp = students[st_id_min];
			students[st_id_min] = students[i];
			students[i] = temp;
		}
	}
}
void sortStudents_by_name(Student students[], int num) {
	/* Selection Sorting student array by name in increasing order */
	Student* pST, * pST_min;
	Student temp;
	int st_name_min;
	for (int i = 0; i < num; i++) {
		pST_min = pST = &students[i];
		st_name_min = i;
		for (int j = i + 1; j < num; j++) {
			pST = &students[j];
			if (strcmp(pST->name, pST_min->name) < 0) {
				pST_min = pST;
				st_name_min = j;
			}
		} // end inner for
		if (st_name_min != i) {
			temp = students[st_name_min];
			students[st_name_min] = students[i];
			students[i] = temp;
		}
	} // end outer for
}
void sortStudents_by_BirthDate(Student students[], int num) {
	/* Selection Sorting student array by BirthDate in increasing order */
	Student* pST, * pST_min;
	Student temp;
	int st_date_min;
	for (int i = 0; i < num; i++) {
		pST_min = pST = &students[i];
		st_date_min = i;
		for (int j = i + 1; j < num; j++) {
			pST = &students[j];
			if (compareDate(pST->birth_date, pST_min->birth_date) < 0) {
				pST_min = pST;
				st_date_min = j;
			}
		}
		if (st_date_min != i) {
			temp = students[st_date_min];
			students[st_date_min] = students[i];
			students[i] = temp;
		}
	}
}
void sortStudents_by_TelNumber(Student students[], int num) {
	/* Selection Sorting student array by TelNo in increasing order */
	Student* pST, * pST_min;
	Student temp;
	int st_telno_min;
	for (int i = 0; i < num; i++) {
		pST_min = pST = &students[i];
		st_telno_min = i;
		for (int j = i + 1; j < num; j++) {
			pST = &students[j];
			if (compareTelNumber(pST->tel_number, pST_min->tel_number) < 0) {
				pST_min = pST;
				st_telno_min = j;
			}
		}
		if (st_telno_min != i) {
			temp = students[st_telno_min];
			students[st_telno_min] = students[i];
			students[i] = temp;
		}
	}
}
#endif