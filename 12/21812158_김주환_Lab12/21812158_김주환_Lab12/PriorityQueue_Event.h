/* PriorityQueue_Event.h */
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mutex>
#include "Event.h"

#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TRUE 1
#define FALSE 0

using namespace std;

typedef struct CBTN_Event {
	int priority;
	Event event;
} CBTN_Event;
typedef struct PriorityQueue {
	char PriQ_name[MAX_NAME_LEN];
	int priQ_capacity;
	int priQ_size;
	int pos_last;
	CBTN_Event* pCBT_Event;
	mutex cs_PriQ;
} PriQ_Event;
PriQ_Event* initPriQ_Event(PriQ_Event* pPriQ_Event, const char* name, int capacity);
Event* enPriQ_Event(PriQ_Event* pPriQ_Event, Event ev);
Event* dePriQ_Event(PriQ_Event* pPriQ_Event);
void printPriQ_Event(PriQ_Event* pPriQ_Event);
void fprintPriQ_Event(FILE* fout, PriQ_Event* pPriQ_Event);
void deletePriQ_Event(PriQ_Event* pPriQ_Event);
#endif