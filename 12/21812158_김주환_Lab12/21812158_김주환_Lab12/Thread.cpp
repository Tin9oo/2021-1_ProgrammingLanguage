/* Thread_Event Genenerator and Handler.cpp */
#include <Windows.h>
#include <time.h>
#include "Thread.h"
#include "PriorityQueue_Event.h"
#include "Event.h"

void Thread_EventGenerator(ThreadParam_Event* pParam) {
	PriQ_Event* pCirQ_Event = pParam->pPriQ_Event;
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int event_gen_count = 0;
	ThreadStatusMonitor* pThrdMon = pParam->pThrdMon;
	pCirQ_Event = pParam->pPriQ_Event;
	int targetEventGen = pParam->targetEventGen;
	Event* pEv;
	srand(time(NULL));
	for (int round = 0; round < maxRound; round++) {
		if (event_gen_count >= targetEventGen) {
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
			else {
				Sleep(500);
				continue;
			}
		}
		pEv = (Event*)calloc(1, sizeof(Event));
		pEv->ev_generator = myAddr;
		pEv->ev_handler = -1; // event handler is not defined yet !!
		pEv->ev_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr;
		//pEv->ev_pri = eventPriority = rand() % NUM_PRIORITY;
		pEv->ev_pri = targetEventGen - event_gen_count - 1;
		QueryPerformanceCounter(&pEv->ev_t_gen);
		pThrdMon->eventGenerated[pThrdMon->numEventGenerated] = *pEv;
		/*while (enPriQ_Event(pCirQ_Event, *pEv) == NULL) {
			Sleep(500); // 공간이 남아 있으면 인큐
		}*/
		enPriQ_Event(pCirQ_Event, *pEv);
		free(pEv);
		pParam->pMTX_thrd_mon->lock();
		pThrdMon->numEventGenerated++;
		pThrdMon->totalEventGenerated++;
		pParam->pMTX_thrd_mon->unlock();
		event_gen_count++;
		//Sleep(100 + rand() % 300);
		Sleep(10);
	}
}
void Thread_EventHandler(ThreadParam_Event* pParam) {
	Event* pEv, * pEvProc;
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	PriQ_Event* pCirQ_Event = pParam->pPriQ_Event;
	ThreadStatusMonitor* pThrdMon = pParam->pThrdMon;
	int maxRound = pParam->maxRound;
	int targetEventGen = pParam->targetEventGen;
	srand(time(NULL));
	for (int round = 0; round < maxRound; round++) {
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break;
		if ((pEv = dePriQ_Event(pCirQ_Event)) != NULL) {
			//printf("Thread_EventProc::deLL_EventQ_from_HighPri_LL_EventQ : ");
			//printEvent(pEv);
			//printf("\n");
			QueryPerformanceCounter(&pEv->ev_t_handle);
			pParam->pMTX_thrd_mon->lock();
			pEv->ev_handler = myAddr;
			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = *pEv; // 동작 순서 확인
			pThrdMon->numEventProcessed++;
			pThrdMon->totalEventProcessed++;
			pParam->pMTX_thrd_mon->unlock();
		} // 요소가 있으면 디큐
		Sleep(100 + rand() % 300);
	}
}