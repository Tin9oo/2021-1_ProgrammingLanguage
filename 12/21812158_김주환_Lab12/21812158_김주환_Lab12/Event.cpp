/* Event.cpp */
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Event.h"

const char* strEventStatus[] = { "GENERATED", "ENQUED", "PROCESSED", "UNDEFINED" };

void printEvent(Event* pEv) {
	char str_pri[6];
	printf("Ev(id:%3d, pri:%2d, gen:%2d, proc:%2d) ", pEv->ev_no, pEv->ev_pri,
		pEv->ev_generator, pEv->ev_handler);
}
Event* genEvent(Event* pEv, int event_Gen_ID, int ev_no, int ev_pri) {
	pEv = (Event*)calloc(1, sizeof(Event));
	if (pEv == NULL)
		return NULL;
	pEv->ev_generator = event_Gen_ID;
	pEv->ev_handler = -1; // event handler is not defined yet !!
	pEv->ev_no = ev_no;
	//pEv->ev_pri = eventPriority = rand() % NUM_PRIORITY;
	pEv->ev_pri = ev_pri;
	return pEv;
}
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq) {
	LONGLONG t_diff;
	t_diff = pEv->ev_t_handle.QuadPart - pEv->ev_t_gen.QuadPart;
	pEv->elap_time = (double)t_diff / freq.QuadPart;
}
void printEvent_withTime(Event* pEv)
{
	char str_pri[6];
	//printf("Ev(no:%3d, pri:%2d, src:%2d, proc:%2d) ", pEv->event_no, pEv->event_pri,
	// pEv->event_gen_addr, pEv->event_handler_addr);
	printf("Ev(no:%2d, pri:%2d, elap_t:%6.0lf[ms]) ", pEv->ev_no, pEv->ev_pri, pEv->elap_time * 1000);
}