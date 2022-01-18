/* Thread.cpp */
#include <Windows.h>
#include <mutex>
#include "CirQ_Ev.h"
#include "SimParam.h"
using namespace std;

enum ROLE {
	EVENT_GENERATOR,
	EVENT_HANDLER
};
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };

typedef struct
{
	int numEvGent;
	int numEvPrcd;
	int total_EvGent;
	int total_EvPrcd;
	Event evGent[TOTAL_NUM_EVENTS]; // used for monitoring only
	Event evPrcd[TOTAL_NUM_EVENTS]; // used for monitoring only
	THREAD_FLAG* pFlagThreadTerminate;
} ThrdStatMon;

typedef struct
{
	mutex* pCS_main;
	mutex* pCS_thrd_mon;
	CirQ_Ev* pCirQ_Ev;
	ROLE role;
	int myAddr;
	int maxRound;
	int target_EvGen;
	ThrdStatMon* pThrdMon;
} ThrdParam_Ev;

void Thrd_EvProc(ThrdParam_Ev* pParam) {
	Event* pEv, * pEvProc;
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	CirQ_Ev* pCirQ_Event = pParam->pCirQ_Ev;
	ThrdStatMon* pThrdMon = pParam->pThrdMon;
	int maxRound = pParam->maxRound;
	int targetEventGen = pParam->target_EvGen;
	srand(time(NULL));
	for (int round = 0; round < maxRound; round++) {
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break;
		if ((pEv = deCirQ_Ev(pCirQ_Event)) != NULL) {
			//printf("Thread_EventProc::deLL_EventQ_from_HighPri_LL_EventQ : ");
			//printEvent(pEv);
			//printf("\n");
			pParam->pCS_thrd_mon->lock();
			pEv->ev_handler = myAddr;
			pThrdMon->evPrcd[pThrdMon->total_EvPrcd] = *pEv; // 동작 순서 확인
			pThrdMon->numEvPrcd++;
			pThrdMon->total_EvPrcd++;
			pParam->pCS_thrd_mon->unlock();
		} // 요소가 있으면 디큐
		Sleep(100 + rand() % 300);
	}
}
void Thrd_EvGen(ThrdParam_Ev* pParam) {
	CirQ_Ev* pCirQ_Event = pParam->pCirQ_Ev;
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int event_gen_count = 0;
	ThrdStatMon* pThrdMon = pParam->pThrdMon;
	pCirQ_Event = pParam->pCirQ_Ev;
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
		pThrdMon->evGent[pThrdMon->numEvGent] = *pEv;
		/*while (enPriQ_Event(pCirQ_Event, *pEv) == NULL) {
			Sleep(500); // 공간이 남아 있으면 인큐
		}*/
		enCirQ_Ev(pCirQ_Event, *pEv);
		free(pEv);
		pParam->pCS_thrd_mon->lock();
		pThrdMon->numEvGent++;
		pThrdMon->total_EvGent++;
		pParam->pCS_thrd_mon->unlock();
		event_gen_count++;
		//Sleep(100 + rand() % 300);
		Sleep(10);
	}
}