/* PriQ_Ev.h */
#ifndef P
#define P
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <mutex>
#include "Event.h"

using namespace std;

#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TRUE 1
#define FALSE 0


typedef struct CBTN_Event
{
	int priority;
	Event * pEvent;
} CBTN_Event;

typedef struct PriorityQueue
{
	char PriQ_name[MAX_NAME_LEN];
	int priQ_capacity;
	int priQ_size;
	int pos_last;
	CBTN_Event * pCBT_Event;
	mutex cs_priQ;
} PriQ_Ev;

PriQ_Ev * initPriQ_Ev(PriQ_Ev * pPriQ_Ev, const char* name, int capacity);
Event * enPriQ_Ev(PriQ_Ev * pPriQ_Ev, Event * pEvent);
Event * dePriQ_Ev(PriQ_Ev * pPriQ_Ev);
void printPriQ_Ev(PriQ_Ev * pPriQ_Ev);
void deletePriQ_Ev(PriQ_Ev * pPriQ_Ev);
#endif