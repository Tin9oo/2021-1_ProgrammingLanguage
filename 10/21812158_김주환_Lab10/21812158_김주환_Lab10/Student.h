// Student.h
#define _CRT_SECURE_NO_WARNINGS

#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
void printStudent(Student* pST);
void printStudents(Student * stArr, int num_students);
void fprintStudent(FILE* fout, Student* pST);
void fprintStudents(FILE* fout, Student* stArr, int num_students);
void sortStudents_by_ST_ID(Student students[], int num);
#endif