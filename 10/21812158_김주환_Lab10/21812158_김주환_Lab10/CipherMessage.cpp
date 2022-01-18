// CipherMessage.cpp
#ifndef CM_H
#define CM_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "CipherMessage.h"

void atox(unsigned char uc) { // 16������ ���ڷ� ��ȯ
	printf("%c", uc);
}
void xtoa(unsigned char uc) { // ���ڸ� 16������ ��ȯ
	unsigned char temp1, temp2;

	temp1 = uc / 16; // ������Ʈ
	temp2 = uc % 16; // ������Ʈ
	printf("%X%X", temp1, temp2);
}
void cipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l) { // ��Ʈ �и�
	*pCC_u = ch / 16;; // ������Ʈ ��ȯ
	*pCC_l = ch % 16; // ������Ʈ ��ȯ
}
void cipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code) {
	int len;
	unsigned char trsf;
	char text[1000] = { '\0' };
	unsigned char rc_u = 0, rc_l = 0;
	unsigned char* pCC_u = &rc_u, * pCC_l = &rc_l;

	while (fgets(text, 1000, fp_msg) != NULL) { // ���ڿ� �ҷ�����
		len = strlen(text); // �ҷ��� ���ڿ� ����
		for (int i = 0; i < len; i++) {
			trsf = text[i] ^ cipher_code; // ��ȣȭ
			xtoa(trsf);
			cipherChar(trsf, pCC_u, pCC_l); // �и�����
			fprintf(fp_tx, "%X%X", rc_u, rc_l);
		}
		fprintf(fp_tx, "\n");
		printf("\n");
	}
}
unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l) { // ��Ʈ ����
	unsigned char rst;
	unsigned char rc_u_2, rc_l_2;
	if (rc_u >= 'A') // 10 ~ 15
		rc_u_2 = rc_u - 'A' + 10;
	else // 0 ~ 9
		rc_u_2 = rc_u - '0';
	if (rc_l >= 'A')
		rc_l_2 = rc_l - 'A' + 10;
	else
		rc_l_2 = rc_l - '0';
	rst = rc_u_2 << 4; // ����
	rst |= rc_l_2;
	return rst;
}
void deCipherText(FILE* fp_tx, FILE* fp_out, unsigned char cipher_code) {
	int len;
	char text[1000] = { '\0' };
	unsigned char trsf;
	unsigned char rc_u, rc_l, rst;

	while (fgets(text, 1000, fp_tx) != NULL) { // ���ڿ� �ҷ�����
		len = strlen(text) - 1; // �ҷ��� ���ڿ� ����
		for (int i = 0; i < len; i += 2) {
			rc_u = text[i]; // ����
			rc_l = text[i + 1]; // ����
			rst = deCipherChar(rc_u, rc_l); // ���հ���
			trsf = rst ^ cipher_code; // ��ȣȭ
			atox(trsf);
			fprintf(fp_out, "%c", trsf);
		}
		printf("\n");
	}
}
#endif