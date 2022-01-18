// hexadecimal.cpp
#ifndef HD_H
#define HD_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <math.h>
#include <stdlib.h>
#include "hexadecimal.h"

#define MAX_HEX_STR_LEN 8

int atox(char* hxdStr) {
	int rst;
	sscanf(hxdStr, "%X", &rst);
	return rst;
}
void xtoa(char* strBuf, int hxd) {
	sprintf(strBuf, "%X", hxd);
}
#endif