#include <stdio.h>

typedef struct {
	char name; // 1
	short id; // 2
	int id_2; // 4
	double gpa; // 8
} type_A;
typedef struct {
	short id; // 2
	char name; // 1
	int id_2; // 4
	double gpa; // 8
} type_B;
typedef struct {
	short id; // 2
	double gpa; // 8
	int id_2; // 4
	char name; // 1
} type_C;
typedef struct {
	short id; // 2
	double gpa; // 8
	int id_2; // 4
} type_C_2;
typedef struct {
	short id; // 2
	double gpa; // 8
} type_C_3;

int main(void) {
	printf("Size of type_A is %d\n", sizeof(type_A));
	printf("Size of type_B is %d\n", sizeof(type_B));
	printf("Size of type_C is %d\n", sizeof(type_C));
	printf("Size of type_C_2 is %d\n", sizeof(type_C_2));
	printf("Size of type_C_3 is %d\n", sizeof(type_C_3));

	return 0;
}