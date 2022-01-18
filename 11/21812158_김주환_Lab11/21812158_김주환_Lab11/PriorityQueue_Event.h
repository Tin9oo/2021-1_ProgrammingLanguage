/* PriorityQueue_Event.h */
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Event.h"
#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TRUE 1
#define FALSE 0
typedef struct CBTN_Event
{
	int priority;
	Event* pEv; // 저장되는 곳 주소
} CBTN_Event;
typedef struct PriorityQueue
{
	char priQ_name[MAX_NAME_LEN]; // 이름
	int priQ_capacity; // 용량
	int priQ_size; // 몇개가 포함되어 있는가
	int pos_last; // 마지막 위치
	CBTN_Event* pCBT_Ev; // 배열을 가르키는 역할
} PriQ_Ev;
bool hasLeftChild(int pos, PriQ_Ev* pPriQ_Ev);
bool hasRightChild(int pos, PriQ_Ev* pPriQ_Ev);
PriQ_Ev* initPriQ_Ev(PriQ_Ev* pPriQ_Ev, const char* name, int capacity = 1);
void deletePriQ_Ev(PriQ_Ev* pPriQ_Ev);
void insertPriQ_Ev(PriQ_Ev* pPriQ_Event, Event* pEvent);
Event* removeMinPriQ_Ev(PriQ_Ev* pPriQ_Event);
void printPriQ_Ev(PriQ_Ev* pPriQ_Event);
void fprintPriQ_Ev(FILE* fout, PriQ_Ev* pPriQ_Event);
#endif