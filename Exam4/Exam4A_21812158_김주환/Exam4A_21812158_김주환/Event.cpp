/* Event.cpp */
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Event.h"

#define EVENT_PER_LINE 5

extern const char* strEventStatus[];

void printEvent(Event* pEv) {
	char str_pri[6];
	printf("Ev(id:%3d, pri:%2d, gen:%2d, proc:%2d) ", pEv->ev_no, pEv->ev_pri,
		pEv->ev_generator, pEv->ev_handler);
}
void printEvents(Event* L_Ev, int num_Ev) {
	for (int i = 0; i < num_Ev; i++) {
		printEvent(&L_Ev[i]);
		if (((i + 1) % 5) == 0)
			printf("\n ");
	}
}