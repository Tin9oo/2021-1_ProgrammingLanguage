/*
* 파일명 : main.cpp
* 목적 및 기본 기능
*	우선순위 큐의 구현
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 5월 22일
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Task.h"
#include "PriorityQueue_Task.h"

#define TASKS_GENERATOR 0
#define TOTAL_NUM_TASKS 50
#define MAX_ROUND 100
#define INIT_PriQ_SIZE 1

void main()
{
	PriQ_T* pPriQ_T;
	Task* pEv = NULL;
	Task processed_events[TOTAL_NUM_TASKS];

	FILE* fout;

	int data;
	int total_processed_tasks = 0;
	int total_generated_tasks = 0;
	int num_tasks = 0;
	int num_generated_round = 0;
	int num_processed_round = 0;

	int max_tasks_per_round;
	srand(time(0));

	printf("Input num_tasks per round :");
	scanf("%d", &max_tasks_per_round);
	PriQ_T* pPriQ_Task;
	Task * pTask = NULL;
	Task generated_tasks[TOTAL_NUM_TASKS];
	Task processed_tasks[TOTAL_NUM_TASKS];
	
	fout = fopen("output.txt", "w");

	fprintf(fout, "Testing Task Handling with Priority Queue\n");
	pPriQ_Task = (PriQ_T*)malloc(sizeof(PriQ_T));
	if (pPriQ_Task == NULL)
	{
		printf("Error in malloc() for PriQ_Task !\n");
		fclose(fout);
		exit(-1);
	}
	printf("Initializing PriQ_Task of capacity (%d)\n", INIT_PriQ_SIZE);
	initPriQ_Task(pPriQ_Task, "PriQ_Task", INIT_PriQ_SIZE);
	
	for (int round = 0; round < MAX_ROUND; round++)
	{
		fprintf(fout, "\n*** Start of round(%2d)...\n", round);
		num_generated_round = 0;
		if (total_generated_tasks < TOTAL_NUM_TASKS)
		{
			num_tasks = max_tasks_per_round;
			if ((total_generated_tasks + num_tasks) > TOTAL_NUM_TASKS)
				num_tasks = TOTAL_NUM_TASKS - total_generated_tasks;
			fprintf(fout, ">>> enqueue %2d tasks\n", num_tasks);
			for (int i = 0; i < num_tasks; i++)
			{
				pTask = genTask(total_generated_tasks,
					TOTAL_NUM_TASKS - total_generated_tasks - 1);
				if (pTask == NULL)
				{
					printf("Error in generation of event !!\n");
					fclose(fout);
					exit(-1);
				}
				fprintf(fout, " *** enqued event : ");
				fprintTask(fout, pTask);
				enPriQ_Task(pPriQ_Task, pTask);
				generated_tasks[total_generated_tasks] = *pTask;
				total_generated_tasks++;
				num_generated_round++;
				fprintPriQ_Task(fout, pPriQ_Task);
				}
			}
		num_tasks = max_tasks_per_round;
		if ((total_processed_tasks + num_tasks) > TOTAL_NUM_TASKS)
			num_tasks = TOTAL_NUM_TASKS - total_processed_tasks;
		fprintf(fout, "<<< dequeue %2d tasks\n", num_tasks);
		num_processed_round = 0;
		for (int i = 0; i < num_tasks; i++)
		{
			pTask = dePriQ_Task(pPriQ_Task);
			if (pTask == NULL)
			{
				fprintf(fout, " PriQ is empty\n");
				break;
			}
			
			fprintf(fout, " *** dequeued event : ");
			fprintTask(fout, pTask);
			fprintPriQ_Task(fout, pPriQ_Task);
			processed_tasks[total_processed_tasks] = *pTask;
			free(pTask);
			total_processed_tasks++;
			num_processed_round++;
		}
		/* Monitoring simulation status */
		fprintf(fout, "Round(%2d): generated_in_this_round(%3d), total_generated_tasks(% 3d), processed_in_this_round(% 3d), total_processed_tasks(% 3d), tasks_in_queue(% 3d)\n\n", round,
			num_generated_round, total_generated_tasks, num_processed_round,
			total_processed_tasks, pPriQ_Task->priQ_size);
		printf("Round(%2d): generated_in_this_round(%3d), total_generated(%3d), processed_in_this_round(% 3d), total_processed_tasks(% 3d), tasks_in_queue(% 3d)\n", round, num_generated_round, total_generated_tasks,
			num_processed_round, total_processed_tasks, pPriQ_Task->priQ_size);
		fflush(fout);
		if (total_processed_tasks >= TOTAL_NUM_TASKS)
			break;
		}
	
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
	deletePriQ_Task(pPriQ_Task);
	fprintf(fout, "\n");
	fclose(fout);
}