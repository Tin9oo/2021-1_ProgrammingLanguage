/*
* ���ϸ� : main_Matrix_Operations.cpp
* ���� �� �⺻ ���
*	�־��� ��Ŀ� �⺻ ������ ����
*	������� ���ϰ� ����
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 5�� 3��
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

void main() {
	FILE* fin_ABC, * fout;
	const char* input_file_ABC = "mtrx_AB_6x7_C_7x6.txt"; // ���� �̸�
	const char* output_file = "mtrx_operations_results.txt";
	double** mA, ** mB, ** mC, ** mD, ** mE, ** mF, ** inv_mF, ** mI;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	int c_row_size, c_col_size;
	int d_row_size, d_col_size;
	int e_row_size, e_col_size, k_size;
	int f_row_size, f_col_size;
	fin_ABC = fopen(input_file_ABC, "r"); // �Է¹��� ���� ����
	if (fin_ABC == NULL) {
		printf("Error in opening input data file (%s) !!", input_file_ABC);
		exit;
	}
	fout = fopen(output_file, "w"); // �Է��� ���� ����
	if (fout == NULL) {
		printf("Error in opening output data file (%s) !!", output_file);
		exit;
	}
	mA = fGetMtrx(fin_ABC, &a_row_size, &a_col_size); // �⺻ �迭 �а� ���
	printMtrx((const char*)"mA", mA, a_row_size, a_col_size);
	fprintMtrx(fout, (const char*)"mA", mA, a_row_size, a_col_size);
	mB = fGetMtrx(fin_ABC, &b_row_size, &b_col_size);
	printMtrx((const char*)"mB", mB, b_row_size, b_col_size);
	fprintMtrx(fout, (const char*)"mB", mB, b_row_size, b_col_size);
	mC = fGetMtrx(fin_ABC, &c_row_size, &c_col_size);
	printMtrx((const char*)"mC", mC, c_row_size, c_col_size);
	fprintMtrx(fout, (const char*)"mC", mC, c_row_size, c_col_size);
	d_row_size = a_row_size;
	d_col_size = b_col_size;
	mD = addMtrx(mA, mB, a_row_size, a_col_size); // ����
	printMtrx((const char*)"mC", mC, c_row_size, c_col_size);
	fprintMtrx(fout, (const char*)"mC", mC, c_row_size, c_col_size);
	e_row_size = a_row_size;
	e_col_size = b_col_size;
	mE = subtractMtrx(mA, mB, e_row_size, e_col_size); // ����
	printMtrx((const char*)"mE = mA - mB", mE, e_row_size, e_col_size);
	fprintMtrx(fout, (const char*)"mE = mA - mB", mE, e_row_size, e_col_size);
	f_row_size = a_row_size;
	f_col_size = c_col_size;
	k_size = a_col_size;
	mF = multiplyMtrx(mA, mC, f_row_size, k_size, f_col_size); // ����
	printMtrx((const char*)"mF = mA * mC", mF, f_row_size, f_col_size);
	fprintMtrx(fout, (const char*)"mF = mA * mC", mF, f_row_size, f_col_size);
	inv_mF = inverseMtrx(mF, f_row_size); // �����
	printMtrx((const char*)"inv_mF", inv_mF, f_row_size, f_col_size);
	fprintMtrx(fout, (const char*)"inv_mF", inv_mF, f_row_size, f_col_size);
	mI = multiplyMtrx(mF, inv_mF, f_row_size, f_col_size, f_col_size); // ����
	printMtrx((const char*)"mI = mF * inv_mF", mI, f_row_size, f_col_size);
	fprintMtrx(fout, (const char*)"mI = mF * inv_mF", mI, f_row_size, f_col_size);
	fclose(fin_ABC);
	fclose(fout);
}