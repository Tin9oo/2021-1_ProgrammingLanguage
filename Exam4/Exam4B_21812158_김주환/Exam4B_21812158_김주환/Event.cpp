/* Event.cpp */
#include <stdio.h>
#include <Windows.h>
#include "SimParam.h"
#include "Event.h"

void printEvent(Event* pEvt) {
	char str_pri[6];
	printf("Ev(id:%3d, pri:%2d, gen:%2d, proc:%2d) ", pEvt->ev_no, pEvt->ev_pri,
		pEvt->ev_generator, pEvt->ev_handler);
}
void printEvent_withTime(Event* pEv) {
	char str_pri[6];
	//printf("Ev(no:%3d, pri:%2d, src:%2d, proc:%2d) ", pEv->event_no, pEv->event_pri,
	// pEv->event_gen_addr, pEv->event_handler_addr);
	printf("Ev(no:%2d, pri:%2d, elap_t:%6.0lf[ms]) ", pEv->ev_no, pEv->ev_pri, pEv->t_elapsed * 1000);
}
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq) {
	LONGLONG t_diff;
	t_diff = pEv->t_proc.QuadPart - pEv->t_gen.QuadPart;
	pEv->t_elapsed = (double)t_diff / freq.QuadPart;
}
void printEvents(Event* L_Ev, int num_Ev) {
	for (int i = 0; i < num_Ev; i++) {
		printEvent(&L_Ev[i]);
		if (((i + 1) % 5) == 0)
			printf("\n ");
	}
}
void getStatistics_tElapsed(Event* pEv, int num_Ev, Stat_tElapsed* pStat_tElapsed) {
	/* Analyze the event processing times */
	double min, max, avg, sum;
	int min_ev, max_ev;
	min = max = sum = pEv->t_elapsed;
	min_ev = max_ev = 0;
	for (int i = 1; i < TOTAL_NUM_EVENTS; i++) {
		sum += pEv->t_elapsed;
		if (min > pEv->t_elapsed) {
			min = pEv->t_elapsed;
			min_ev = i;
		}
		if (max < pEv->t_elapsed) {
			max = pEv->t_elapsed;
			max_ev = i;
		}
	}
	avg = sum / TOTAL_NUM_EVENTS;
}