/* Task.h */
#ifndef TASK_H
#define TASK_H
#include <stdio.h>
#include <stdlib.h>
#include "Task.h"

typedef struct
{
	int task_no; int task_pri;
} Task;

#define TASK_PER_LINE 5

void printTask(Task* tsk) {
	printf("Ev(no:%3d, pri:%2d) ", tsk->task_no, tsk->task_pri);
}
void fprintTask(FILE* fout, Task* tsk) {
	fprintf(fout, "Ev(no:%3d, pri:%2d) ", tsk->task_no, tsk->task_pri);
}
Task* genTask(int tsk_no, int tsk_pri) {
	Task* pT = NULL;
	pT = (Task*)calloc(1, sizeof(Task));
	if (pT == NULL)
		return NULL;
	pT->task_no = tsk_no;
	pT->task_pri = tsk_pri;
	return pT;
}
#endif