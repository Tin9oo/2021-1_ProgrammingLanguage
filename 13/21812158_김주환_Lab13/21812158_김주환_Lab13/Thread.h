/* Thread.h */
#ifndef THREAD_H
#define THREAD_H

#include <Windows.h>
#include <thread>
#include <mutex>
#include <process.h>
#include "Event.h"
#include "SimParams.h"
#include "DLL_EvQ.h"

using namespace std;

enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };

typedef struct {
	int eventsGen[NUM_EVENT_GENERATORS];
	int eventsProc[NUM_EVENT_HANDLERS];
	int totalEventGen;
	int totalEventProc;
	int numEventProcs_priH;
	int numEventProcs_priL;
	THREAD_FLAG* pFlagThreadTerminate;
	Event eventGenerated[TOTAL_NUM_EVENTS];
	Event eventProcessed[TOTAL_NUM_EVENTS];
} ThreadStatMon;
typedef struct {
	FILE* fout;
	mutex* pCS_main;
	mutex* pCS_thrd_mon;
	DLL_EvQ* EvQ_PriH;
	DLL_EvQ* EvQ_PriL;
	ROLE role;
	int myAddr;
	int maxRound;
	int targetEventGen;
	LARGE_INTEGER PC_freq;
	// frequency of performance counter that is used
	// to measure elapsed time
	ThreadStatMon* pThrdMon;
} ThreadParam_Ev;

void Thread_EventHandler(ThreadParam_Ev* pParam);
void Thread_EventGenerator(ThreadParam_Ev* pParam);
#endif