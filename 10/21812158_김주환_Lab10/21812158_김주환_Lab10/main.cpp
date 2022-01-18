/*
* ���ϸ� : main.cpp
* ���� �� �⺻ ���
*	SelectionSortWord, RandomFileAccess, BinaryFileDump, Cipher
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 5�� 14��
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

	fin = fopen("words.txt", "r"); // ������ ���� �б��� ����
	fout = fopen("sorted_words.txt", "w"); // ���� �����͸� �Է��� ���� ������ ����

	word_array = (char**)calloc(MAX_NUM_WORDS, sizeof(char*));
	for (int i = 0; i < MAX_NUM_WORDS; i++)
		word_array[i] = (char*)calloc(21, sizeof(char));

	for (int i = 0; i < MAX_NUM_WORDS; i++) { // ���� �ܾ� ���� �ľ�
		if (fscanf(fin, "%s", word_array[i]) == EOF)
			break;
		num_words++;
	}

	selectionSortWords(word_array, num_words); // selection sorting

	for (int i = 1; i <= num_words; i++) { // ���
		fprintf(fout, "%22s", word_array[i - 1]);
		if ((i % 10) == 0)
			fprintf(fout, "\n");
	}
	free(word_array); // ���� �Ҵ� ����
	fclose(fin); // ���� �ݱ�
}
void test_RandomFileAccess_Student() {
	FILE* fin, * fout;
	int ns = 0;
	int record_len;
	extern Student students[];
	char student_record[MAX_STRING_LEN] = { 0 };

	for (int i = 0; i < MAX_NUM_STUDENTS; i++) { // �л� �� �ľ�
		if (students[i].st_id == -1)
			break;
		else ns++;
	}

	fout = fopen("Sorted_Students.txt", "w"); // ���ĵ� �����͸� �Է��� ���� ������ ����
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
	sortStudents_by_ST_ID(students, ns); // �й��� ���� ����
	printf("Storing sorted students by increasing order of student ID into SortedStudent.txt ....\n");
	fprintf(fout, "Storing sorted students by increasing order of student ID into SortedStudent.txt ....\n");
	printStudents(students, ns);
	fprintStudents(fout, students, ns);
	printf("\n");
	fprintf(fout, "\n");
	fclose(fout); // ���� �ݱ�

	fin = fopen("Sorted_Students.txt", "r"); // ���ĵ� ������ ���� �б��� ����
	if (fin == NULL) {
		printf("Error in opening Sorted_Students.txt (read mode)!!\n");
		exit;
	}
	int cur_pos;
	rewind(fin); // Ŀ�� ��ġ �ʱ�ȭ
	fgets(student_record, MAX_STRING_LEN, fin); // ���ϴ� ũ�⸸ŭ�� ���ڿ� �о����
	record_len = strlen(student_record); // �ش� ���ڿ� ���� ��ȯ
	fprintf(fout, "\nRandom access to Sorted_students.txt file (Student record length: %d) ...\n", record_len);
	for (int i = ns - 1; i >= 0; i--) { // �������� ����
		fseek(fin, (record_len + 1) * i, SEEK_SET); // Ŀ�� ��ġ �̵�
		cur_pos = ftell(fin); // Ŀ�� ��ġ ��ȯ
		printf("Current file_position : %3d\n", cur_pos);
		fgets(student_record, record_len + 1, fin);
		printf("Student (%2d): ", i);
		printStudent(students + i);
		printf("\n");
	}
	fclose(fin); // ���� �ݱ�
}
void test_BinaryFileDump() {
	FILE* fin, * fout;
	const char* fname = "Sorted_Students.txt"; // ���� ���� ����
	if ((fin = fopen(fname, "rb")) == NULL) { // ���� ���� �б�/ ���̳ʸ� ��� ����
		printf("Error - binary input file (%s) cannot be openned !!\n", fname);
		exit;
	}
	if ((fout = fopen("Output.txt", "w")) == NULL) { // ����� ���� ������ ����
		printf("Error - Output.txt cannot be created !!\n");
		exit;
	}
	printf("Dumping binary file (%s) ... \n", fname);
	dumpBinaryFile(fin, fout); 
	fclose(fin); // ���� �ݱ�
	fclose(fout); // ���� �ݱ�
}
void test_simple_cipher_text() {
	FILE* fp_msg, * fp_tx, * fp_rx, * fp_dump_msg, * fout;

	fp_msg = fopen("Message.txt", "r"); // ��ȣȭ�� ���� �б��� ����
	if (fp_msg == NULL) {
		printf("Error in file open - Message.txt !!\n");
		exit(-1);
	}
	fp_tx = fopen("Ciphered.txt", "w"); // ��ȣȭ�� �����͸� �Է��� ���� ������ ����
	if (fp_tx == NULL) {
		printf("Error in file open - Transmit.txt !!\n");
		exit(-1);
	}
	fout = fopen("Deciphered.txt", "w"); // ��ȣȭ�� �����͸� �Է��� ���� ������ ����
	if (fout == NULL) {
		printf("Error in file open - Output.txt !!\n");
		exit(-1);
	}

	printf("Generating cipher text with cipher-code (%#04x) ..\n", CIPHER_CODE);
	cipherText(fp_msg, fp_tx, CIPHER_CODE); // ��ȣȭ
	fclose(fp_tx); // ��ȣȭ�� ������ ���� �ݱ�
	rewind(fp_msg); // Ŀ�� ��ġ �ʱ�ȭ
	fprintf(fout, "Binary dump of message.txt file: \n");
	dumpBinaryFile(fp_msg, fout);

	fp_tx = fopen("Ciphered.txt", "r"); // ��ȣȭ�� ������ ���� �б��� ����
	if (fp_tx == NULL) {
		printf("Error in file open - Transmit.txt !!\n");
		exit(-1);
	}
	fprintf(fout, "\n=========================================\n");
	fprintf(fout, "Binary dump of ciphered document: \n");
	dumpBinaryFile(fp_tx, fout);
	rewind(fp_tx); // Ŀ�� ��ġ �ʱ�ȭ
	printf("Generating de-ciphered text with cipher-code (%#04x) ..\n", CIPHER_CODE);
	fprintf(fout, "\n=========================================\n");
	fprintf(fout, "Generating de-ciphered text with cipher-code (%#04x) ..\n", CIPHER_CODE);
	deCipherText(fp_tx, fout, CIPHER_CODE); // ��ȣȭ
	fclose(fp_msg); // �ʱ� ������ ���� �ݱ�
	fclose(fp_tx); // ��ȣȭ�� ������ ���� �ݱ�
	fclose(fout); // ��ȣȭ�� ������ ���� �ݱ�
}