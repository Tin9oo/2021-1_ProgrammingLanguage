/* DLL_EvQ.h */
#ifndef DLL_EvQ_H
#define DLL_EvQ_H

#include <Windows.h>
#include <stdio.h>
#include <mutex>
#include "Event.h"

using namespace std;

// doubly linked list node (DLLN)
typedef struct DLLN {
	DLLN* prev;
	DLLN* next;
	Event* pEv;
} DLLN_Ev;
typedef struct {
	char name[50];
	mutex cs_EvQ;
	int priority;
	DLLN_Ev* front;
	DLLN_Ev* back;
	int num_event;
} DLL_EvQ;

void initDLL_EvQ(DLL_EvQ* DLL_EvQ, int priority);
Event* enDLL_EvQ(DLL_EvQ* DLL_EvQ, Event* pEv);
Event* deDLL_EvQ(DLL_EvQ* DLL_EvQ);
void printDLL_EvQ(DLL_EvQ* DLL_EvQ);
#endif