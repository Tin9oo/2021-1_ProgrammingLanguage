/* Event.h */
#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5
enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
extern const char* strEventStatus[];
typedef struct {
	int event_no; int event_gen_addr; int event_handler_addr; int event_pri; // event_priority
	EventStatus eventStatus;
} Event;
void printEvent(Event* pEvt);
void fprintEvent(FILE* fout, Event* pEvent);
void initEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri, int ev_handler_addr, EventStatus ev_status);
Event* genEvent(Event* pEvent, int event_Gen_ID, int event_no, int event_pri);
void printEventArray(Event* pEv, int size, int items_per_line);
#endif