/* Task.h */
#ifndef TASK_H
#define TASK_H
#include <stdio.h>
typedef struct
{
	int task_no; int task_pri;
} Task;

#define TASK_PER_LINE 5

void printTask(Task * tsk);
void fprintTask(FILE * fout, Task * tsk);
Task * genTask(int tsk_no, int tsk_pri);
#endif