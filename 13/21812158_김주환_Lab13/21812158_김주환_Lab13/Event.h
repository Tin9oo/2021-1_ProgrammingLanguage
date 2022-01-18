/* Event.h */
#ifndef EVENT_H
#define EVENT_H

#include <stdio.h>
#include <Windows.h>
#include "ConsoleDisplay.h"
#include "SimParams.h"

#define NUM_PRIORITY 10
#define PRIORITY_THRESHOLD 3
#define EVENT_PER_LINE 5

enum EventStatus {
	GENERATED, ENQUEUED,
	PROCESSED, UNDEFINED
};

extern const char* strEventStatus[];

typedef struct {
	int event_no;
	int event_gen_addr;
	int event_handler_addr;
	int event_pri; // event_priority
	LARGE_INTEGER t_gen;
	LARGE_INTEGER t_proc;
	double t_elapsed;
	EventStatus eventStatus;
} Event;

void printEvent(Event* pEvt);
void printEvent_withTime(Event* pEv);
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq);

/*void printEvent_withGenTime(Event* pEv, LARGE_INTEGER freq);
void printEvent_withProcTime(Event* pEv, LARGE_INTEGER freq);*/
#endif