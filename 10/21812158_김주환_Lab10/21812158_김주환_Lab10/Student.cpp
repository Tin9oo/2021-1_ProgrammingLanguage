// Student.cpp
#define _CRT_SECURE_NO_WARNINGS

#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Student.h"

#define U_SHORT unsigned short
#define MAX_NAME_LEN 20
#define NUM_STUDENTS 10

typedef struct {
	int year;
	int month;
	int day;
} Date;
typedef struct {
	U_SHORT nation_code;
	U_SHORT region_no;
	U_SHORT switch_no;
	U_SHORT line_no;
} Tel_Number;
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
	printf("(%04d, %2d, %2d)", pST->birth_date.year, pST->birth_date.month, pST->birth_date.day);
	printf(", ");
	printf("(tel: +%d-", pST->tel_number.nation_code);
	printf("%03d-%04d-%04d)", pST->tel_number.region_no, pST->tel_number.switch_no, pST->tel_number.line_no);
	printf("]");
}
void printStudents(Student* stArr, int num_students) {
	Student* st = stArr;
	for (int i = 0; i < num_students; i++) {
		printStudent(st);
		printf("\n");
		st++;
	}
}
void fprintStudent(FILE* fout, Student* pST) {
	fprintf(fout, "Student [ID: %08d, %-10s", pST->st_id, pST->name);
	fprintf(fout, ", GPA: %5.2lf", pST->GPA);
	fprintf(fout, ", ");
	fprintf(fout, "(%04d, %2d, %2d)", pST->birth_date.year, pST->birth_date.month, pST->birth_date.day);
	fprintf(fout, ", ");
	fprintf(fout, "(tel: +%d-", pST->tel_number.nation_code);
	fprintf(fout, "%03d-%04d-%04d)", pST->tel_number.region_no, pST->tel_number.switch_no, pST->tel_number.line_no);
	fprintf(fout, "]");
}
void fprintStudents(FILE* fout, Student* stArr, int num_students) {
	Student* st = stArr;
	for (int i = 0; i < num_students; i++) {
		fprintStudent(fout, st);
		fprintf(fout, "\n");
		st++;
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
#endif