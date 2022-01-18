#ifndef BO
#define BO

#include <stdio.h>

#define GET_BIT(w, k) (((w) >> (k)) & 0x01)

#define num_bits_int 33

enum Operater { BIT_AND = 1, BIT_OR, BIT_XOR, BIT_NOR, SHIFT_LEFT, SHIFT_RIGHT };

void printint_bits(long d);
void printIntOper_Bits(enum Operater bop, int x, int y);
#endif