/* Event.h */
#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>

#define EVENT_PER_LINE 5

enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
extern const char* strEventStatus[];

typedef struct
{
int ev_no;
int ev_generator;
int ev_handler;
int ev_pri; // ev_priority
EventStatus ev_status;
} Event;

void printEvent(Event * pEv);
void printEvents(Event * L_Ev, int num_Ev);
#endif