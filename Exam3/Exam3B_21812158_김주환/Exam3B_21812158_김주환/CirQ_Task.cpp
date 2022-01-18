/* CirQ_Task.cpp */
#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "Task.h"

#define TASK_PER_LINE 5

typedef struct
{
	Task* T; // circular queue for events
	int capacity; int front; int end; int num_elements;
} CirQ_Task;

CirQ_Task* initCirQ_Task(CirQ_Task* pCirQ, int capacity) {
	Task* pT;
	pT = (Task*)calloc(capacity, sizeof(Task));
	if (pT == NULL) {
		printf("Error in memory allocation for Event array of size (%d)\n", capacity);
		exit;
	}
	pCirQ->T= pT;
	pCirQ->capacity = capacity;
	pCirQ->front = pCirQ->end = 0;
	pCirQ->num_elements = 0;
	return pCirQ;
}
bool isCirQFull(CirQ_Task* CirQ) {
	if (CirQ->num_elements == CirQ->capacity)
		return true;
	else
		return false;
}
bool isCirQEmpty(CirQ_Task* CirQ) {
	if (CirQ->num_elements == 0)
		return true;
	else
		return false;
}
void printCirQ_Task(CirQ_Task* CirQ) {
	Task tsk;
	int index;
	if ((CirQ == NULL) || (CirQ->T == NULL))
	{
		printf("Error in printArrayQueue: CirQ is NULL or CirQ->array is NULL");
		exit;
	}
	printf(" %2d Elements in CirQ_Event (index_front:%2d) :\n ",
		CirQ->num_elements, CirQ->front);
	if (isCirQEmpty(CirQ))
	{
		printf("CirQ_Event is Empty");
	}
	else
	{
		for (int i = 0; i < CirQ->num_elements; i++)
		{
			index = CirQ->front + i;
			if (index >= CirQ->capacity)
				index = index % CirQ->capacity;
			tsk = CirQ->T[index];
			printTask(&tsk);
			if ((((i + 1) % TASK_PER_LINE) == 0) && ((i + 1) != CirQ->num_elements))
				printf("\n ");
		}
	}
	printf("\n");
}
void fprintCirQ_Task(FILE* fout, CirQ_Task* CirQ) {
	Task tsk;
	int index;
	if ((CirQ == NULL) || (CirQ->T == NULL))
	{
		fprintf(fout, "Error in printArrayQueue: CirQ is NULL or CirQ->array is NULL");
		exit;
	}
	fprintf(fout, " %2d Elements in CirQ_Event (index_front:%2d) :\n ",
		CirQ->num_elements, CirQ->front);
	if (isCirQEmpty(CirQ))
	{
		fprintf(fout, "CirQ_Event is Empty");
	}
	else
	{
		for (int i = 0; i < CirQ->num_elements; i++)
		{
			index = CirQ->front + i;
			if (index >= CirQ->capacity)
				index = index % CirQ->capacity;
			tsk = CirQ->T[index];
			fprintTask(fout, &tsk);
			if ((((i + 1) % TASK_PER_LINE) == 0) && ((i + 1) != CirQ->num_elements))
				fprintf(fout, "\n ");
		}
	}
	fprintf(fout, "\n");
}
Task* enCirQ_Task(CirQ_Task* CirQ, Task ev) {
	if (isCirQFull(CirQ)) {
		return NULL;
	}
	CirQ->T[CirQ->end] = ev;
	CirQ->num_elements++;
	CirQ->end++;
	if (CirQ->end >= CirQ->capacity)
		CirQ->end = CirQ->end % CirQ->capacity;
	return &(CirQ->T[CirQ->end]);
}
Task* deCirQ_Task(CirQ_Task* pCirQ) {
	if (isCirQEmpty(pCirQ))
		return NULL;
	Task* tsk = &(pCirQ->T[pCirQ->front]);
	pCirQ->front++;
	if (pCirQ->front >= pCirQ->capacity)
		pCirQ->front = pCirQ->front % pCirQ->capacity;
	pCirQ->num_elements--;
	return tsk;
}
void delCirQ_Task(CirQ_Task* pCirQ) {
	if (pCirQ->T != NULL)
		free(pCirQ->T);
	pCirQ->T = NULL;
	pCirQ->capacity = 0;
	pCirQ->front = pCirQ->end = 0;
	pCirQ->num_elements = 0;
	free(pCirQ);
}
#endif