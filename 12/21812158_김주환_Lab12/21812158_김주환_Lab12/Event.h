/* Event.h */
#ifndef EVENT_H
#define EVENT_H

#include <stdio.h>
#include <Windows.h>

#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5

enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };

extern const char* strEventStatus[];

typedef struct {
	int ev_no;
	int ev_generator;
	int ev_handler;
	int ev_pri; // ev_priority
	LARGE_INTEGER ev_t_gen; // for performance monitoring
	LARGE_INTEGER ev_t_handle; // for performance monitoring
	double elap_time; // for performance monitoring
	EventStatus eventStatus;
} Event;
void printEvent(Event* pEv);
void fprintEvent(FILE* fout, Event* pEv);
Event* genEvent(Event* pEv, int event_Gen_ID, int ev_no, int ev_pri);
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq);
void printEvent_withTime(Event* pEv);
#endif