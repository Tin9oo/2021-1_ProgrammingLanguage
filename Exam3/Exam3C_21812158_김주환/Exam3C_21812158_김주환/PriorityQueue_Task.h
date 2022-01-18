/* PriorityQueue_Task.h */
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "Task.h"

#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TRUE 1
#define FALSE 0

typedef struct CBTN_Task
{
	int priority;
	Task task;
} CBTN_Task;

typedef struct PriorityQueue
{
	char priQ_name[MAX_NAME_LEN];
	int priQ_capacity;
	int priQ_size;
	int pos_last;
	CBTN_Task* pCBT_Ev;
} PriQ_T;

PriQ_T* initPriQ_Task(PriQ_T* pPriQ_Task, const char* name, int capacity);
Task * enPriQ_Task(PriQ_T* pPriQ_Task, Task * pTask);
Task * dePriQ_Task(PriQ_T* pPriQ_Task);
void printPriQ_Task(PriQ_T* pPriQ_Task);
void fprintPriQ_Task(FILE * fout, PriQ_T* pPriQ_Task);
void deletePriQ_Task(PriQ_T* pPriQ_Task);
#endif