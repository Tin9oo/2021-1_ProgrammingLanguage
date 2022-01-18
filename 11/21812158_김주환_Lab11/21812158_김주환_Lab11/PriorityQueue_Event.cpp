/* PriorityQueue_Event.cpp */
#define _CRT_SECURE_NO_WARNINGS

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PriorityQueue_Event.h"
#include "Event.h"

#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TRUE 1
#define FALSE 0

typedef struct CBTN_Event {
	int priority;
	Event* pEv;
} CBTN_Event;
typedef struct PriorityQueue {
	char priQ_name[MAX_NAME_LEN];
	int priQ_capacity;
	int priQ_size;
	int pos_last;
	CBTN_Event* pCBT_Ev;
} PriQ_Ev;
bool hasLeftChild(int pos, PriQ_Ev* pPriQ_Ev) {
	if (pos * 2 <= pPriQ_Ev->priQ_size)
		return TRUE;
	else
		return FALSE;
}
bool hasRightChild(int pos, PriQ_Ev* pPriQ_Ev) {
	if (pos * 2 + 1 <= pPriQ_Ev->priQ_size)
		return TRUE;
	else
		return FALSE;
}
PriQ_Ev* initPriQ_Ev(PriQ_Ev* pPriQ_Ev, const char* name, int capacity = 1) {
	strcpy(pPriQ_Ev->priQ_name, name);
	pPriQ_Ev->priQ_capacity = capacity;
	pPriQ_Ev->pCBT_Ev = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event));
	pPriQ_Ev->priQ_size = 0;
	pPriQ_Ev->pos_last = 0;
	return pPriQ_Ev;
}
void deletePriQ_Ev(PriQ_Ev* pPriQ_Ev) {
	CBTN_Event* pCBTN_Ev;
	for (int i = 0; i < pPriQ_Ev->priQ_size; i++) {
		pCBTN_Ev = &(pPriQ_Ev->pCBT_Ev)[i];
		if (pCBTN_Ev != NULL) {
			if (pCBTN_Ev->pEv != NULL)
				free(pCBTN_Ev->pEv);
			free(pCBTN_Ev);
		}
	}
}
void insertPriQ_Ev(PriQ_Ev* pPriQ_Ev, Event* pEv) {
	int pos, pos_parent;
	CBTN_Event CBTN_Ev_tmp;
	if (pPriQ_Ev->priQ_size >= pPriQ_Ev->priQ_capacity)	{ // 꽉 차면 사이즈 키우는 역할
		// Priority Queue is full
		/* Expand the capacity twice, and copy the entries */
		CBTN_Event* newCBT_Event;
		int newCapacity;
		newCapacity = 2 * pPriQ_Ev->priQ_capacity;
		newCBT_Event = (CBTN_Event*)malloc((newCapacity + 1) * sizeof(CBTN_Event));
		if (newCBT_Event == NULL) {
			printf("Error in expanding CompleteBinaryTree for Priority Queue !!\n");
			exit(-1);
		}
		for (int pos = 1; pos <= pPriQ_Ev->priQ_size; pos++) {
			newCBT_Event[pos] = pPriQ_Ev->pCBT_Ev[pos];
		}
		free(pPriQ_Ev->pCBT_Ev); // 기존 할당 해제
		pPriQ_Ev->pCBT_Ev = newCBT_Event;
		pPriQ_Ev->priQ_capacity = newCapacity;
	} // end - if
	/* insert at the last position */
	pos = ++pPriQ_Ev->priQ_size;
	pPriQ_Ev->pCBT_Ev[pos].priority = pEv->event_pri;
	pPriQ_Ev->pCBT_Ev[pos].pEv = pEv;
	/* up-heap bubbling */
	while (pos != POS_ROOT) {
		pos_parent = pos / 2;
		if (pPriQ_Ev->pCBT_Ev[pos].priority >= pPriQ_Ev->pCBT_Ev[pos_parent].priority) {
			break; // if the priority of the new packet is lower than its parent's priority,
			// just stop up-heap bubbling
		}
		else {
			CBTN_Ev_tmp = pPriQ_Ev->pCBT_Ev[pos_parent]; // 스왑
			pPriQ_Ev->pCBT_Ev[pos_parent] = pPriQ_Ev->pCBT_Ev[pos];
			pPriQ_Ev->pCBT_Ev[pos] = CBTN_Ev_tmp;
			pos = pos_parent; // 주소도 스왑
		}
	} // end - while
}
Event* removeMinPriQ_Ev(PriQ_Ev* pPriQ_Ev) {
	Event* pEv;
	CBTN_Event CBT_Event_tmp;
	int pos, pos_root = 1, pos_last, pos_child;
	if (pPriQ_Ev->priQ_size <= 0)
		return NULL; // 우선순위 큐가 비었으면 탈출
	pEv = pPriQ_Ev->pCBT_Ev[1].pEv; // 최고 우선순위 주소 반환
	pos_last = pPriQ_Ev->priQ_size; // 최 하단 주소 반환
	--pPriQ_Ev->priQ_size; // 뺄거니까 빼줌
	if (pPriQ_Ev->priQ_size > 0) { // 
		/* put the last node into the top position */
		pPriQ_Ev->pCBT_Ev[pos_root] = pPriQ_Ev->pCBT_Ev[pos_last]; // 최하단 주소를 최상단 주소로 이동
		pos_last--;
		/* down heap bubbling */
		pos = pos_root;
		while (hasLeftChild(pos, pPriQ_Ev)) { // 왼쪽에 자식이 있는가
			pos_child = pos * 2;
			if (hasRightChild(pos, pPriQ_Ev)) { // 오른쪽에 자식이 있는가
				if (pPriQ_Ev->pCBT_Ev[pos_child].priority > // 오른쪽 우선순위가 높으면 그놈 선택
					pPriQ_Ev->pCBT_Ev[pos_child + 1].priority)
					pos_child = pos * 2 + 1;
			}
			/* if the Event in pos_child has higher priority than Event in pos, swap them */
			if (pPriQ_Ev->pCBT_Ev[pos_child].priority < pPriQ_Ev->pCBT_Ev[pos].priority) {
				CBT_Event_tmp = pPriQ_Ev->pCBT_Ev[pos]; // 스왑
				pPriQ_Ev->pCBT_Ev[pos] = pPriQ_Ev->pCBT_Ev[pos_child];
				pPriQ_Ev->pCBT_Ev[pos_child] = CBT_Event_tmp;
			}
			else
				break;
			pos = pos_child;
		} // end while
	} // end if
	return pEv;
}
void fprintPriQ_Ev(FILE* fout, PriQ_Ev* pPriQ_Ev) {
	int pos, count, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;
	if (pPriQ_Ev->priQ_size == 0) {
		fprintf(fout, "PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;
	level = 0;
	level_count = 1; // level_count = 2^^level
	fprintf(fout, "\n CompBinTree :\n", level);
	while (count <= pPriQ_Ev->priQ_size) {
		fprintf(fout, " level%2d : ", level);
		count_per_line = 0;
		while (count_per_line < level_count) {
			pEv = pPriQ_Ev->pCBT_Ev[pos].pEv;
			eventPriority = pPriQ_Ev->pCBT_Ev[pos].priority;
			fprintEvent(fout, pEv);
			pos++;
			count++;
			if (count > pPriQ_Ev->priQ_size)
				break;
			count_per_line++;
			if ((count_per_line % EVENT_PER_LINE) == 0) {
				if (count_per_line < level_count)
					fprintf(fout, "\n ");
				else
					fprintf(fout, "\n");
			}
		} // end - while
		if ((count_per_line % EVENT_PER_LINE) != 0)
			fprintf(fout, "\n");
		level++;
		level_count *= 2;
	} // end - while
	fprintf(fout, "\n");
}
#endif