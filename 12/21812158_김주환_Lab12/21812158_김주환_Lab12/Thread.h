/* Thread.h */
#ifndef TH
#define TH

#include <mutex>
#include "priorityQueue_Event.h"
#include "SimParams.h"
using namespace std;

enum ROLE {
	EVENT_GENERATOR,
	EVENT_HANDLER
};
enum THREAD_FLAG {
	INITIALIZE, RUN,
	TERMINATE
};
#define THREAD_RETURN_CODE 7
typedef struct
{
	int numEventGenerated;
	int numEventProcessed;
	int totalEventGenerated;
	int totalEventProcessed;
	Event eventGenerated[TOTAL_NUM_EVENTS]; // 생성된 순서대로 저장
	Event eventProcessed[TOTAL_NUM_EVENTS]; // 처리된 순서대로 저장
	THREAD_FLAG* pFlagThreadTerminate;
} ThreadStatusMonitor;
typedef struct
{
	mutex* pMTX_main; // 메인과 동시에 처리할 경우 사용
	mutex* pMTX_thrd_mon; // 스레드 모니터링과 동시에 처리할 경우 사용
	PriQ_Event* pPriQ_Event;
	ROLE role;
	int myAddr;
	int maxRound;
	int targetEventGen;
	ThreadStatusMonitor* pThrdMon;
} ThreadParam_Event;
void Thread_EventHandler(ThreadParam_Event* pParam);
void Thread_EventGenerator(ThreadParam_Event* pParam);
#endif