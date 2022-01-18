// hexadecimal.h
#ifndef HD_H
#define HD_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include<math.h>
#include <stdlib.h>

#define MAX_HEX_STR_LEN 8

int atox(char* hxdStr);
void xtoa(char* strBuf, int hxd);
#endif