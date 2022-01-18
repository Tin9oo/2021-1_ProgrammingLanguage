// Telephone_Number.cpp
#ifndef TELEPHONE_NUMBER_H
#define TELEPHONE_NUMBER_H
#include <stdio.h>
#include "Telephone_number.h"
#define U_SHORT unsigned short
typedef struct
{
	U_SHORT nation_code;
	U_SHORT region_no;
	U_SHORT switch_no;
	U_SHORT line_no;
} Tel_Number;
void printTelephoneNumber(Tel_Number telNo) {
	printf("(tel: +%d-", telNo.nation_code);
	printf("%03d-%04d-%04d)", telNo.region_no, telNo.switch_no, telNo.line_no);
}
int compareTelNumber(Tel_Number tn1, Tel_Number tn2)
{
	if (tn1.nation_code > tn2.nation_code)
		return 1;
	else if (tn1.nation_code < tn2.nation_code)
		return -1;
	else if (tn1.region_no > tn2.region_no)
		return 1;
	else if (tn1.region_no < tn2.region_no)
		return -1;
	else if (tn1.switch_no > tn2.switch_no)
		return 1;
	else if (tn1.switch_no < tn2.switch_no)
		return -1;
	else if (tn1.line_no > tn2.line_no)
		return 1;
	else if (tn1.line_no < tn2.line_no)
		return -1;
	else
		return 0;
}
#endif