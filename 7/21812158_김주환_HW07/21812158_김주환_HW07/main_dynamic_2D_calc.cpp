/*
* ���ϸ� : main_dynammic_2D_calc.cpp
* ���� �� �⺻ ���
*	2���� �迭�� ���� �Ҵ��� ���� �����ϰ� ��� ����, ����, ����, ����� ���ϴ� ���
*   �� �����ϰ� ����â�� ���Ͽ� ����Ѵ�.
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 4�� 19��
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

#define MTRXINPUTDATA "input_data.txt" // ����ϴ� ���� �̸�

int main(void) {
	FILE* fin;

	double** dma = NULL, ** dmb = NULL, ** dmc = NULL; // ����� 2���� �迭 ������
	int a_row_size = 0, a_col_size = 0; // ��� ũ��
	int b_row_size = 0, b_col_size = 0;
	int c_row_size = 0, c_col_size = 0;
	int temp = 0; // ����� �� ���� ����

	fin = fopen(MTRXINPUTDATA, "r"); // ���� �б� ���� ����
	if (fin == NULL) {
		printf("Error in openning input.txt file !!\n");
		exit(-1);
	}

	dma = input_mtrx(fin, dma, &a_row_size, &a_col_size); // �⺻ ���
	printf("Input Matrix_A (%d x %d) : \n", a_row_size, a_col_size);
	print_mtrx(dma, a_row_size, a_col_size);
	printf("\n");

	dmb = input_mtrx(fin, dmb, &b_row_size, &b_col_size);
	printf("Input Matrix_B (%d x %d) : \n", b_row_size, b_col_size);
	print_mtrx(dmb, b_row_size, b_col_size);
	printf("\n");

	c_row_size = a_row_size;
	c_col_size = b_col_size;
	dmc = input_mtrx(fin, dmc, &c_row_size, &c_col_size); // ������ ����� ���� �迭 ����

	dmc = add_mtrx(dma, dmb, dmc, a_row_size, a_col_size); // ��� ����
	printf("Matrix_C (%d x %d) = Matrix_A + Matrix_B :\n", c_row_size, c_col_size);
	print_mtrx(dmc, c_row_size, c_col_size);
	printf("\n");

	dmc = sub_mtrx(dma, dmb, dmc, a_row_size, a_col_size); // ��� ����
	printf("Matrix_D (%d x %d) = Matrix_A - Matrix_B :\n", c_row_size, c_col_size);
	print_mtrx(dmc, c_row_size, c_col_size);
	printf("\n");

	temp = c_row_size;
	dmc = multiply_mtrx(dma, dmb, dmc, c_row_size, c_col_size, temp); // ��� ����
	printf("Matrix_C (%d x %d) = Matrix_A x Matrix_B :\n", c_row_size, c_col_size);
	print_mtrx(dmc, c_row_size, c_col_size);
	printf("\n");

	delete_double_mtrx(dma, a_row_size, a_col_size); // ���� ������ �迭 ����
	delete_double_mtrx(dmb, b_row_size, b_col_size);
	delete_double_mtrx(dmc, c_row_size, c_col_size);
	fclose(fin); // ���� �ݱ�
	return 0;
}