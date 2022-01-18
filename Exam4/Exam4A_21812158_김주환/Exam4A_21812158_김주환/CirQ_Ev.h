/* CirQ_Ev.h */

#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H
#include <mutex>
#include "Event.h"
using namespace std;
typedef struct
{
	Event* CirBuff_Ev; // circular queue for events
	int capacity;
	int front;
	int end;
	int num_elements;
	mutex cs_CirBuf;
} CirQ_Ev;

CirQ_Ev* initCirQ_Ev(CirQ_Ev* pCirQ, int capacity);
void printCirQ_Ev(CirQ_Ev * cirQ);
bool isCirQ_Ev_Full(CirQ_Ev * cirQ);
bool isCirQ_Ev_Empty(CirQ_Ev * cirQ);
Event * enCirQ_Ev(CirQ_Ev * cirQ, Event ev);
Event * deCirQ_Ev(CirQ_Ev * cirQ);
void delCirQ_Ev(CirQ_Ev * cirQ);

#endif