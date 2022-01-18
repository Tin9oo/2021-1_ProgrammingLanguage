// CipherMessage.h
#ifndef CM_H
#define CM_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void atox(unsigned char uc);
void xtoa(unsigned char uc);
void cipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l);
void cipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code);
unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l);
void deCipherText(FILE* fp_tx, FILE* fp_out, unsigned char cipher_code);
#endif