/* PriorityQueue_Event.cpp */
#define _CRT_SECURE_NO_WARNINGS

#include "PriorityQueue_Event.h"
#include "Event.h"

bool hasLeftChild(int pos, PriQ_Event* pPriQ_Event) {
	if (pos * 2 <= pPriQ_Event->priQ_size)
		return TRUE;
	else
		return FALSE;
}
bool hasRightChild(int pos, PriQ_Event* pPriQ_Event) {
	if (pos * 2 + 1 <= pPriQ_Event->priQ_size)
		return TRUE;
	else
		return FALSE;
}
PriQ_Event* initPriQ_Event(PriQ_Event* pPriQ_Event, const char* name, int capacity = 1) {
	pPriQ_Event->cs_PriQ.lock();
	strcpy(pPriQ_Event->PriQ_name, name);
	pPriQ_Event->priQ_capacity = capacity;
	pPriQ_Event->pCBT_Event = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event));
	pPriQ_Event->priQ_size = 0;
	pPriQ_Event->pos_last = 0;
	pPriQ_Event->cs_PriQ.unlock();
	return pPriQ_Event;
}
void deletePriQ_Event(PriQ_Event* pPriQ_Event) {
	pPriQ_Event->cs_PriQ.lock(); if (pPriQ_Event->pCBT_Event != NULL) free(pPriQ_Event->pCBT_Event); pPriQ_Event->cs_PriQ.unlock();
}
Event* enPriQ_Event(PriQ_Event* pPriQ_Event, Event ev) {
	int pos, pos_parent; CBTN_Event CBTN_Ev_tmp;
	pPriQ_Event->cs_PriQ.lock(); // 인큐 중 스위치 되지 않도록 락
	if (pPriQ_Event->priQ_size >= pPriQ_Event->priQ_capacity) {
		// Priority Queue is full /* Expand the capacity twice, and copy the entries */ CBTN_Event *newCBT_Event;
		int newCapacity;
		newCapacity = 2 * pPriQ_Event->priQ_capacity;
		CBTN_Event* newCBT_Event = (CBTN_Event*)calloc((newCapacity + 1), sizeof(CBTN_Event));
		if (newCBT_Event == NULL) {
			printf("Error in expanding CompleteBinaryTree for Priority Queue !!₩n");
			exit(-1);
		}
		for (int pos = 1; pos <= pPriQ_Event->priQ_size; pos++)
			newCBT_Event[pos] = pPriQ_Event->pCBT_Event[pos];
		free(pPriQ_Event->pCBT_Event);
		pPriQ_Event->pCBT_Event = newCBT_Event;
		pPriQ_Event->priQ_capacity = newCapacity;
	} //end - if
	/* insert at the last position */
	pos = ++pPriQ_Event->priQ_size;
	pPriQ_Event->pCBT_Event[pos].priority = ev.ev_pri;
	pPriQ_Event->pCBT_Event[pos].event = ev;
	/* up-heap bubbling */
	while (pos != POS_ROOT) 	{
		pos_parent = pos / 2;
		if (pPriQ_Event->pCBT_Event[pos].priority >= pPriQ_Event->pCBT_Event[pos_parent].priority) {
			break;
			// if the priority of the new packet is lower than its parent's priority, just stop up-heap bubbling
		}
		else {
			CBTN_Ev_tmp = pPriQ_Event->pCBT_Event[pos_parent];
			pPriQ_Event->pCBT_Event[pos_parent] = pPriQ_Event->pCBT_Event[pos];
			pPriQ_Event->pCBT_Event[pos] = CBTN_Ev_tmp;
			pos = pos_parent;
		}
	} // end - while
	pPriQ_Event->cs_PriQ.unlock();
	return &(pPriQ_Event->pCBT_Event[pPriQ_Event->pos_last].event);
}
Event* dePriQ_Event(PriQ_Event* pPriQ_Event) {
	Event* pEv, ev;
	CBTN_Event CBTN_Ev_tmp;
	int pos, pos_root = 1, pos_last, pos_child;
	if (pPriQ_Event->priQ_size <= 0)
		return NULL; // Priority queue is empty
	pPriQ_Event->cs_PriQ.lock(); // 동작 중 스위치 되지 않도록 락
	pEv = (Event*)calloc(1, sizeof(Event));
	*pEv = pPriQ_Event->pCBT_Event[1].event; // get the packet address of current top
	pos_last = pPriQ_Event->priQ_size;
	pPriQ_Event->priQ_size--;
	if (pPriQ_Event->priQ_size > 0) {
		/* put the last node into the top position */
		pPriQ_Event->pCBT_Event[pos_root] = pPriQ_Event->pCBT_Event[pos_last];
		/* down heap bubbling */
		pos = pos_root;
		while (hasLeftChild(pos, pPriQ_Event)) {
			pos_child = pos * 2;
			if (hasRightChild(pos, pPriQ_Event)) {
				if (pPriQ_Event->pCBT_Event[pos_child].priority >
					pPriQ_Event->pCBT_Event[pos_child + 1].priority)
					pos_child = pos * 2 + 1; // if right child has higher priority, then select it
			}
			/* if the Event in pos_child has higher priority than Event in pos, swap them */
			if (pPriQ_Event->pCBT_Event[pos_child].priority >= pPriQ_Event->pCBT_Event[pos].priority)
				break;
			else {
				CBTN_Ev_tmp = pPriQ_Event->pCBT_Event[pos];
				pPriQ_Event->pCBT_Event[pos] = pPriQ_Event->pCBT_Event[pos_child];
				pPriQ_Event->pCBT_Event[pos_child] = CBTN_Ev_tmp;
			}
			pos = pos_child;
		} // end while
	} // end if
	pPriQ_Event->cs_PriQ.unlock();
	return pEv;
}
void printPriQ_Event(PriQ_Event* pPriQ_Event) {
	int pos, count;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;
	if (pPriQ_Event->priQ_size == 0) {
		printf(" PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;
	level = 0;
	level_count = 1; // level_count = 2^^level
	printf("\n CompBinTree :\n", level);
		while (count <= pPriQ_Event->priQ_size)	{
			printf(" level%2d : ", level);
			for (int i = 0; i < level_count; i++) {
				pEv = &(pPriQ_Event->pCBT_Event[pos].event);
				eventPriority = pEv->ev_pri;
				//printf("Event(pri: %2d, id:%2d, src:%2d, dst: %2d) ", eventPriority, pEvent->event_no, pEvent->event_gen_addr, pEvent->event_handler_addr);
	//printf("Event(pri:%2d, src:%2d, id:%3d) ", eventPriority, pEvent->event_gen_addr,	pEvent->event_no);
			printEvent(pEv);
			pos++;
			if ((count % EVENT_PER_LINE) == 0)
				printf("\n ");
					count++;
			if (count > pPriQ_Event->priQ_size)
				break;
			}
			printf("\n");
				level++;
			level_count *= 2;
		} // end - while
	printf("\n");
}