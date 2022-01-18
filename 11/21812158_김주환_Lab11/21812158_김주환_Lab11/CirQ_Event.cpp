/* CirQ_Event.cpp */
#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "CirQ_Event.h"
#include "Event.h"

typedef struct {
	Event* pEv; // circular queue for events
				// 버퍼
	int capacity;
	int front; // 맨 처음 누가 서비스를 받을 것인가
	int end; // 어디 집어넣을지
	int num_elements;
} CirQ_Event;
CirQ_Event* initCirQ(CirQ_Event* pCirQ, int capacity) {
	Event* pEv2;
	pEv2 = (Event*)calloc(capacity, sizeof(Event));
	if (pEv2 == NULL) {
		printf("Error in memory allocation for Event array of size (%d)\n", capacity);
		exit;
	}
	pCirQ->pEv = pEv2;
	pCirQ->capacity = capacity;
	pCirQ->front = pCirQ->end = 0;
	pCirQ->num_elements = 0;
	return pCirQ;

}
bool isCirQEmpty(CirQ_Event* pCirQ) {
	if (pCirQ->num_elements == 0)
		return true;
	else
		return false;
}
/* void printCirQ(CirQ_Event* cirQ) {} */
void fprintCirQ(FILE* fout, CirQ_Event* pCirQ) {
	Event ev;
	int index;
	if ((pCirQ == NULL) || (pCirQ->pEv == NULL))
	{
		printf("Error in printArrayQueue: pCirQ is NULL or pCirQ->array is NULL");
		exit;
	}
	fprintf(fout, " %2d Elements in CirQ_Event (index_front:%2d) :\n ",
		pCirQ->num_elements, pCirQ->front);
	if (isCirQEmpty(pCirQ))
	{
		fprintf(fout, "pCirQ_Event is Empty");
	}
	else
	{
		for (int i = 0; i < pCirQ->num_elements; i++)
		{
			index = pCirQ->front + i;
			if (index >= pCirQ->capacity)
				index = index % pCirQ->capacity;
			ev = pCirQ->pEv[index];
			fprintEvent(fout, &ev);
			if ((((i + 1) % EVENT_PER_LINE) == 0) && ((i + 1) != pCirQ->num_elements))
				fprintf(fout, "\n ");
		}
	}
	fprintf(fout, "\n");
}
bool isCirQFull(CirQ_Event* pCirQ) {
	if (pCirQ->num_elements == pCirQ->capacity)
		return true;
	else
		return false;
}
Event* enCirQ(FILE* fout, CirQ_Event* pCirQ, Event ev) { // 집어넣기
	if (isCirQFull(pCirQ)) {
		return NULL;
	}
	pCirQ->pEv[pCirQ->end] = ev;
	pCirQ->num_elements++;
	pCirQ->end++;
	if (pCirQ->end >= pCirQ->capacity)
		pCirQ->end = pCirQ->end % pCirQ->capacity;
	return &(pCirQ->pEv[pCirQ->end]);
}
Event* deCirQ(FILE* fout, CirQ_Event* pCirQ) { // 뽑아내기
	if (isCirQEmpty(pCirQ))
		return NULL;
	Event* pEv = &(pCirQ->pEv[pCirQ->front]);
	pCirQ->front++;
	if (pCirQ->front >= pCirQ->capacity)
		pCirQ->front = pCirQ->front % pCirQ->capacity;
	pCirQ->num_elements--;
	return pEv;
}
void delCirQ(CirQ_Event* pCirQ) { // 메모리 배열 반납
	if (pCirQ->pEv != NULL)
		free(pCirQ->pEv);
	pCirQ->pEv = NULL;
	pCirQ->capacity = 0;
	pCirQ->front = pCirQ->end = 0;
	pCirQ->num_elements = 0;
	free(pCirQ);
}

int expand_CirQ(CirQ_Event* A, int curS, int newS) {
	Event* newA;
	Event* empty_sp = (Event*)calloc(1, sizeof(Event));

	newA = (Event*)realloc(A->pEv, sizeof(Event) * newS);
	for (int i = curS; i < newS; i++)
		newA[i] = *empty_sp;
	return newS;
}
#endif