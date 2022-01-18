/* Thread.h */
#ifndef T
#define T
#include <thread>
#include <mutex>
#include "Event.h"
#include "SimParam.h"
#include "PriQ_Ev.h"

using namespace std;
enum ROLE {
	EVENT_GENERATOR,
	EVENT_HANDLER
};
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };

typedef struct
{
	int total_EvGent;
	int total_EvPrcd;
	int num_EvGent[NUM_EVENT_GENERATORS];
	int num_EvPrcd[NUM_EVENT_HANDLERS];
	THREAD_FLAG * pFlagThreadTerminate;
	Event evGent[TOTAL_NUM_EVENTS];
	Event evPrcd[TOTAL_NUM_EVENTS];
} ThrdStatMon;

typedef struct
{
	mutex * pCS_main;
	mutex * pCS_thrd_mon;
	PriQ_Ev * pPriQ_Ev;
	ROLE role;
	int myAddr;
	int maxRound;
	int target_EvGen;
	LARGE_INTEGER PC_freq; // frequency of performance counter
	ThrdStatMon * pThrdMon;
} ThrdParam_Ev;

void Thrd_EvProc(ThrdParam_Ev * pParam);
void Thrd_EvGen(ThrdParam_Ev * pParam);
#endif