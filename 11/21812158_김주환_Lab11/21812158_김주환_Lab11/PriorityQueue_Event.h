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
	Event* pEv; // ����Ǵ� �� �ּ�
} CBTN_Event;
typedef struct PriorityQueue
{
	char priQ_name[MAX_NAME_LEN]; // �̸�
	int priQ_capacity; // �뷮
	int priQ_size; // ��� ���ԵǾ� �ִ°�
	int pos_last; // ������ ��ġ
	CBTN_Event* pCBT_Ev; // �迭�� ����Ű�� ����
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