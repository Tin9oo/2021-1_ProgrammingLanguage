// Student.h
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
void printStudent(Student* pST);
void printStudents(Student* stArr, int num_students);
void shuffleStudents(Student students[], int num_students);
void statisticsGPA(Student students[], int num_students);
Student* searchBestGPAStudent(Student students[], int num);
Student* searchWorstGPAStudent(Student students[], int num);
void sortStudents_by_GPA(Student students[], int num);
void sortStudents_by_ST_ID(Student students[], int num);
void sortStudents_by_name(Student students[], int num);
void sortStudents_by_BirthDate(Student students[], int num);
void sortStudents_by_TelNumber(Student students[], int num);
#endif