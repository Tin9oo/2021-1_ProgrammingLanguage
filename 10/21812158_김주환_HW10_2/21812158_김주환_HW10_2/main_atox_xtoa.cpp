/*
* ���ϸ� : main_atox_xtoa.cpp
* ���� �� �⺻ ���
*	ASCII ���ڸ� �Է¹޾� 16������ ��ȯ�ϱ�
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 5�� 17��
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hexadecimal.h"

void main()
{
	char* hexStr;
	char* hexConvertStr;
	unsigned int value_int;
	while (1)
	{
		hexStr = (char*)calloc(MAX_HEX_STR_LEN + 1, sizeof(char));
		hexConvertStr = (char*)calloc(MAX_HEX_STR_LEN + 1, sizeof(char));
		printf("input hexadecimal number : ");
		scanf("%s", hexStr);
		if (strcmp(hexStr, ".") == 0)
			break;
		value_int = atox(hexStr);
		printf("hexadecimal (%s) = %d (decimal)\n", hexStr, value_int);
		xtoa(hexConvertStr, value_int);
		printf("hexadecimal (%s) = %d (decimal) = %#0X (hexadecimal) = re - converted hexadecimal string(% s)\n",
			hexStr, value_int, value_int, hexConvertStr);
	}
}