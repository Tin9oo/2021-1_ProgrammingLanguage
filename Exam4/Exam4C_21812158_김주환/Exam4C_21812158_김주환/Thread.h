/* Thread.h */
#ifndef T
#define T
#include <Windows.h>
#include <thread>
#include <mutex>
#include <process.h>
#include "Event.h"
#include "SimParams.h"
#include "DLL_EvQ.h"

using namespace std;

enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };

typedef struct
{
	int total_EvGent;
	int total_EvGent_priH;
	int total_EvGent_priL;
	int total_EvPrcd;
	int total_EvPrcd_priH;
	int total_EvPrcd_priL;
	int num_EvGent_priH[NUM_EVENT_GENERATORS];
	int num_EvGent_priL[NUM_EVENT_GENERATORS];
	int num_EvPrcd_priH[NUM_EVENT_HANDLERS];
	int num_EvPrcd_priL[NUM_EVENT_HANDLERS];
	THREAD_FLAG * pFlagThreadTerminate;
	Event evGent[TOTAL_NUM_EVENTS];
	Event evPrcd[TOTAL_NUM_EVENTS];
} ThrdStatMon;
typedef struct
{
	mutex * pCS_main;
	mutex * pCS_thrd_mon;
	DLL_EvQ * EvQ_PriH;
	DLL_EvQ * EvQ_PriL;
	int myAddr;
	int maxRound;
	int target_EvGen;
	LARGE_INTEGER PC_freq; // frequency of performance counter
	ThrdStatMon * pThrdMon;
} ThrdParam_Ev;

void Thrd_EvProc(ThrdParam_Ev * pParam);
void Thrd_EvGen(ThrdParam_Ev * pParam);
#endif