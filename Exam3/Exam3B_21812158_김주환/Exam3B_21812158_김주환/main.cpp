/*
* 파일명 : main.cpp
* 목적 및 기본 기능
*	환형 큐의 구현
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 5월 22일
*/

#include <stdio.h>
#include <stdlib.h>
#include "Task.h"
#include "CirQ_Task.h"

#define TOTAL_NUM_TASKS 50
#define CIRQUEUE_CAPACITY 10
#define MAX_ROUND 100
#define MAX_TASKS_PER_ROUND 10


void main()
{
	CirQ_Task * pCirQ_Task;
	Task task, * pTask = NULL;
	int max_tasks_per_round = 5;
	Task processed_tasks[TOTAL_NUM_TASKS];
	Task generated_tasks[TOTAL_NUM_TASKS];
	
	int total_processed_tasks = 0;
	int total_generated_tasks = 0;
	int num_tasks = 0;
	int num_generated_round = 0;
	int num_processed_round = 0;

	int c = 0, n = 0;

		printf("Testing Task Handling with FIFO Circular Queue\n");
	pCirQ_Task = (CirQ_Task*)calloc(1, sizeof(CirQ_Task));
	printf("Initializing FIFO_CirQ of capacity (%d)\n", CIRQUEUE_CAPACITY);
	pCirQ_Task = initCirQ_Task(pCirQ_Task, CIRQUEUE_CAPACITY);
	
	for (int round = 0; round < MAX_ROUND; round++)
	{
		//printf("start of Round(%2d) ****\n", round);
		if (total_generated_tasks < TOTAL_NUM_TASKS)
		{
			num_tasks = rand() % MAX_TASKS_PER_ROUND;
			if ((total_generated_tasks + num_tasks) > TOTAL_NUM_TASKS)
				num_tasks = TOTAL_NUM_TASKS - total_generated_tasks;
			//printf("generate and enqueue %2d tasks\n", num_tasks);
			num_generated_round = 0;
			for (int i = 0; i < num_tasks; i++)
				{
				if (isCirQFull(pCirQ_Task))
				{
					//printf("CirQ_Task is full --> skip generation of event. \n");
					break;
				}
				pTask = genTask(total_generated_tasks,
					TOTAL_NUM_TASKS - total_generated_tasks - 1);
				enCirQ_Task(pCirQ_Task, *pTask);
				//printCirQ_Task(pCirQ_Task);
				generated_tasks[total_generated_tasks] = *pTask;
				free(pTask);
				total_generated_tasks++;
				num_generated_round++;
				} // end for
			} // end if
		num_tasks = rand() % MAX_TASKS_PER_ROUND;
		if ((total_processed_tasks + num_tasks) > TOTAL_NUM_TASKS)
			num_tasks = TOTAL_NUM_TASKS - total_processed_tasks;
		//printf("dequeue %2d tasks\n", num_tasks);
		num_processed_round = 0;
		for (int i = 0; i < num_tasks; i++)
			{
			if (isCirQEmpty(pCirQ_Task))
				break;
			pTask = deCirQ_Task(pCirQ_Task);
			if (pTask != NULL)
			{
				processed_tasks[total_processed_tasks] = *pTask;
				total_processed_tasks++;
				num_processed_round++;
			}
		} // end for
		
		/* Monitoring simulation status */
		printf("Round(%2d): generated_in_this_round(%3d), total_generated(%3d), processed_in_this_round(% 3d), total_processed_tasks(% 3d), tasks_in_queue(% 3d)\n", round, num_generated_round, total_generated_tasks,
			num_processed_round, total_processed_tasks, pCirQ_Task->num_elements);
		if (total_processed_tasks >= TOTAL_NUM_TASKS)
			break;
	} // end for()
	printf("\nGenerated Tasks :\n");
	for (int i = 0; i < TOTAL_NUM_TASKS; i++)
	{
		printf("Task(id:%3d, pri:%3d), ", generated_tasks[i].task_no,
			generated_tasks[i].task_pri);
		if ((i + 1) % 5 == 0)
			printf("\n");
		}
	printf("\n");
	printf("Processed Tasks :\n");
	for (int i = 0; i < TOTAL_NUM_TASKS; i++)
	{
		printf("Task(id:%3d, pri:%3d), ", processed_tasks[i].task_no,
			processed_tasks[i].task_pri);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("\n");
	delCirQ_Task(pCirQ_Task);
}