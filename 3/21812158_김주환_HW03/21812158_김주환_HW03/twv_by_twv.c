/*
* ���ϸ� : twlv_by_twlv.c
* ���� �� �⺻ ���
*	��ø �ݺ����� ����Ͽ� 12 X 12 ����ǥ�� ����϶�.
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 3�� 22��
*/
#include <stdio.h>

int main(void) {
	printf("> > > 12 X 12 Multiplication Table < < <\n\n");
	
	printf("    |");
	for (int i = 1; i <= 12; i++) { // ���κ� ���
		printf("%5d", i);
	}
	printf("\n");
	printf("====+============================================================\n");

	for (int j = 1; j <= 12; j++) { // 2�� �ݺ����� ����ǥ ���
		printf("%3d |", j);
		for (int k = 1; k <= 12; k++) {
			printf("%5d", j * k);
		}
		printf("\n");
	}

	printf("����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .\n\n");

	return 0;
}