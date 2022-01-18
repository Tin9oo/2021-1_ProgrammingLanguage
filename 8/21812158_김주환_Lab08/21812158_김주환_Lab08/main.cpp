/*
* ���ϸ� : main.cpp
* ���� �� �⺻ ���
*	2���� ���� �迭�� �����ϰ� ������ ��� �����͸� �˸°� ��/��� �������� Ȯ���ϰ� 
*	�־��� ����� ����, ����, ���� ������ �����Ѵ�.
*	Gauss-Jordan �ҰŹ��� �����ϰ� �̸� �̿��Ͽ� ������� ���ϰ� �̸� �����Ѵ�.
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 4�� 30��
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Mtrx.h"
#include "GaussJordan_LinearSystem.h"

const char* outputFile = "OutputResult.txt";
void test_2D_DynamicArray_FileIO(FILE* fout);
void test_MatrixAdditionSubtraction(FILE* fout);
void test_MatrixMultiplication(FILE* fout);
void test_GaussJordanElimination_LinearSystem(FILE* fout);
void test_InvMtrx_GaussJordanElimination_LinearSystem(FILE* fout);

int main(void) {
	FILE* fin, * fout;
	int menu;
	fout = fopen(outputFile, "w");
	if (fout == NULL) {
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	while (1) {
		printf("Testing Matrix Operations with 2-Dimensional Dynamic Array\n");
		printf(" 1: Test 2-D Dynamic Array Creation for Matrix with File I/O\n");
		printf(" 2: Test Matrix Addition, Subtraction\n");
		printf(" 3: Test Matrix Multiplication\n");
		printf(" 4: Test Gauss-Jordan Elimination for Linear System\n");
		printf(" 5: Test Inverse Matrix with Gauss-Jordan Elimination for Linear System\n");
		printf(" 0: Quit\n");
		printf("Input menu (0 to quit) : ");
		scanf("%d", &menu);
		if (menu == 0)
			break;
		printf("\n");
		switch (menu) {
		case 1:
			test_2D_DynamicArray_FileIO(fout);
			break;
		case 2:
			test_MatrixAdditionSubtraction(fout);
			break;
		case 3:
			test_MatrixMultiplication(fout);
			break;
		case 4:
			test_GaussJordanElimination_LinearSystem(fout);
			break;
		case 5:
			test_InvMtrx_GaussJordanElimination_LinearSystem(fout);
			break;
		default:
			break;
		}
	}
	fclose(fout);
}
// �־��� ��� �����͸� ���Ϸκ��� �а� ���� �۾��� �����Ѵ�.
void test_2D_DynamicArray_FileIO(FILE* fout) {
	const char* matrixDataFile = "mtrx_input.txt";
	FILE* fin;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	double** mA, ** mB;
	fin = fopen(matrixDataFile, "r"); // ���� �б���� ����.
	if (fin == NULL) {
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	mA = fGetMtrx(fin, &a_row_size, &a_col_size);
	printf("Input Matrix_A ( %d x %d) : \n", a_row_size, a_col_size);
	printMtrx(mA, a_row_size, a_col_size);
	printf("\n");
	mB = fGetMtrx(fin, &b_row_size, &b_col_size);
	printf("Input Matrix_B ( %d x %d) : \n", b_row_size, b_col_size);
	printMtrx(mB, b_row_size, b_col_size);
	printf("\n");
	fclose(fin); // ���� �ݱ�
}
// �־��� ����� ����, ���� ������ �����Ѵ�.
void test_MatrixAdditionSubtraction(FILE* fout) {
	const char* matrixDataFile = "mtrx_nxn_input.txt";
	FILE* fin;
	double** mA, ** mB, ** mC, ** mD;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	int c_row_size, c_col_size;
	int d_row_size, d_col_size;

	fin = fopen(matrixDataFile, "r"); // ���� �б���� ����.
	if (fin == NULL) {
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	mA = fGetMtrx(fin, &a_row_size, &a_col_size); // 2���� �迭�� ���� �Ҵ��ϰ� ���Ϸκ��� ���� �ҷ��´�.
	printf("Input Matrix_A ( %d x %d) : \n", a_row_size, a_col_size);
	printMtrx(mA, a_row_size, a_col_size); // �ҷ��� ��� �����͸� ����â�� ����Ѵ�.
	printf("\n");
	mB = fGetMtrx(fin, &b_row_size, &b_col_size);
	printf("Input Matrix_B ( %d x %d) : \n", b_row_size, b_col_size);
	printMtrx(mB, b_row_size, b_col_size);
	printf("\n");
	if ((a_row_size != b_row_size) || (a_col_size != b_col_size)) {
		printf("Error in input matrix dimension: row_size and/or col_size are not equal !!\n");
		fclose(fin);
		return;
	}
	// ����
	c_row_size = a_row_size;
	c_col_size = b_col_size;
	mC = addMatrix(mA, mB, a_row_size, a_col_size);
	printf("Matrix_C (%d x %d) = Matrix_A + Matrix_B : \n", c_row_size, c_col_size);
	printMtrx(mC, c_row_size, c_col_size);
	printf("\n");
	// ����
	d_row_size = a_row_size;
	d_col_size = b_col_size;
	mD = subtractMatrix(mA, mB, a_row_size, a_col_size);
	printf("Matrix_D (%d x %d) = Matrix_A - Matrix_B : \n", d_row_size, d_col_size);
	printMtrx(mD, d_row_size, d_col_size);
	printf("\n");
	// ������ 2���� �迭 ����
	deleteDynMtrx(mA, a_row_size, a_col_size);
	deleteDynMtrx(mB, b_row_size, b_col_size);
	deleteDynMtrx(mC, c_row_size, c_col_size);
	deleteDynMtrx(mD, d_row_size, d_col_size);
	fclose(fin); // ���� �ݱ�
}
// �־��� ��� �������� ���� ������ �����Ѵ�.
void test_MatrixMultiplication(FILE* fout) {
	const char* matrixDataFile = "mtrx_input.txt";
	FILE* fin;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	int c_row_size, c_col_size;
	double** mA, ** mB, ** mC;
	fin = fopen(matrixDataFile, "r"); // ���� �б���� ����.
	if (fin == NULL) {
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	mA = fGetMtrx(fin, &a_row_size, &a_col_size); // 2���� �迭�� �����ϰ� ���Ϸκ��� ��� �����͸� �ҷ��´�.
	printf("Input Matrix_A ( %d x %d) : \n", a_row_size, a_col_size);
	printMtrx(mA, a_row_size, a_col_size); // �ҷ��� ��� �����͸� ����â�� ����Ѵ�.
	printf("\n");
	mB = fGetMtrx(fin, &b_row_size, &b_col_size);
	printf("Input Matrix_B ( %d x %d) : \n", b_row_size, b_col_size);
	printMtrx(mB, b_row_size, b_col_size);
	printf("\n");
	// ����
	c_row_size = a_row_size;
	c_col_size = b_col_size;
	mC = multiplyMatrix(mA, mB, a_row_size, a_col_size, b_col_size);
	printf("Matrix_C (%d x %d) = Matrix_A x Matrix_B : \n", c_row_size, c_col_size);
	printMtrx(mC, c_row_size, c_col_size);
	printf("\n");
	// ������ 2���� ���� �迭�� ����
	deleteDynMtrx(mA, a_row_size, a_col_size);
	deleteDynMtrx(mB, b_row_size, b_col_size);
	deleteDynMtrx(mC, c_row_size, c_col_size);
	fclose(fin); // ���� �ݱ�
}
// Gauss-Jordan �ҰŹ��� �����Ѵ�.
const char* augMatrix_inputFile = "augMtrx.txt";
void test_GaussJordanElimination_LinearSystem(FILE* fout) {
	FILE* fin;
	int size_N, row_size, col_size;
	double* solution;
	double** augMtrx = NULL;
	int i, j, solExist = 1, error = 0;
	double d;
	fin = fopen(augMatrix_inputFile, "r");
	if (fin == NULL) {
		printf("Error in opening input.txt file (%s)!!\n", augMatrix_inputFile);
		exit(-1);
	}
	fscanf(fin, "%d", &size_N);
	augMtrx = createDynamicDoubleMatrix(size_N, size_N + 1); // ÷������� �����Ҵ�
	solution = (double*)calloc(size_N, sizeof(double)); // ���� �迭�� ���� �Ҵ�
	fprintf(fout, "Augmented Matrix size_N : %d\n", size_N);
	//fGetDoubleMatrixData(fin, augMtrx, size_N, size_N + 1);
	getAugmentedMatrixData(fin, augMtrx, size_N); // ÷����� �����͸� ���Ϸκ��� �ҷ��´�.
	fprintf(fout, "Augmented Matrix : \n");
	fprintMtrx(fout, augMtrx, size_N, size_N + 1);
	printf("Augmented Matrix : \n");
	printMtrx(augMtrx, size_N, size_N + 1);
	diagonalize_FileOut(fout, (double**)augMtrx, size_N, &solExist); // �밢ȭ ����
	if (solExist) { // �ذ� ������ ���
		fprintf(fout, "The solution of the given linear system:\n");
		printf("The solution of the given linear system:\n");
		for (i = 0; i < size_N; i++) {
			solution[i] = augMtrx[i][size_N]; // ���� �迭�� ������� ����
			fprintf(fout, " x[%d] : %4f\n", i, solution[i]);
			printf(" x[%d] : %4f\n", i, solution[i]);
		}
	}
	else { // �ذ� �������� ���� ���
		fprintf(fout, "No unique solution\n");
		printf("No unique solution\n");
	}
	// ���� �Ҵ� ����
	for (int i = 0; i < size_N; i++)
		free(augMtrx[i]);
	free(augMtrx);
	free(solution);
	fclose(fin);

}
// ����� ���ϴ� ���� ����
// const char* linearSystem_inputFile = "ElectronicCircuit_A_5x5.txt";
const char* linearSystem_inputFile = "invMtrx.txt";
void test_InvMtrx_GaussJordanElimination_LinearSystem(FILE* fout) {
	FILE* fin;
	double** mA, ** inv_A, ** res, ** mE;
	int size_N;
	double data;
	//fin = fopen("InputData.txt", "r");
	fin = fopen(linearSystem_inputFile, "r"); // ���� �б���� ����
	//fin = fopen("ElectronicCircuit_B_5x5.txt", "r");
	if (fin == NULL) {
		printf("Error in openning %s input file !!\n", linearSystem_inputFile);
		exit(-1);
	}
	fscanf(fin, "%d", &size_N); // ��� ũ�� �ҷ�����
	mA = (double**)calloc(size_N, sizeof(double*));
	inv_A = (double**)calloc(size_N, sizeof(double*));
	mE = (double**)calloc(size_N, sizeof(double*));
	res = (double**)calloc(size_N, sizeof(double*));
	for (int i = 0; i < size_N; i++) {
		mA[i] = (double*)calloc(size_N, sizeof(double));
		mE[i] = (double*)calloc(size_N, sizeof(double));
		inv_A[i] = (double*)calloc(size_N, sizeof(double));
		res[i] = (double*)calloc(size_N, sizeof(double));
	}
	for (int r = 0; r < size_N; r++)
		for (int c = 0; c < size_N; c++) {
			fscanf(fin, "%lf", &data);
			mA[r][c] = data;
		}
	for (int i = 0; i < size_N; i++) {
		fscanf(fin, "%lf", &data);
		mE[i][0] = data;
	}
	fprintf(fout, "Matrix A: \n");
	fprintMtrx(fout, mA, size_N, size_N);
	printf("Matrix A: \n");
	printMtrx(mA, size_N, size_N);
	invMtrxGaussJordanElim_FileOut(fout, mA, inv_A, size_N); // ����� ���ϱ�
	fprintf(fout, " Inverse A: \n");
	fprintMtrx(fout, inv_A, size_N, size_N);
	printf(" Inverse A: \n");
	printMtrx(inv_A, size_N, size_N);
	fprintf(fout, " mE: \n");
	fprintMtrx(fout, mE, size_N, 1);
	printf(" mE: \n");
	printMtrx(mE, size_N, 1);
	res = multiplyMatrix(inv_A, mE, size_N, size_N, 1);
	fprintf(fout, " Res = Inv_A x mE: \n");
	fprintMtrx(fout, res, size_N, 1);
	printf(" Res = Inv_A x mE: \n");
	printMtrx(res, size_N, 1);
	fprintf(fout, "\n");
	
	// ������� �´��� ����
	mA = multiplyMatrix(inv_A, mA, size_N, size_N, size_N);
	printf(" I = Inv_A x mA: \n");
	printMtrx(mA, size_N, size_N);

	// ���� �Ҵ� ����
	for (int i = 0; i < size_N; i++) {
		free(mA[i]); free(mE[i]);
		free(inv_A[i]); free(res[i]);
	}
	free(mA); free(mE);
	free(inv_A); free(res);
	fclose(fin);
}