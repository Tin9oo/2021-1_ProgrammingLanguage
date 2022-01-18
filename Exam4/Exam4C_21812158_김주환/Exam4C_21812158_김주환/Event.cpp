/* Event.cpp */
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Event.h"
#include "SimParams.h"

extern const char* strEventStatus[];


void printEvent(Event* pEvt) {
	printf("Ev(no:%3d, pri:%2d, gen:%2d. proc:%2d) ",
		pEvt->ev_no, pEvt->ev_pri, pEvt->ev_generator, pEvt->ev_handler);
}
void printEvent_withTime(Event* pEv) {
	printf("Ev(no:%3d, pri:%2d, %6.0lf[ms]) ", pEv->ev_no, pEv->ev_pri,
		pEv->t_elapsed * 1000);
}
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq) {
	LONGLONG t_diff_LL;
	double t_elapsed;
	t_diff_LL = pEv->t_proc.QuadPart - pEv->t_gen.QuadPart;
	t_elapsed = (double)t_diff_LL / (double)freq.QuadPart;
	pEv->t_elapsed = t_elapsed;
}
void printEvents(Event* L_Ev, int num_Ev) {
	for (int i = 0; i < num_Ev; i++) {
		printEvent(&L_Ev[i]);
		if (((i + 1) % 5) == 0)
			printf("\n ");
	}
}
void getStatistics_tElapsed(Event* pEv, int num_Ev, Stat_tElapsed* pStat_tElapsed) {
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