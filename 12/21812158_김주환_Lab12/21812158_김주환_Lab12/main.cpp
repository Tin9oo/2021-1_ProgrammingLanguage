/* main_EventGen_CirQ_EventHandler.cpp */
/*
* 파일명 : main.cpp
* 목적 및 기본 기능
*	Multi-Thread Priority Queue
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 5월 28일
*/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mutex>
#include "Thread.h"
#include "PriorityQueue_Event.h"
#include "Event.h"
#include "ConsoleDisplay.h"
using namespace std;

void main() {
	PriQ_Event priQ_Event;
	Event* pEv;
	int myAddr = 0;
	int ev_handler, eventPriority;
	initPriQ_Event(&priQ_Event, "PriQ_Event", 1);
	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr;
	HANDLE hThrd_EventGenerator, hThrd_EventHandler;
	mutex cs_main; // console display
	mutex cs_thrd_mon; // thread monitoring
	ThreadStatusMonitor thrdMon;
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN;
	int count, numEventGenerated, numEventProcessed;
	LARGE_INTEGER freq;
	consHndlr = initConsoleHandler();

	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0;
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++) {
		thrdMon.eventProcessed[ev].ev_no = -1; // mark as not-processed
		thrdMon.eventProcessed[ev].ev_pri = -1;
	}
	QueryPerformanceFrequency(&freq);
	// Thread_EventHandler 생성 및 활성화
	thrdMon.numEventProcessed = 0;
	thrdParam_EventHndlr.role = EVENT_HANDLER; // 역할
	thrdParam_EventHndlr.myAddr = 1; // link address
	thrdParam_EventHndlr.pMTX_main = &cs_main;
	thrdParam_EventHndlr.pMTX_thrd_mon = &cs_thrd_mon;
	thrdParam_EventHndlr.pPriQ_Event = &priQ_Event;
	thrdParam_EventHndlr.maxRound = MAX_ROUND;
	thrdParam_EventHndlr.pThrdMon = &thrdMon;
	thread thrd_ev_handler(Thread_EventHandler, &thrdParam_EventHndlr);
	cs_main.lock();
	printf("Thread_EventHandler is created and activated ...\n");
	cs_main.unlock();
	// Thread_EventGen 생성 및 활성화
	thrdMon.numEventGenerated = 0;
	thrdParam_EventGen.role = EVENT_GENERATOR;
	thrdParam_EventGen.myAddr = 0; // my Address
	thrdParam_EventGen.pMTX_main = &cs_main;
	thrdParam_EventGen.pMTX_thrd_mon = &cs_thrd_mon;
	thrdParam_EventGen.pPriQ_Event = &priQ_Event;
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN;
	thrdParam_EventGen.maxRound = MAX_ROUND;
	thrdParam_EventGen.pThrdMon = &thrdMon;
	thread thrd_ev_generator(Thread_EventGenerator, &thrdParam_EventGen);
	cs_main.lock();
	printf("Thread_EventGen is created and activated ...\n");
	cs_main.unlock();

	for (int round = 0; round < MAX_ROUND; round++)	{
		//cs_main.lock();
		system("cls"); // 라운드 진행마다 진행 현황 출력을 위해 출력창 초기화
		gotoxy(consHndlr, 0, 0); // 커서 초기화
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n",
			round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);
		printf("\n");
		printf("Events generated: \n ");
		count = 0;
		numEventGenerated = thrdMon.totalEventGenerated;
		for (int i = 0; i < numEventGenerated; i++)	{
			pEv = &thrdMon.eventGenerated[i];
			if (pEv != NULL) {
				printEvent(pEv);
				if (((i + 1) % EVENT_PER_LINE) == 0)
					printf("\n ");
			}
		}
		printf("\n");
		printf("Event_Gen generated %2d events\n", thrdMon.numEventGenerated);
		printf("Event_Handler processed %2d events\n", thrdMon.numEventProcessed);
		printf("\n");
		printf("PriQ_Event::"); printPriQ_Event(&priQ_Event);
		printf("\n");
		printf("Events processed: \n ");
		count = 0;
		numEventProcessed = thrdMon.totalEventProcessed;
		for (int i = 0; i < numEventProcessed; i++)	{
			pEv = &thrdMon.eventProcessed[i];
			if (pEv != NULL) {
				calc_elapsed_time(pEv, freq);
				printEvent_withTime(pEv);
				if (((i + 1) % EVENT_PER_LINE) == 0)
					printf("\n ");
			}
		}
		printf("\n");
		if (numEventProcessed >= TOTAL_NUM_EVENTS) {
			eventThreadFlag = TERMINATE; // set 2 to terminate threads
			break;
		}

		//cs_main.unlock();
		Sleep(100); // 컨텍스트 스위치
	}

	/* Analyze the event processing times */
	double min, max, avg, sum;
	int min_ev, max_ev;
	min = max = sum = thrdMon.eventProcessed[0].elap_time;
	min_ev = max_ev = 0;
	for (int i = 1; i < TOTAL_NUM_EVENTS; i++) {
		sum += thrdMon.eventProcessed[i].elap_time;
		if (min > thrdMon.eventProcessed[i].elap_time) {
			min = thrdMon.eventProcessed[i].elap_time;
			min_ev = i;
		}
		if (max < thrdMon.eventProcessed[i].elap_time) {
			max = thrdMon.eventProcessed[i].elap_time;
			max_ev = i;
		}
	}
	avg = sum / TOTAL_NUM_EVENTS;
	printf("Minimum event processing time: %8.2lf[ms] for ", min * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[min_ev]); printf("\n");
	printf("Maximum event processing time: %8.2lf[ms] for ", max * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[max_ev]); printf("\n");
	printf("Average event processing time: %8.2lf[ms] for total %d events\n", avg * 1000,
		TOTAL_NUM_EVENTS);
	printf("\n");
	thrd_ev_generator.join(); // 종료까지 기다림
	printf("Thread_EventGenerator is terminated !!\n");
	thrd_ev_handler.join(); // 종료까지 기다림
	printf("Thread_EventHandler is terminated !!\n");
}