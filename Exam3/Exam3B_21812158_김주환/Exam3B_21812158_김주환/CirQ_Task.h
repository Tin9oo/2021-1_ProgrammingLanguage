/* CirQ_Task.h */
#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H
#include "Task.h"

typedef struct
{
	Task* T; // circular queue for events
	int capacity; int front; int end; int num_elements;
} CirQ_Task;

CirQ_Task * initCirQ_Task(CirQ_Task * pCirQ, int capacity);
Task* enCirQ_Task(CirQ_Task* CirQ, Task ev);
Task* deCirQ_Task(CirQ_Task* pCirQ);
void printCirQ_Task(CirQ_Task * CirQ);
void fprintCirQ_Task(FILE * fout, CirQ_Task * CirQ);
bool isCirQFull(CirQ_Task * CirQ);
bool isCirQEmpty(CirQ_Task * CirQ);
void delCirQ_Task(CirQ_Task * pCirQ);
#endif