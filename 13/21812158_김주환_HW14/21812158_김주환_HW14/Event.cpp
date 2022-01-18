/* Event.cpp */
#include <stdio.h>
#include <stdlib.h>
#include "Event.h"

const char* strEventStatus[] = { "GENERATED", "ENQUED", "PROCESSED", "UNDEFINED" };

void printEvent(Event* pEvent) {
	printf("Ev(no:%3d, pri:%2d, gen:%2d. proc:%2d) ", pEvent->event_no, pEvent->event_pri, pEvent->event_gen_addr, pEvent->event_handler_addr);
}
void printEvent_withTime(Event* pEv) {
	printf("Ev(no:%3d, pri:%2d, %6.0lf[ms]) ", pEv->event_no, pEv->event_pri,
		pEv->t_elapsed * 1000);
}
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq) {
	LONGLONG t_diff_LL;
	double t_elapsed;
	t_diff_LL = pEv->t_proc.QuadPart - pEv->t_gen.QuadPart;
	t_elapsed = (double)t_diff_LL / (double)freq.QuadPart;
	pEv->t_elapsed = t_elapsed;
}

/*void printEvent_withGenTime(Event* pEv, LARGE_INTEGER freq) {
	printf("Ev(no:%3d, pri:%2d, %6.0lf[ms]) ", pEv->event_no, pEv->event_pri,
		(double)pEv->t_gen.QuadPart / (double)freq.QuadPart);
}
void printEvent_withProcTime(Event* pEv, LARGE_INTEGER freq) {
	printf("Ev(no:%3d, pri:%2d, %6.0lf[ms]) ", pEv->event_no, pEv->event_pri,
		(double)pEv->t_proc.QuadPart/(double)freq.QuadPart);
}*/