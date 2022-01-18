/* Thread.cpp */
#include <Windows.h>
#include <time.h>
#include <thread>
#include <mutex>
#include "Thread.h"
#include "DLL_EvQ.h"
#include "Event.h"
#include "SimParams.h"

using namespace std;

void Thread_EventGenerator(ThreadParam_Ev* pThrdParam) {
	Event* pEv;
	int event_no = 0;
	int event_pri = 0;
	int event_gen_count = 0;
	int myRole = pThrdParam->role;
	int myGenAddr = pThrdParam->myAddr;
	int targetEventGen = pThrdParam->targetEventGen;
	DLL_EvQ* pEvQ;
	DLL_EvQ* priH_EvQ = pThrdParam->EvQ_PriH;
	DLL_EvQ* priL_EvQ = pThrdParam->EvQ_PriL;
	ThreadStatMon* pThrdMon = pThrdParam->pThrdMon;
	int maxRound = pThrdParam->maxRound;
	pThrdParam->pCS_main->lock();
	printf("Thread_EventGenerator(%d): targetEventGen(%d)₩n", myGenAddr, targetEventGen);
	pThrdParam->pCS_main->unlock();
	for (int round = 0; round < maxRound; round++) {
		if (event_gen_count < targetEventGen) {
			pEv = (Event*)calloc(1, sizeof(Event));
			pEv->event_gen_addr = myGenAddr;
			pEv->event_no = event_no = event_gen_count + (NUM_EVENTS_PER_GEN * myGenAddr);
			pEv->event_pri = event_pri = rand() % NUM_PRIORITY;
			pEv->event_handler_addr = -1;
			QueryPerformanceCounter(&pEv->t_gen);
			pEvQ = (event_pri < PRIORITY_THRESHOLD) ? priH_EvQ : priL_EvQ;
			while (enDLL_EvQ(pEvQ, pEv) == NULL) {
				Sleep(100);
			} // end while
			pThrdParam->pCS_thrd_mon->lock();
			pThrdMon->eventsGen[myGenAddr]++;
			pThrdMon->eventGenerated[pThrdMon->totalEventGen] = *pEv;
			pThrdMon->totalEventGen++;
			pThrdParam->pCS_thrd_mon->unlock();
			event_gen_count++;
		}
		else {
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
		} // end if
		Sleep(100 + rand() % 100);
	} // end for round
}
void Thread_EventHandler(ThreadParam_Ev* pThrdParam) {
	int myRole = pThrdParam->role;
	int myProcAddr = pThrdParam->myAddr;
	Event* pEv;
	DLL_EvQ* pEvQ;
	DLL_EvQ* priH_EvQ = pThrdParam->EvQ_PriH;
	DLL_EvQ* priL_EvQ = pThrdParam->EvQ_PriL;
	ThreadStatMon* pThrdMon = pThrdParam->pThrdMon;
	int maxRound = pThrdParam->maxRound;
	Event* evProc = pThrdParam->pThrdMon->eventProcessed;
	int targetEventGen = pThrdParam->targetEventGen;
	LARGE_INTEGER PC_freq = pThrdParam->PC_freq; // frequence of performance counter
	pThrdParam->pCS_main->lock();
	printf("Thread_EventHandler(%d): targetEventGen(%d)₩n", myProcAddr, targetEventGen);
	pThrdParam->pCS_main->unlock();
	for (int round = 0; round < maxRound; round++) {
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break;
		while ((pEv = deDLL_EvQ(priH_EvQ)) != NULL) {
			pThrdParam->pCS_thrd_mon->lock();
			pEv->event_handler_addr = myProcAddr;
			QueryPerformanceCounter(&pEv->t_proc);
			calc_elapsed_time(pEv, PC_freq);
			pThrdMon->eventProcessed[pThrdMon->totalEventProc] = *pEv;
			pThrdMon->eventsProc[myProcAddr]++;
			pThrdMon->totalEventProc++;
			pThrdMon->numEventProcs_priH++;
			free(pEv); // free the memory space for a Packet
			pThrdParam->pCS_thrd_mon->unlock();
			Sleep(300 + rand() % 500);
		} // end while
		if ((pEv = deDLL_EvQ(priL_EvQ)) != NULL) {
			pThrdParam->pCS_thrd_mon->lock();
			pEv->event_handler_addr = myProcAddr;
			QueryPerformanceCounter(&pEv->t_proc);
			calc_elapsed_time(pEv, PC_freq);
			pThrdMon->eventProcessed[pThrdMon->totalEventProc] = *pEv;
			pThrdMon->eventsProc[myProcAddr]++;
			pThrdMon->totalEventProc++;
			pThrdMon->numEventProcs_priL++;
			free(pEv);
			pThrdParam->pCS_thrd_mon->unlock();
		} // end if
		/*_*/Sleep(100 + rand() % 100);
	} // end while
}