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
#include "CirQ_Ev.h"
#include "Event.h"
using namespace std;

void main()
{
	CirQ_Ev cirQ_Event;
	Event* pEv;
	int myAddr = 0;
	int ev_handler, eventPriority;
	ThrdParam_Ev thrdParam_EvGen, thrdParam_EvProc;
	HANDLE hThrd_EventGenerator, hThrd_EventHandler;
	mutex cs_main; // console display
	mutex cs_thrd_mon; // thread monitoring
	ThrdStatMon thrdMon;
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN;
	int count, numEventGenerated, numEventProcessed;

	initCirQ_Ev(&cirQ_Event, CIR_QUEUE_CAPACITY);

	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.total_EvGent = 0;
	thrdMon.total_EvPrcd = 0;
	/* Create and Activate Thrd_EvProc */
	thrdParam_EvProc.myAddr = 1; // link address

	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.total_EvGent = 0;
	thrdMon.total_EvPrcd = 0;
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++) {
		thrdMon.evPrcd[ev].ev_no = -1; // mark as not-processed
		thrdMon.evPrcd[ev].ev_pri = -1;
	}
	// Thread_EventHandler 생성 및 활성화
	thrdMon.numEvGent = 0;
	thrdParam_EvProc.role = EVENT_HANDLER; // 역할
	thrdParam_EvProc.myAddr = 1; // link address
	thrdParam_EvProc.pCS_main = &cs_main;
	thrdParam_EvProc.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EvProc.pCirQ_Ev = &cirQ_Event;
	thrdParam_EvProc.maxRound = MAX_ROUND;
	thrdParam_EvProc.pThrdMon = &thrdMon;

	thread thrd_ev_handler(Thrd_EvProc, &thrdParam_EvProc);
	cs_main.lock();
	printf("Thrd_EvProc is created and activated ...\n");
	cs_main.unlock();

	/* Create and Activate Thread_EventGen */
	thrdParam_EvGen.myAddr = 0; // my Address
	thrdMon.numEvGent = 0;
	thrdParam_EvGen.role = EVENT_GENERATOR;
	thrdParam_EvGen.myAddr = 0; // my Address
	thrdParam_EvGen.pCS_main = &cs_main;
	thrdParam_EvGen.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EvGen.pCirQ_Ev = &cirQ_Event;
	thrdParam_EvGen.target_EvGen = NUM_EVENTS_PER_GEN;
	thrdParam_EvGen.maxRound = MAX_ROUND;
	thrdParam_EvGen.pThrdMon = &thrdMon;

	thread thrd_ev_generator(Thrd_EvGen, &thrdParam_EvGen);
	cs_main.lock();
	printf("Thread_EventGen is created and activated ...\n");
	cs_main.unlock();

	for (int round = 0; round < MAX_ROUND; round++)
	{
		//cs_main.lock();
		system("cls");
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n",
			round, thrdMon.total_EvGent, thrdMon.total_EvPrcd);
		printf("\n");
		printf("Events generated: \n ");
		printEvents(thrdMon.evGent, thrdMon.total_EvGent);
		printf("Event_Gen generated %2d events\n", thrdMon.total_EvGent);
		printf("Event_Handler processed %2d events\n", thrdMon.total_EvPrcd);
		printf("\n");
		printf("CirQ_Ev::\n"); printCirQ_Ev(&cirQ_Event);
		printf("\n");
		printf("Events processed: \n ");
		printEvents(thrdMon.evPrcd, thrdMon.total_EvPrcd);

		if (thrdMon.total_EvPrcd >= TOTAL_NUM_EVENTS)
		{
			eventThreadFlag = TERMINATE; // set 1 to terminate threads
			break;
		}

		//cs_main.unlock();
		Sleep(100);
	}

	thrd_ev_generator.join();
	cs_main.lock();
	printf("Thrd_EvGen is terminated !!\n");
	cs_main.unlock();

	thrd_ev_handler.join();
	cs_main.lock();
	printf("Thrd_EvProc is terminated !!\n");
	cs_main.unlock();
}