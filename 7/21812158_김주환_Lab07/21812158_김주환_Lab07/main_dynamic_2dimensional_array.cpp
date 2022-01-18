/*
* ���ϸ� : main_dynammic_2dimensional_array.cpp
* ���� �� �⺻ ���
*	2���� �迭�� ���� �Ҵ��� ���� �����ϰ� ��� ����, ����, ����, ����� ���ϴ� ���
*   �� �����ϰ� ����â�� ���Ͽ� ����Ѵ�.
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 4�� 14��
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
			check_address_2dim_array_for_matrix(); // ������ �迭�� �̸� �ּҸ� ���
			break;
		case 2:
			test_2d_dynamic_array_FileIO(); // ������ ����� �ҷ��� �� �ִ��� Ȯ��
			break;
		case 3:
			test_matrix_addition_subtraction(); // ��� ����, ���� ���
			break;
		case 4:
			test_matrix_multiplication(); // ��� ���� ���
			break;
		case 5:
			test_matrix_average(); // ��� Ư¡
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

	fin = fopen(matrix_data_file, "r"); // ���� �б� ���� ����
	if (fin == NULL) {
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}

	// ��� A
	fscanf(fin, "%d %d", &a_row_size, &a_col_size); // ��� ũ�� �Ǵ�
	dma = fget_double_mtrx(fin, dma, a_row_size, a_col_size); // ���� �Ҵ� �� ��� �ҷ�����
	printf("Input Matrix_A (%d x %d) : \n", a_row_size, a_col_size);
	print_mtrx(dma, a_row_size, a_col_size); // ��� ���
	printf("\n");

	// ��� B
	fscanf(fin, "%d %d", &b_row_size, &b_col_size);
	dmb = fget_double_mtrx(fin, dmb, b_row_size, b_col_size);
	printf("Input Matrix_B (%d x %d) : \n", b_row_size, b_col_size);
	print_mtrx(dmb, b_row_size, b_col_size);
	printf("\n");

	delete_double_mtrx(dma, a_row_size, a_col_size); // ���� �Ҵ� ����
	delete_double_mtrx(dmb, b_row_size, b_col_size);
	fclose(fin); // ���� �ݱ�
}
void test_matrix_addition_subtraction() {
	const char* matrix_data_file = "mtrx_nxn_InputData.txt";
	FILE* fin;

	double** dma = NULL, ** dmb = NULL, ** dmc, ** dmd;
	int a_row_size = 0, a_col_size = 0;
	int b_row_size = 0, b_col_size = 0;
	int c_row_size = 0, c_col_size = 0;
	int d_row_size = 0, d_col_size = 0;

	fin = fopen(matrix_data_file, "r"); // ���� �б� ���� ����
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
	fin = fopen(MTRXINPUTDATA, "r"); // ���� �б� ���� ����
	if (fin == NULL) {
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}

	fscanf(fin, "%d %d", &a_row_size, &a_col_size); // ��� ũ�� �Ǵ�
	dma = fget_double_mtrx(fin, dma, a_row_size + 1, a_col_size + 1); // ���� �Ҵ��� ���Ͽ��� ��� �ҷ�����
	average_mtrx(dma, a_row_size, a_col_size);
	printf("Input Matrix_A (%d x %d) : \n", a_row_size++, a_col_size++);
	print_mtrx(dma, a_row_size, a_col_size); // ��� ���
	printf("\n");

	delete_double_mtrx(dma, a_row_size, a_col_size); // ���� �Ҵ� ����
	fclose(fin); // ���� �ݱ�
#undef AM
}