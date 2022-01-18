/* Thread.cpp */
#include <thread>
#include <mutex>
#include "Event.h"
#include "SimParam.h"
#include "PriQ_Ev.h"
#include "Thread.h"

using namespace std;

void Thrd_EvProc(ThrdParam_Ev* pParam) {
	Event* pEv, * pEvProc;
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	PriQ_Ev* pCirQ_Event = pParam->pPriQ_Ev;
	ThrdStatMon* pThrdMon = pParam->pThrdMon;
	int maxRound = pParam->maxRound;
	int targetEventGen = pParam->target_EvGen;
	srand(time(NULL));
	for (int round = 0; round < maxRound; round++) {
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break;
		if ((pEv = dePriQ_Ev(pCirQ_Event)) != NULL) {
			//printf("Thread_EventProc::deLL_EventQ_from_HighPri_LL_EventQ : ");
			//printEvent(pEv);
			//printf("\n");
			QueryPerformanceCounter(&pEv->t_proc);
			pParam->pCS_thrd_mon->lock();
			pEv->ev_handler = myAddr;
			pThrdMon->evPrcd[pThrdMon->total_EvPrcd] = *pEv; // 동작 순서 확인
			pThrdMon->num_EvPrcd[myAddr]++;
			pThrdMon->total_EvPrcd++;
			pParam->pCS_thrd_mon->unlock();
		} // 요소가 있으면 디큐
		Sleep(100 + rand() % 300);
	}
}
void Thrd_EvGen(ThrdParam_Ev* pParam) {
	PriQ_Ev* pCirQ_Event = pParam->pPriQ_Ev;
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int event_gen_count = 0;
	ThrdStatMon* pThrdMon = pParam->pThrdMon;
	pCirQ_Event = pParam->pPriQ_Ev;
	int targetEventGen = pParam->target_EvGen;
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
		QueryPerformanceCounter(&pEv->t_gen);
		pThrdMon->evGent[pThrdMon->num_EvGent[myAddr]] = *pEv;
		/*while (enPriQ_Event(pCirQ_Event, *pEv) == NULL) {
			Sleep(500); // 공간이 남아 있으면 인큐
		}*/
		enPriQ_Ev(pCirQ_Event, pEv);
		free(pEv);
		pParam->pCS_thrd_mon->lock();
		pThrdMon->num_EvGent[myAddr]++;
		pThrdMon->total_EvGent++;
		pParam->pCS_thrd_mon->unlock();
		event_gen_count++;
		//Sleep(100 + rand() % 300);
		Sleep(10);
	}
}