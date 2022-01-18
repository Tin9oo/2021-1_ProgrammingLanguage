/*
* 파일명 : main_dynammic_2dimensional_array.cpp
* 목적 및 기본 기능
*	2차원 배열을 동적 할당을 통해 생성하고 행렬 덧셈, 뺄셈, 곱셈, 평균을 구하는 계산
*   을 실행하고 실행창과 파일에 출력한다.
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 4월 14일
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

#define MTRXINPUTDATA "mtrxInputData.txt"
#define MTRXNXNINPUTDATA "mtrx_nxn_InputData.txt"

void check_address_2dim_array_for_matrix();
void test_2d_dynamic_array_FileIO();
void test_matrix_addition_subtraction();
void test_matrix_multiplication();
void test_matrix_average();

int main(void) {
	int menu;

	while (1) {
		printf("Testing Matrix Operations with 2-Dimensional Dynamic Array\n");
		printf("1 : Check addresses of 2-Dim array for Matrix\n");
		printf("2 : Test 2-D Dynamic Array Creation for Matrix with File I/O\n");
		printf("3 : Test Matrix Addition, Subtraction\n");
		printf("4 : Test Matrix Multiplication\n");
		printf("5 : Test Matrix Trait\n");
		printf("-1 : Quit\n");
		printf("Input menu (-1 to quit) : ");
		scanf("%d", &menu);
		if (menu == -1)break;
		printf("\n");
		switch (menu) {
		case 1:
			check_address_2dim_array_for_matrix(); // 생성한 배열의 이름 주소를 출력
			break;
		case 2:
			test_2d_dynamic_array_FileIO(); // 파일의 행렬을 불러낼 수 있는지 확인
			break;
		case 3:
			test_matrix_addition_subtraction(); // 행렬 덧셈, 뺄셈 계산
			break;
		case 4:
			test_matrix_multiplication(); // 행렬 곱셈 계산
			break;
		case 5:
			test_matrix_average(); // 행렬 특징
		default:
			break;
		}
	}
	return 0;
}
void check_address_2dim_array_for_matrix() {
	int m[3][3] = {
		10, 20, 30, 40, 50, 60, 70, 80, 90
	};
	
	printf("m        = %p\n", m);
	printf("m[0]     = %p\n", m[0]);
	printf("m[1]     = %p\n", m[1]);
	printf("m[2]     = %p\n", m[2]);
	printf("&m[0][0] = %p\n", &m[0][0]);
	printf("&m[1][0] = %p\n", &m[1][0]);
	printf("&m[2][0] = %p\n", &m[2][0]);
	printf("\n");
}
void test_2d_dynamic_array_FileIO() {
	const char* matrix_data_file = "mtrxInputData.txt";
	FILE* fin;
	int a_row_size = 0, a_col_size = 0;
	int b_row_size = 0, b_col_size = 0;
	double** dma = NULL, ** dmb = NULL;

	fin = fopen(matrix_data_file, "r"); // 파일 읽기 모드로 열기
	if (fin == NULL) {
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}

	// 행렬 A
	fscanf(fin, "%d %d", &a_row_size, &a_col_size); // 행렬 크기 판단
	dma = fget_double_mtrx(fin, dma, a_row_size, a_col_size); // 동적 할당 후 행렬 불러오기
	printf("Input Matrix_A (%d x %d) : \n", a_row_size, a_col_size);
	print_mtrx(dma, a_row_size, a_col_size); // 행렬 출력
	printf("\n");

	// 행렬 B
	fscanf(fin, "%d %d", &b_row_size, &b_col_size);
	dmb = fget_double_mtrx(fin, dmb, b_row_size, b_col_size);
	printf("Input Matrix_B (%d x %d) : \n", b_row_size, b_col_size);
	print_mtrx(dmb, b_row_size, b_col_size);
	printf("\n");

	delete_double_mtrx(dma, a_row_size, a_col_size); // 동적 할당 해제
	delete_double_mtrx(dmb, b_row_size, b_col_size);
	fclose(fin); // 파일 닫기
}
void test_matrix_addition_subtraction() {
	const char* matrix_data_file = "mtrx_nxn_InputData.txt";
	FILE* fin;

	double** dma = NULL, ** dmb = NULL, ** dmc, ** dmd;
	int a_row_size = 0, a_col_size = 0;
	int b_row_size = 0, b_col_size = 0;
	int c_row_size = 0, c_col_size = 0;
	int d_row_size = 0, d_col_size = 0;

	fin = fopen(matrix_data_file, "r"); // 파일 읽기 모드로 열기
	if (fin == NULL) {
		printf("Error in openning input.txt file !!\n");
		exit(-1);
	}

	fscanf(fin, "%d %d", &a_row_size, &a_col_size);
	dma = fget_double_mtrx(fin, dma, a_row_size, a_col_size);
	printf("Input Matrix_A (%d x %d) : \n", a_row_size, a_col_size);
	print_mtrx(dma, a_row_size, a_col_size);
	printf("\n");

	fscanf(fin, "%d %d", &b_row_size, &b_col_size);
	dmb = fget_double_mtrx(fin, dmb, b_row_size, b_col_size);
	printf("Input Matrix_B (%d x %d) : \n", b_row_size, b_col_size);
	print_mtrx(dmb, b_row_size, b_col_size);
	printf("\n");

	if ((a_row_size != b_row_size) || (a_col_size != b_col_size)) {
		printf("Error in input matrix dimension : row_size and/or col_size are not equal !!\n");
		fclose(fin);
		return;
	}

	c_row_size = a_row_size;
	c_col_size = b_col_size;
	dmc = create_double_mtrx(c_row_size, c_col_size);
	add_mtrx(dma, dmb, dmc, a_row_size, a_col_size);
	printf("Matrix_C (%d x %d) = Matrix_A + Matrix_B :\n", c_row_size, c_col_size);
	print_mtrx(dmc, c_row_size, c_col_size);
	printf("\n");

	d_row_size = a_row_size;
	d_col_size = b_col_size;
	dmd = create_double_mtrx(d_row_size, d_col_size);
	sub_mtrx(dma, dmb, dmd, a_row_size, a_col_size);
	printf("Matrix_D (%d x %d) = Matrix_A - Matrix_B :\n", d_row_size, d_col_size);
	print_mtrx(dmd, d_row_size, d_col_size);
	printf("\n");

	delete_double_mtrx(dma, a_row_size, a_col_size);
	delete_double_mtrx(dmb, b_row_size, b_col_size);
	delete_double_mtrx(dmc, c_row_size, c_col_size);
	delete_double_mtrx(dmd, d_row_size, d_col_size);

	fclose(fin);
}
void test_matrix_multiplication() {
	const char* matrix_data_file = "mtrxInputData.txt";
	FILE* fin;

	int a_row_size = 0, a_col_size = 0;
	int b_row_size = 0, b_col_size = 0;
	int c_row_size = 0, c_col_size = 0;
	int temp = 0;
	
	double** dma = NULL, ** dmb = NULL, ** dmc = NULL;
	fin = fopen(matrix_data_file, "r");
	if (fin == NULL) {
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	fscanf(fin, "%d %d", &a_row_size, &a_col_size);
	dma = fget_double_mtrx(fin, dma, a_row_size, a_col_size);
	printf("Input Matrix_A (%d x %d) : \n", a_row_size, a_col_size);
	print_mtrx(dma, a_row_size, a_col_size);
	printf("\n");

	fscanf(fin, "%d %d", &b_row_size, &b_col_size);
	dmb = fget_double_mtrx(fin, dmb, b_row_size, b_col_size);
	printf("Input Matrix_B (%d x %d) : \n", b_row_size, b_col_size);
	print_mtrx(dmb, b_row_size, b_col_size);
	printf("\n");

	temp = a_col_size;
	c_row_size = a_row_size;
	c_col_size = b_col_size;
	dmc = create_double_mtrx(c_row_size, c_col_size);
	multiply_mtrx(dma, dmb, dmc, c_row_size, c_col_size, temp);
	printf("Matrix_C (%d x %d) = Matrix_A x Matrix_B :\n", c_row_size, c_col_size);
	print_mtrx(dmc, c_row_size, c_col_size);
	printf("\n");

	delete_double_mtrx(dma, a_row_size, a_col_size);
	delete_double_mtrx(dmb, b_row_size, b_col_size);
	delete_double_mtrx(dmc, c_row_size, c_col_size);

	fclose(fin);
}
void test_matrix_average() {
	FILE* fin;
	int a_row_size = 0, a_col_size = 0;
	double** dma = NULL;
#define AM
	fin = fopen(MTRXINPUTDATA, "r"); // 파일 읽기 모드로 열기
	if (fin == NULL) {
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}

	fscanf(fin, "%d %d", &a_row_size, &a_col_size); // 행렬 크기 판단
	dma = fget_double_mtrx(fin, dma, a_row_size + 1, a_col_size + 1); // 동적 할당후 파일에서 행렬 불러오기
	average_mtrx(dma, a_row_size, a_col_size);
	printf("Input Matrix_A (%d x %d) : \n", a_row_size++, a_col_size++);
	print_mtrx(dma, a_row_size, a_col_size); // 행렬 출력
	printf("\n");

	delete_double_mtrx(dma, a_row_size, a_col_size); // 동적 할당 해제
	fclose(fin); // 파일 닫기
#undef AM
}