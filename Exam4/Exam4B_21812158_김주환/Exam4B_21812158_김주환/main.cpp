/*
* 파일명 : main.cpp
* 목적 및 기본 기능
*
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 6월 16일
*/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mutex>
#include "Thread.h"
#include "PriQ_Ev.h"
#include "Event.h"
#include "SimParam.h"
using namespace std;
void main()
{
	PriQ_Ev priQ_Ev;
	Event * pEvent;
	int myAddr = 0;
	int ev_handler, eventPriority;
	LARGE_INTEGER pc_freq;
	
	initPriQ_Ev(&priQ_Ev, "PriQ_Ev", 1);
	srand(time(NULL));
	ThrdParam_Ev thrdParam_EvGen[NUM_EVENT_GENERATORS],
	thrdParam_EvProc[NUM_EVENT_HANDLERS];
	thread thread_EvProc[NUM_EVENT_HANDLERS];
	thread thread_EvGen[NUM_EVENT_GENERATORS];
	mutex cs_main, cs_thrd_mon;
	ThrdStatMon thrdMon;
	THREAD_FLAG eventThreadFlag = RUN;
	int count, total_EvGent, total_EvPrcd;
	Event evPrcd[TOTAL_NUM_EVENTS];
	
	QueryPerformanceFrequency(&pc_freq);
	
	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.total_EvGent = 0;
	thrdMon.total_EvPrcd = 0;
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++) {
		thrdMon.evPrcd[ev].ev_no = -1; // mark as not-processed
		thrdMon.evPrcd[ev].ev_pri = -1;
	}
	
	/* Create and Activate Thrd_EvProc */
	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)
	{
		thrdMon.num_EvPrcd[p] = 0;
		thrdParam_EvProc[p].myAddr = p; // Event handler address
		thrdParam_EvProc[p].pCS_main = &cs_main;
		thrdParam_EvProc[p].pCS_thrd_mon = &cs_thrd_mon;
		thrdParam_EvProc[p].pPriQ_Ev = &priQ_Ev;
		thrdParam_EvProc[p].maxRound = MAX_ROUND;
		thrdParam_EvProc[p].pThrdMon = &thrdMon;
		thrdParam_EvProc[p].PC_freq = pc_freq;
		thread_EvProc[p] = thread(Thrd_EvProc, &thrdParam_EvProc[p]);
		//cs_main.lock();
		printf("%d-th thread_EventHandler is created and activated (id: %d)\n", p,
		thread_EvProc[p].get_id());
		//cs_main.unlock();
	}
	
	/* Create and Activate Thrd_EvGens */
	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)
	{
		thrdMon.num_EvGent[g] = 0;
		thrdParam_EvGen[g].myAddr = g; // my Address of event generator
		thrdParam_EvGen[g].pCS_main = &cs_main;
		thrdParam_EvGen[g].pCS_thrd_mon = &cs_thrd_mon;
		thrdParam_EvGen[g].pPriQ_Ev = &priQ_Ev;
		thrdParam_EvGen[g].target_EvGen = NUM_EVENTS_PER_GEN;
		thrdParam_EvGen[g].maxRound = MAX_ROUND;
		thrdParam_EvGen[g].pThrdMon = &thrdMon;
		thrdParam_EvGen[g].PC_freq = pc_freq;
		thread_EvGen[g] = thread(Thrd_EvGen, &thrdParam_EvGen[g]);
		//cs_main.lock();
		printf("%d-th thread_EventGen is created and activated (id: %d)\n", g,
		thread_EvGen[g].get_id());
		//cs_main.unlock();
	}
	
	/* Monitoring thread progress in rounds */
	for (int round = 0; round < MAX_ROUND; round++)
	{
		cs_main.lock();
		system("cls");
		printf("Thread monitoring by main() :: round(%2d): \n", round);
		cs_thrd_mon.lock();
		for (int i = 0; i < NUM_EVENT_GENERATORS; i++)
		{
			printf(" Event_Gen[%d] generated %2d events.\n", i,
				thrdMon.num_EvGent[i]);
		}
		printf("Event_Generators have generated total %2d events\n",
			thrdMon.total_EvGent);
		total_EvGent = thrdMon.total_EvPrcd;
		printf("\nGenerated Events (current total %d events)\n ", total_EvGent);
		printEvents(thrdMon.evGent, thrdMon.total_EvGent);
		printf("\nEvent_Handlers have processed total %2d events ",
			thrdMon.total_EvPrcd);
		for (int i = 0; i < NUM_EVENT_HANDLERS; i++)
		{
			printf(" Event_Proc[%d] processed %2d events.\n", i,
				thrdMon.num_EvPrcd[i]);
		}
		
		printf("\n");
		printf("PriQ_Ev (%3d events):\n ", priQ_Ev.priQ_size);
		printf("\n");
		total_EvPrcd = thrdMon.total_EvPrcd;
		printf("Events processed: \n ");
		printEvents(thrdMon.evPrcd, thrdMon.total_EvPrcd);
		cs_thrd_mon.unlock();
		if (total_EvPrcd >= TOTAL_NUM_EVENTS)
		{
			printf("!!! TotalEventProcessed (%d) is reached to target TOTAL_NUM_EVENTS(% d)\n", total_EvPrcd, TOTAL_NUM_EVENTS);
			eventThreadFlag = TERMINATE; // set 1 to terminate threads
			cs_main.unlock();
			break;
		}
		cs_main.unlock();
		Sleep(100);
	} // end for (int round .....)
	
	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)
	{
		thread_EvProc[p].join();
	}
	printf("All threads of event handlers are terminated !!\n");
	
	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)
	{
		thread_EvGen[g].join();
	}
	printf("All threads of event generators are terminated !!\n");
	
	/* get statistics of elapsed times of event processings */
	Stat_tElapsed stat_tElapsed;
	getStatistics_tElapsed(thrdMon.evPrcd, thrdMon.total_EvPrcd, &stat_tElapsed);
	printf("Minimum event processing time: %8.2lf[ms] for ",
		stat_tElapsed.min_tElapsed * 1000);
	printEvent_withTime(&thrdMon.evPrcd[stat_tElapsed.min_tElapsed_Ev]); printf("\n");
	printf("Maximum event processing time: %8.2lf[ms] for ",
		stat_tElapsed.max_tElapsed * 1000);
	printEvent_withTime(&thrdMon.evPrcd[stat_tElapsed.max_tElapsed_Ev]); printf("\n");
	printf("Average event processing time: %8.2lf[ms] for total %d events\n",
		stat_tElapsed.avg_tElapsed * 1000, TOTAL_NUM_EVENTS);
	printf("\n");
}