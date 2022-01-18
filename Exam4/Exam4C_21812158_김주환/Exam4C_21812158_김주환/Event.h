/* Event.h */
#ifndef E
#define E
#include <stdio.h>
#include <Windows.h>
#include "SimParams.h"

enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
extern const char* strEventStatus[];

typedef struct
{
	int ev_no;
	int ev_generator;
	int ev_handler;
	int ev_pri; // event_priority
	LARGE_INTEGER t_gen;
	LARGE_INTEGER t_proc;
	double t_elapsed;
	EventStatus ev_status;
} Event;

typedef struct
{
	int min_tElapsed_Ev;
	int max_tElapsed_Ev;
	double min_tElapsed;
	double max_tElapsed;
	double avg_tElapsed;
	
} Stat_tElapsed;

void printEvent(Event * pEvt);
void printEvent_withTime(Event * pEv);
void calc_elapsed_time(Event * pEv, LARGE_INTEGER freq);
void printEvents(Event * L_Ev, int num_Ev);
void getStatistics_tElapsed(Event * pEv, int num_Ev, Stat_tElapsed * pStat_tElapsed);
#endif