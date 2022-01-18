/* DLL_EvQ.h */
#ifndef D
#define D
#include <Windows.h>
#include <stdio.h>
#include <mutex>
#include "Event.h"

using namespace std;

// doubly linked list node (DLLN)
typedef struct DLLN
{
	struct DLLN* next;
	struct DLLN* prev;
	Event * pEv;
} DLLN_Ev;

typedef struct
{
	mutex cs_EvQ;
	int priority;
	DLLN_Ev* front;
	DLLN_Ev* back;
	int num_event;
} DLL_EvQ;

void initDLL_EvQ(DLL_EvQ * DLL_EvQ, int priority);
Event * enDLL_EvQ(DLL_EvQ * DLL_EvQ, Event * pEv);
Event * deDLL_EvQ(DLL_EvQ * DLL_EvQ);
void printDLL_EvQ(DLL_EvQ * DLL_EvQ);
#endif