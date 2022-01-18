/*
* 파일명 : main.cpp
* 목적 및 기본 기능
*	이중 연결형 리스트 구현 멀티스레드 실행
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 6월 16일
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <thread>
#include <mutex>
#include "Thread.h"
#include "DLL_EvQ.h"
#include "Event.h"

using namespace std;

void main()
{
	DLL_EvQ dll_EvQ_PriH, dll_EvQ_PriL;
	Event * pEvent;
	int myAddr = 0;
	int ev_handler, eventPriority;
	LARGE_INTEGER pc_freq;
	
	initDLL_EvQ(&dll_EvQ_PriH, 0);
	initDLL_EvQ(&dll_EvQ_PriL, 1);
	srand(time(NULL));
	ThrdParam_Ev thrdParam_EvGen[NUM_EVENT_GENERATORS];
	ThrdParam_Ev thrdParam_EvProc[NUM_EVENT_HANDLERS];
	thread thrd_EvProc[NUM_EVENT_HANDLERS];
	thread thrd_EvGen[NUM_EVENT_GENERATORS];
	mutex cs_main, cs_thrd_mon;
	ThrdStatMon thrdMon;
	THREAD_FLAG eventThreadFlag = RUN;
	
	 QueryPerformanceFrequency(&pc_freq);
	
	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.total_EvGent = 0;
	thrdMon.total_EvGent_priH = 0;
	thrdMon.total_EvGent_priL = 0;
	thrdMon.total_EvPrcd = 0;
	thrdMon.total_EvPrcd_priH = 0;
	thrdMon.total_EvPrcd_priL = 0;
	
	/* Create and Activate Thrd_EvProc */
	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)
	{
		thrdMon.num_EvPrcd_priH[p] = 0;
		thrdMon.num_EvPrcd_priL[p] = 0;
		thrdParam_EvProc[p].myAddr = p; // Event handler address
		// . . . . // thrdParam_EvProc[p] 속성 추가 설정
		
		
		thrd_EvProc[p] = thread(Thrd_EvProc, &thrdParam_EvProc[p]);
		//cs_main.lock();
		printf("%d-th thread_EventHandler is created and activated (id: %d)\n", p,
			thrd_EvProc[p].get_id());
		//cs_main.unlock();
	}
	
	/* Create and Activate Thrd_EvGens */
	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)
	{
		thrdMon.num_EvGent_priH[g] = 0;
		thrdMon.num_EvGent_priL[g] = 0;
		thrdParam_EvGen[g].myAddr = g; // my Address of event generator
		//. . . . // thrdParam_EvGen[g] 속성 추가 설정
		
		thrd_EvGen[g] = thread(Thrd_EvGen, &thrdParam_EvGen[g]);
		//cs_main.lock();
		printf("%d-th thread_EventGen is created and activated (id: %d)\n", g,
			thrd_EvGen[g].get_id());
		//cs_main.unlock();
	}
	
	/* Monitoring thread progress in rounds */
	for (int round = 0; round < MAX_ROUND; round++)
	{
		cs_main.lock();
		system("cls");
		//gotoxy(consHndlr, 0, 0);
		printf("Thread monitoring by main() :: round(%2d): \n", round);
		cs_thrd_mon.lock();
		for (int i = 0; i < NUM_EVENT_GENERATORS; i++)
		{
			printf(" Event_Gen[%d] generated %2d PriH events and %2d PriL events.\n",
				i, thrdMon.num_EvGent_priH[i], thrdMon.num_EvGent_priL[i]);
		}
		
		printf("Event_Generators have generated total %2d events (PriH: %d, PriL: % d)\n",
			thrdMon.total_EvGent, thrdMon.total_EvGent_priH,
		thrdMon.total_EvGent_priL);
		printf("\nGenerated Events (current total %d events)\n ",
				thrdMon.total_EvGent);
		printEvents(thrdMon.evGent, thrdMon.total_EvGent);
		
		printf("\nEvent_Handlers have processed total %2d events ",
				thrdMon.total_EvPrcd);
		printf("(ev__PriH (%2d), ev_PriL (%2d))\n", thrdMon.total_EvPrcd_priH,
			thrdMon.total_EvPrcd_priL);
		for (int i = 0; i < NUM_EVENT_HANDLERS; i++)
		{
			printf(" Event_Proc[%d] processed %2d PriH events and %2d PriL events.\n",
				i, thrdMon.num_EvPrcd_priH[i], thrdMon.num_EvPrcd_priL[i]);
		}
		
		printf("\nDLL_EvQ_PriH (%3d events):\n ", dll_EvQ_PriH.num_event);
		printDLL_EvQ(&dll_EvQ_PriH); printf("\n");
		printf("DLL_EvQ_PriL (%3d events):\n ", dll_EvQ_PriL.num_event);
		printDLL_EvQ(&dll_EvQ_PriL); printf("\n");
		
		printf("Events processed: \n ");
		printEvents(thrdMon.evPrcd, thrdMon.total_EvPrcd);
		cs_thrd_mon.unlock();
		if (thrdMon.total_EvPrcd >= TOTAL_NUM_EVENTS)
		{
			printf("!!! TotalEventProcessed (%d) is reached to target TOTAL_NUM_EVENTS(% d)\n",
				thrdMon.total_EvPrcd, TOTAL_NUM_EVENTS);
			eventThreadFlag = TERMINATE; // set 1 to terminate threads
			cs_main.unlock();
			break;
		}
		cs_main.unlock();
		Sleep(100);
	} // end for (int round .....)
	
	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)
	{
		thrd_EvProc[p].join();
	}
	printf("All threads of event handlers are terminated !!\n");
	
	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)
	{
		thrd_EvGen[g].join();
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