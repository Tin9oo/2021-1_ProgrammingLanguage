/* Thread.h */
#include <Windows.h>
#include <thread>
#include <mutex>
#include <process.h>
#include "Event.h"
#include "SimParams.h"
#include "DLL_EvQ.h"
#include "Thread.h"

using namespace std;

void Thrd_EvProc(ThrdParam_Ev* pParam) {
	//int myRole = pParam->role;
	int myProcAddr = pParam->myAddr;
	Event* pEv;
	DLL_EvQ* pEvQ;
	DLL_EvQ* priH_EvQ = pParam->EvQ_PriH;
	DLL_EvQ* priL_EvQ = pParam->EvQ_PriL;
	ThrdStatMon* pThrdMon = pParam->pThrdMon;
	int maxRound = pParam->maxRound;
	Event* evProc = pParam->pThrdMon->evPrcd;
	int targetEventGen = pParam->target_EvGen;
	LARGE_INTEGER PC_freq = pParam->PC_freq; // frequence of performance counter
	pParam->pCS_main->lock();
	printf("Thread_EventHandler(%d): targetEventGen(%d)₩n", myProcAddr, targetEventGen);
	pParam->pCS_main->unlock();
	for (int round = 0; round < maxRound; round++) {
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break;
		while ((pEv = deDLL_EvQ(priH_EvQ)) != NULL) {
			pParam->pCS_thrd_mon->lock();
			pEv->ev_handler = myProcAddr;
			QueryPerformanceCounter(&pEv->t_proc);
			calc_elapsed_time(pEv, PC_freq);
			pThrdMon->evPrcd[pThrdMon->total_EvPrcd] = *pEv;
			pThrdMon->num_EvPrcd_priH[myProcAddr]++;
			pThrdMon->total_EvPrcd++;
			//pThrdMon->num_EvPrcd_priH++;
			free(pEv); // free the memory space for a Packet
			pParam->pCS_thrd_mon->unlock();
			Sleep(300 + rand() % 500);
		} // end while
		if ((pEv = deDLL_EvQ(priL_EvQ)) != NULL) {
			pParam->pCS_thrd_mon->lock();
			pEv->ev_handler = myProcAddr;
			QueryPerformanceCounter(&pEv->t_proc);
			calc_elapsed_time(pEv, PC_freq);
			pThrdMon->evPrcd[pThrdMon->total_EvPrcd] = *pEv;
			pThrdMon->num_EvPrcd_priL[myProcAddr]++;
			pThrdMon->total_EvPrcd++;
			//pThrdMon->num_EvPrcd_priL++;
			free(pEv);
			pParam->pCS_thrd_mon->unlock();
		} // end if
		/*_*/Sleep(100 + rand() % 100);
	} // end while
}
void Thrd_EvGen(ThrdParam_Ev* pParam) {
	Event* pEv;
	int event_no = 0;
	int event_pri = 0;
	int event_gen_count = 0;
	//int myRole = pParam->role;
	int myGenAddr = pParam->myAddr;
	int targetEventGen = pParam->target_EvGen;
	DLL_EvQ* pEvQ;
	DLL_EvQ* priH_EvQ = pParam->EvQ_PriH;
	DLL_EvQ* priL_EvQ = pParam->EvQ_PriL;
	ThrdStatMon* pThrdMon = pParam->pThrdMon;
	int maxRound = pParam->maxRound;
	pParam->pCS_main->lock();
	printf("Thread_EventGenerator(%d): targetEventGen(%d)₩n", myGenAddr, targetEventGen);
	pParam->pCS_main->unlock();
	for (int round = 0; round < maxRound; round++) {
		if (event_gen_count < targetEventGen) {
			pEv = (Event*)calloc(1, sizeof(Event));
			pEv->ev_generator = myGenAddr;
			pEv->ev_no = event_no = event_gen_count + (NUM_EVENTS_PER_GEN * myGenAddr);
			pEv->ev_pri = event_pri = rand() % NUM_PRIORITY;
			pEv->ev_handler = -1;
			QueryPerformanceCounter(&pEv->t_gen);
			pEvQ = (event_pri < PRIORITY_THRESHOLD) ? priH_EvQ : priL_EvQ;
			while (enDLL_EvQ(pEvQ, pEv) == NULL) {
				Sleep(100);
			} // end while
			pParam->pCS_thrd_mon->lock();
			if(event_pri < PRIORITY_THRESHOLD) pThrdMon->num_EvGent_priH[myGenAddr]++;
			else pThrdMon->num_EvGent_priL[myGenAddr]++;
			pThrdMon->evGent[pThrdMon->total_EvGent] = *pEv;
			pThrdMon->total_EvGent++;
			pParam->pCS_thrd_mon->unlock();
			event_gen_count++;
		}
		else {
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
		} // end if
		Sleep(100 + rand() % 100);
	} // end for round
}