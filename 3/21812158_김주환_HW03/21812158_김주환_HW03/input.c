/*
* ���ϸ� : seeparate.c
* ���� �� �⺻ ���
*	ǥ���Է���ġ���� ���� 1���� �Է¹ް� �� ���ڰ� �빮��, �ҹ���, ����, ����
*   ����, ��ȣ���� ����
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 3�� 22��
*/
#include <stdio.h>

int main_separate(void) {
	char input;

	// �Է�
	printf("Input character : ");
	scanf("%c", &input);

	// �Ǵ�
	if (65 <= input && input <= 90) {
		printf("�빮�� ");
		if (input == 65 || input == 69 || input == 73 || input == 81 || input == 85) {
			printf("����");
		}
		else {
			printf("����");
		}
	}
	else if (97 <= input && input <= 122) {
		printf("�ҹ��� ");
		if (input == 97 || input == 101 || input == 105 || input == 111 || input == 117) {
			printf("����");
		}
		else {
			printf("����");
		}
	}
	else if (48 <= input && input <= 57) {
		printf("����");
	}
	else if (33 <= input && input <= 47 || 58 <= input && input <= 64
		|| 91 <= input && input <= 96
		|| 123 <= input && input <= 126) {
		printf("��ȣ");
	}
	else {
		printf("��/�ҹ���, ����, ��ȣ�� �ƴϴ�");
	}

	return 0;
}