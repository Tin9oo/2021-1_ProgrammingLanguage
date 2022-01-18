/* PriorityQueue_Task.cpp */
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Task.h"
#include "PriorityQueue_Task.h"

#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TRUE 1
#define FALSE 0

typedef struct CBTN_Task
{
	int priority;
	Task* task;
} CBTN_Task;

typedef struct PriorityQueue
{
	char priQ_name[MAX_NAME_LEN];
	int priQ_capacity;
	int priQ_size;
	int pos_last;
	CBTN_Task* pCBT_T;
} PriQ_T;

PriQ_T* initPriQ_Task(PriQ_T* pPriQ_Task, const char* name, int capacity) {
	strcpy(pPriQ_Task->priQ_name, name);
	pPriQ_Task->priQ_capacity = capacity;
	pPriQ_Task->pCBT_T = (CBTN_Task*)calloc((capacity + 1), sizeof(CBTN_Task));
	pPriQ_Task->priQ_size = 0;
	pPriQ_Task->pos_last = 0;
	return pPriQ_Task;
}
Task* enPriQ_Task(PriQ_T* pPriQ_Task, Task* pTask) {
	int pos, pos_parent;
	CBTN_Task CBTN_T_tmp;
	if (pPriQ_Task->priQ_size >= pPriQ_Task->priQ_capacity) { // 꽉 차면 사이즈 키우는 역할
		// Priority Queue is full
		/* Expand the capacity twice, and copy the entries */
		CBTN_Task* newCBT_Task;
		int newCapacity;
		newCapacity = 2 * pPriQ_Task->priQ_capacity;
		newCBT_Task = (CBTN_Task*)malloc((newCapacity + 1) * sizeof(CBTN_Task));
		if (newCBT_Task == NULL) {
			printf("Error in expanding CompleteBinaryTree for Priority Queue !!\n");
			exit(-1);
		}
		for (int pos = 1; pos <= pPriQ_Task->priQ_size; pos++) {
			newCBT_Task[pos] = pPriQ_Task->pCBT_T[pos];
		}
		free(pPriQ_Task->pCBT_T); // 기존 할당 해제
		pPriQ_Task->pCBT_T = newCBT_Task;
		pPriQ_Task->priQ_capacity = newCapacity;
	} // end - if
	/* insert at the last position */
	pos = ++pPriQ_Task->priQ_size;
	pPriQ_Task->pCBT_T[pos].priority = pTask->task_pri;
	pPriQ_Task->pCBT_T[pos].task = pTask;
	/* up-heap bubbling */
	while (pos != POS_ROOT) {
		pos_parent = pos / 2;
		if (pPriQ_Task->pCBT_T[pos].priority >= pPriQ_Task->pCBT_T[pos_parent].priority) {
			break; // if the priority of the new packet is lower than its parent's priority,
			// just stop up-heap bubbling
		}
		else {
			CBTN_T_tmp = pPriQ_Task->pCBT_T[pos_parent]; // 스왑
			pPriQ_Task->pCBT_T[pos_parent] = pPriQ_Task->pCBT_T[pos];
			pPriQ_Task->pCBT_T[pos] = CBTN_T_tmp;
			pos = pos_parent; // 주소도 스왑
		}
	} // end - while
}
Task* dePriQ_Task(PriQ_T* pPriQ_Task) {
	Task* pT;
	CBTN_Task CBT_T_tmp;
	int pos, pos_root = 1, pos_last, pos_child;
	int lh, rh;
	if (pPriQ_Task->priQ_size <= 0)
		return NULL; // 우선순위 큐가 비었으면 탈출
	pT = pPriQ_Task->pCBT_T[1].task; // 최고 우선순위 주소 반환
	pos_last = pPriQ_Task->priQ_size; // 최 하단 주소 반환
	--pPriQ_Task->priQ_size; // 뺄거니까 빼줌
	if (pPriQ_Task->priQ_size > 0) { // 
		/* put the last node into the top position */
		pPriQ_Task->pCBT_T[pos_root] = pPriQ_Task->pCBT_T[pos_last]; // 최하단 주소를 최상단 주소로 이동
		pos_last--;
		/* down heap bubbling */
		pos = pos_root;
		if (pos * 2 <= pPriQ_Task->priQ_size)
			lh = TRUE;
		else
			lh = FALSE;
		while (lh) { // 왼쪽에 자식이 있는가
			pos_child = pos * 2;
			if (pos * 2 + 1 <= pPriQ_Task->priQ_size)
				rh = TRUE;
			else
				rh = FALSE;
			if (rh) { // 오른쪽에 자식이 있는가
				if (pPriQ_Task->pCBT_T[pos_child].priority > // 오른쪽 우선순위가 높으면 그놈 선택
					pPriQ_Task->pCBT_T[pos_child + 1].priority)
					pos_child = pos * 2 + 1;
			}
			/* if the Event in pos_child has higher priority than Event in pos, swap them */
			if (pPriQ_Task->pCBT_T[pos_child].priority < pPriQ_Task->pCBT_T[pos].priority) {
				CBT_T_tmp = pPriQ_Task->pCBT_T[pos]; // 스왑
				pPriQ_Task->pCBT_T[pos] = pPriQ_Task->pCBT_T[pos_child];
				pPriQ_Task->pCBT_T[pos_child] = CBT_T_tmp;
			}
			else
				break;
			pos = pos_child;
		} // end while
	} // end if
	return pT;
}
void printPriQ_Task(PriQ_T* pPriQ_Task) {
	int pos, count, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1;
	Task* pT;
	if (pPriQ_Task->priQ_size == 0) {
		printf("PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;
	level = 0;
	level_count = 1; // level_count = 2^^level
	printf("\n CompBinTree :\n", level);
	while (count <= pPriQ_Task->priQ_size) {
		printf(" level%2d : ", level);
		count_per_line = 0;
		while (count_per_line < level_count) {
			pT = pPriQ_Task->pCBT_T[pos].task;
			eventPriority = pPriQ_Task->pCBT_T[pos].priority;
			printTask(pT);
			pos++;
			count++;
			if (count > pPriQ_Task->priQ_size)
				break;
			count_per_line++;
			if ((count_per_line % TASK_PER_LINE) == 0) {
				if (count_per_line < level_count)
					printf("\n ");
				else
					printf("\n");
			}
		} // end - while
		if ((count_per_line % TASK_PER_LINE) != 0)
			printf("\n");
		level++;
		level_count *= 2;
	} // end - while
	printf("\n");
}
void fprintPriQ_Task(FILE* fout, PriQ_T* pPriQ_Task) {
	int pos, count, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1;
	Task* pT;
	if (pPriQ_Task->priQ_size == 0) {
		fprintf(fout, "PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;
	level = 0;
	level_count = 1; // level_count = 2^^level
	fprintf(fout, "\n CompBinTree :\n", level);
	while (count <= pPriQ_Task->priQ_size) {
		fprintf(fout, " level%2d : ", level);
		count_per_line = 0;
		while (count_per_line < level_count) {
			pT = pPriQ_Task->pCBT_T[pos].task;
			eventPriority = pPriQ_Task->pCBT_T[pos].priority;
			fprintTask(fout, pT);
			pos++;
			count++;
			if (count > pPriQ_Task->priQ_size)
				break;
			count_per_line++;
			if ((count_per_line % TASK_PER_LINE) == 0) {
				if (count_per_line < level_count)
					fprintf(fout, "\n ");
				else
					fprintf(fout, "\n");
			}
		} // end - while
		if ((count_per_line % TASK_PER_LINE) != 0)
			fprintf(fout, "\n");
		level++;
		level_count *= 2;
	} // end - while
	fprintf(fout, "\n");
}
void deletePriQ_Task(PriQ_T* PriQ_T) {
	CBTN_Task* pCBTN_Task;
	for (int i = 0; i < PriQ_T->priQ_size; i++) {
		pCBTN_Task = &(PriQ_T->pCBT_T)[i];
		if (pCBTN_Task != NULL) {
			if (pCBTN_Task->task != NULL)
				free(pCBTN_Task->task);
			free(pCBTN_Task);
		}
	}
}
#endif