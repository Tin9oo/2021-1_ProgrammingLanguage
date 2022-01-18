/* CirQ_Ev.cpp */

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

CirQ_Ev* initCirQ_Ev(CirQ_Ev* pCirQ, int capacity) {
	Event* pEv2;
	pEv2 = (Event*)calloc(capacity, sizeof(Event));
	if (pEv2 == NULL) {
		printf("Error in memory allocation for Event array of size (%d)\n", capacity);
		exit;
	}
	pCirQ->CirBuff_Ev = pEv2;
	pCirQ->capacity = capacity;
	pCirQ->front = pCirQ->end = 0;
	pCirQ->num_elements = 0;
	return pCirQ;
}
void printCirQ_Ev(CirQ_Ev* cirQ) {
	int pos, count;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;
	if (cirQ->capacity == 0) {
		printf(" CirQ_Ev is Empty !!\n");
		return;
	}
	pos = 1;
	count = 1;
	level = 0;
	level_count = 1; // level_count = 2^^level
	while (count <= cirQ->capacity) {
		//printf(" level%2d : ", level);
		for (int i = 0; i < EVENT_PER_LINE; i++) {
			pEv = &(cirQ->CirBuff_Ev[pos]);
			eventPriority = pEv->ev_pri;
			//printf("Event(pri: %2d, id:%2d, src:%2d, dst: %2d) ", eventPriority, pEvent->event_no, pEvent->event_gen_addr, pEvent->event_handler_addr);
//printf("Event(pri:%2d, src:%2d, id:%3d) ", eventPriority, pEvent->event_gen_addr,	pEvent->event_no);
			printEvent(pEv);
		
			count++;
			if (count > cirQ->capacity)
				break;
		}
		printf("\n");
	} // end - while
	printf("\n");
}
bool isCirQ_Ev_Full(CirQ_Ev* cirQ) {
	if (cirQ->num_elements == cirQ->capacity)
		return true;
	else
		return false;
}
bool isCirQ_Ev_Empty(CirQ_Ev* cirQ) {
	if (cirQ->num_elements == 0)
		return true;
	else
		return false;
}
Event* enCirQ_Ev(CirQ_Ev* cirQ, Event ev) {
	if (isCirQ_Ev_Full(cirQ)) {
		return NULL;
	}
	cirQ->CirBuff_Ev[cirQ->end] = ev;
	cirQ->num_elements++;
	cirQ->end++;
	if (cirQ->end >= cirQ->capacity)
		cirQ->end = cirQ->end % cirQ->capacity;
	return &(cirQ->CirBuff_Ev[cirQ->end]);
}
Event* deCirQ_Ev(CirQ_Ev* cirQ) {
	if (isCirQ_Ev_Empty(cirQ))
		return NULL;
	Event* pEv = &(cirQ->CirBuff_Ev[cirQ->front]);
	cirQ->front++;
	if (cirQ->front >= cirQ->capacity)
		cirQ->front = cirQ->front % cirQ->capacity;
	cirQ->num_elements--;
	return pEv;
}
void delCirQ_Ev(CirQ_Ev* cirQ) {
	if (cirQ->CirBuff_Ev != NULL)
		free(cirQ->CirBuff_Ev);
	cirQ->CirBuff_Ev = NULL;
	cirQ->capacity = 0;
	cirQ->front = cirQ->end = 0;
	cirQ->num_elements = 0;
	free(cirQ);
}

#endif