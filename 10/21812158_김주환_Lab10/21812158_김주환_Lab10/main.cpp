/*
* 파일명 : main.cpp
* 목적 및 기본 기능
*	SelectionSortWord, RandomFileAccess, BinaryFileDump, Cipher
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 5월 14일
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MyString.h"
#include "Student.h"
#include "HandlingBinaryFile.h"
#include "CipherMessage.h"

#define MAX_NUM_WORDS 1000

#define NUM_STUDENTS 10
#define MAX_STRING_LEN 512
#define MAX_NUM_STUDENTS 100
extern Student students[NUM_STUDENTS];
#define TEST_SORTING
#define TEST_BST_Student

#define MAX_STR_LEN 100

#define CIPHER_CODE 0X00 // cipher_code

void test_SelectionSortWords();
void test_RandomFileAccess_Student();
void test_BinaryFileDump();
void test_simple_cipher_text();

void main() {
	int menu;
	while (1) {
		printf(" 1. Test selection sort for words\n");
		printf(" 2. Test random access file for students records\n");
		printf(" 3. Test binary file dump\n");
		printf(" 4. Test cipher text\n");
		printf(" 0. Quit\n");
		printf("Input menu : ");
		scanf("%d", &menu);
		if (menu == 0)
			break;
		switch (menu) {
		case 1:
			test_SelectionSortWords();
			break;
		case 2:
			test_RandomFileAccess_Student();
			break;
		case 3:
			test_BinaryFileDump();
			break;
		case 4:
			test_simple_cipher_text();
			break;
		default:
			break;
		}
	}
}
void test_SelectionSortWords() {
	FILE* fin, *fout;
	char** word_array;
	int num_words = 0;

	fin = fopen("words.txt", "r"); // 데이터 파일 읽기모드 열기
	fout = fopen("sorted_words.txt", "w"); // 정렬 데이터를 입력할 파일 쓰기모드 열기

	word_array = (char**)calloc(MAX_NUM_WORDS, sizeof(char*));
	for (int i = 0; i < MAX_NUM_WORDS; i++)
		word_array[i] = (char*)calloc(21, sizeof(char));

	for (int i = 0; i < MAX_NUM_WORDS; i++) { // 실제 단어 개수 파악
		if (fscanf(fin, "%s", word_array[i]) == EOF)
			break;
		num_words++;
	}

	selectionSortWords(word_array, num_words); // selection sorting

	for (int i = 1; i <= num_words; i++) { // 출력
		fprintf(fout, "%22s", word_array[i - 1]);
		if ((i % 10) == 0)
			fprintf(fout, "\n");
	}
	free(word_array); // 동적 할당 해제
	fclose(fin); // 파일 닫기
}
void test_RandomFileAccess_Student() {
	FILE* fin, * fout;
	int ns = 0;
	int record_len;
	extern Student students[];
	char student_record[MAX_STRING_LEN] = { 0 };

	for (int i = 0; i < MAX_NUM_STUDENTS; i++) { // 학생 수 파악
		if (students[i].st_id == -1)
			break;
		else ns++;
	}

	fout = fopen("Sorted_Students.txt", "w"); // 정렬된 데이터를 입력할 파일 쓰기모드 열기
	if (fout == NULL) {
		printf("Error in opening Sorted_Students.txt (write mode)!!\n");
		exit;
	}

	printf("Array of students at initialization : \n");
	fprintf(fout, "Array of students at initialization : \n");
	printStudents(students, ns);
	fprintStudents(fout, students, ns);
	printf("\n");
	fprintf(fout, "\n");
	sortStudents_by_ST_ID(students, ns); // 학번에 따른 정렬
	printf("Storing sorted students by increasing order of student ID into SortedStudent.txt ....\n");
	fprintf(fout, "Storing sorted students by increasing order of student ID into SortedStudent.txt ....\n");
	printStudents(students, ns);
	fprintStudents(fout, students, ns);
	printf("\n");
	fprintf(fout, "\n");
	fclose(fout); // 파일 닫기

	fin = fopen("Sorted_Students.txt", "r"); // 정렬된 데이터 파일 읽기모드 열기
	if (fin == NULL) {
		printf("Error in opening Sorted_Students.txt (read mode)!!\n");
		exit;
	}
	int cur_pos;
	rewind(fin); // 커서 위치 초기화
	fgets(student_record, MAX_STRING_LEN, fin); // 원하는 크기만큼의 문자열 읽어오기
	record_len = strlen(student_record); // 해당 문자열 길이 반환
	fprintf(fout, "\nRandom access to Sorted_students.txt file (Student record length: %d) ...\n", record_len);
	for (int i = ns - 1; i >= 0; i--) { // 내림차순 정렬
		fseek(fin, (record_len + 1) * i, SEEK_SET); // 커서 위치 이동
		cur_pos = ftell(fin); // 커서 위치 반환
		printf("Current file_position : %3d\n", cur_pos);
		fgets(student_record, record_len + 1, fin);
		printf("Student (%2d): ", i);
		printStudent(students + i);
		printf("\n");
	}
	fclose(fin); // 파일 닫기
}
void test_BinaryFileDump() {
	FILE* fin, * fout;
	const char* fname = "Sorted_Students.txt"; // 실행 파일 생성
	if ((fin = fopen(fname, "rb")) == NULL) { // 실행 파일 읽기/ 바이너리 모드 열기
		printf("Error - binary input file (%s) cannot be openned !!\n", fname);
		exit;
	}
	if ((fout = fopen("Output.txt", "w")) == NULL) { // 출력할 파일 쓰기모드 열기
		printf("Error - Output.txt cannot be created !!\n");
		exit;
	}
	printf("Dumping binary file (%s) ... \n", fname);
	dumpBinaryFile(fin, fout); 
	fclose(fin); // 파일 닫기
	fclose(fout); // 파일 닫기
}
void test_simple_cipher_text() {
	FILE* fp_msg, * fp_tx, * fp_rx, * fp_dump_msg, * fout;

	fp_msg = fopen("Message.txt", "r"); // 암호화할 파일 읽기모드 열기
	if (fp_msg == NULL) {
		printf("Error in file open - Message.txt !!\n");
		exit(-1);
	}
	fp_tx = fopen("Ciphered.txt", "w"); // 암호화된 데이터를 입력할 파일 쓰기모드 열기
	if (fp_tx == NULL) {
		printf("Error in file open - Transmit.txt !!\n");
		exit(-1);
	}
	fout = fopen("Deciphered.txt", "w"); // 복호화된 데이터를 입력할 파일 쓰기모드 열기
	if (fout == NULL) {
		printf("Error in file open - Output.txt !!\n");
		exit(-1);
	}

	printf("Generating cipher text with cipher-code (%#04x) ..\n", CIPHER_CODE);
	cipherText(fp_msg, fp_tx, CIPHER_CODE); // 암호화
	fclose(fp_tx); // 암호화된 데이터 파일 닫기
	rewind(fp_msg); // 커서 위치 초기화
	fprintf(fout, "Binary dump of message.txt file: \n");
	dumpBinaryFile(fp_msg, fout);

	fp_tx = fopen("Ciphered.txt", "r"); // 암호화된 데이터 파일 읽기모드 열기
	if (fp_tx == NULL) {
		printf("Error in file open - Transmit.txt !!\n");
		exit(-1);
	}
	fprintf(fout, "\n=========================================\n");
	fprintf(fout, "Binary dump of ciphered document: \n");
	dumpBinaryFile(fp_tx, fout);
	rewind(fp_tx); // 커서 위치 초기화
	printf("Generating de-ciphered text with cipher-code (%#04x) ..\n", CIPHER_CODE);
	fprintf(fout, "\n=========================================\n");
	fprintf(fout, "Generating de-ciphered text with cipher-code (%#04x) ..\n", CIPHER_CODE);
	deCipherText(fp_tx, fout, CIPHER_CODE); // 복호화
	fclose(fp_msg); // 초기 데이터 파일 닫기
	fclose(fp_tx); // 암호화된 데이터 파일 닫기
	fclose(fout); // 복호화된 데이터 파일 닫기
}