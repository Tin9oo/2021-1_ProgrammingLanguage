/* Thread.h */
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
	THREAD_FLAG * pFlagThreadTerminate;
} ThrdStatMon;

typedef struct
{
	mutex * pCS_main;
	mutex * pCS_thrd_mon;
	CirQ_Ev * pCirQ_Ev;
	ROLE role;
	int myAddr;
	int maxRound;
	int target_EvGen;
	ThrdStatMon * pThrdMon;
} ThrdParam_Ev;

void Thrd_EvProc(ThrdParam_Ev * pParam);
void Thrd_EvGen(ThrdParam_Ev * pParam);