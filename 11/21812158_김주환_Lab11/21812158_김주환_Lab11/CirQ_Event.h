/* CirQ_Event.h */
#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H
#include "Event.h"
typedef struct
{
	Event* pEv; // circular queue for events
	int capacity; int front; int end; int num_elements;
} CirQ_Event;
CirQ_Event* initCirQ(CirQ_Event* pCirQ, int capacity);
bool isCirQEmpty(CirQ_Event* pCirQ);
// void printCirQ(CirQ_Event* cirQ);
void fprintCirQ(FILE* fout, CirQ_Event* pCirQ);
bool isCirQFull(CirQ_Event* pCirQ);
Event* enCirQ(FILE* fout, CirQ_Event* pCirQ, Event ev);
Event* deCirQ(FILE* fout, CirQ_Event* pCirQ);
void delCirQ(CirQ_Event* pCirQ);

int expand_CirQ(CirQ_Event* array, int curS, int newS);
#endif