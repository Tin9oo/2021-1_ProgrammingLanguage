/*
* ���ϸ� : main.cpp
* ���� �� �⺻ ���
*	Circular queue, Priority Queue
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 5�� 21��
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Event.h"
#include "CirQ_Event.h"
#include "PriorityQueue_Event.h"

#define EVENT_GENERATOR 0
#define TOTAL_NUM_EVENTS 128
#define MAX_ROUND 100
#define INIT_PriQ_SIZE 1

void test_FIFO_CirQ_Event(FILE* fout, int max_events_per_round);
void test_PriQ_Event(FILE* fout, int max_events_per_round);

int main() {
	FILE* fout;
	int menu;
	int max_events_per_round;
	fout = fopen("output.txt", "w");
	if (fout == NULL) {
		printf("Error in creation of output.txt file !!\n");
		exit(-1);
	}
	// srand(time(0));
	while (1) {
		printf("\nAvailable Menu : \n");
		printf(" 1. Test FIFO/CirQ Event.\n");
		printf(" 2. Test PriQ Event.\n");
		printf("Input menu (0 to quit) : ");
		scanf("%d", &menu); // ���� ����
		if (menu == 0)
			break;
		printf("Input num_events per round :");
		scanf("%d", &max_events_per_round); // �̺�Ʈ
		switch (menu) {
		case 1:
			test_FIFO_CirQ_Event(fout, max_events_per_round); // ���� ���� ��ȯ ť
			break;
		case 2:
			test_PriQ_Event(fout, max_events_per_round); // �켱���� ť
			break;
		default:
			break;
		}
	}
	fclose(fout);
	return 0;
}
void test_FIFO_CirQ_Event(FILE* fout, int max_events_per_round) {
	CirQ_Event* pCirQ_Event;
	Event ev, * pEv = NULL;
	Event processed_events[TOTAL_NUM_EVENTS]; // ó���� �̺�Ʈ ���

	int total_processed_events = 0;
	int total_generated_events = 0;
	int num_events = 0;
	int num_generated_round = 0;
	int num_processed_round = 0;

	int c = 0, n = 0;

	fprintf(fout, "Testing Event Handling with FIFO Circular Queue\n");
	pCirQ_Event = (CirQ_Event*)calloc(1, sizeof(CirQ_Event));
	printf("Initializing FIFO_CirQ of capacity (%d)\n", max_events_per_round);
	fprintf(fout, "Initializing FIFO_CirQ of capacity (%d)\n", max_events_per_round);
	pCirQ_Event = initCirQ(pCirQ_Event, max_events_per_round); // �ʱ�ȭ �۾�

	//fprintQueue(fout, pCirQ_Event);
	//fprintf(fout, "\nEnqueuing data into event circular queue: \n");
	for (int round = 0; round < MAX_ROUND; round++)	{ // ���� �ݺ�
		printf("Expand CirQ Size(CS NS) : ");
		scanf("%d %d", &c, &n);
		pCirQ_Event->capacity = expand_CirQ(pCirQ_Event, c, n);
		fprintf(fout, "start of Round(%2d) ****\n", round);
		if (total_generated_events < TOTAL_NUM_EVENTS) { // ������ �̺�Ʈ ���� ���� ������ ���� �ʵ��� ����
			num_events = max_events_per_round; // ���ϴ� �̺�Ʈ ��
			if ((total_generated_events + num_events) > TOTAL_NUM_EVENTS)
				num_events = TOTAL_NUM_EVENTS - total_generated_events; // �����ִ� ���� ��ŭ�� ����
			fprintf(fout, "generate and enque %2d events\n", num_events);
			num_generated_round = 0;
			for (int i = 0; i < num_events; i++) {
				if (isCirQFull(pCirQ_Event)) { // ť�� �� �������� Ż��
					fprintf(fout, " !!! CirQ_Event is full --> skip generation and enqueueing of event. \n");
					printf(" !!! CirQ_Event is full --> skip generation and enqueueing of event. \n");
						break;
				}
				/*if (total_generated_events == TOTAL_NUM_EVENTS - 1) {
					if ((TOTAL_NUM_EVENTS % 2) == 0)
					total_generated_events++;
					break;
				}*/
				pEv = genEvent(pEv, EVENT_GENERATOR, total_generated_events, // �̺�Ʈ ����
					TOTAL_NUM_EVENTS - total_generated_events - 1);
				fprintf(fout, ">>> Enqueue event = ");
				fprintEvent(fout, pEv);
				fprintf(fout, "\n");
				enCirQ(fout, pCirQ_Event, *pEv); // ������ �̺�Ʈ�� ��ȯ ť�� ���� �ֱ�
				fprintCirQ(fout, pCirQ_Event);
				free(pEv);
				total_generated_events++;
				num_generated_round++;
			} // end for
		} // end if

		//fprintf(fout, "\nDequeuing data from event circular queue: \n");
		num_events = max_events_per_round;
		if ((total_processed_events + num_events) > TOTAL_NUM_EVENTS)
			num_events = TOTAL_NUM_EVENTS - total_processed_events;
		fprintf(fout, "dequeue %2d events\n", num_events);
		num_processed_round = 0; // �̹� ���忡�� ��� ó���ߴ°�
		for (int i = 0; i < num_events; i++) {
			if (isCirQEmpty(pCirQ_Event)) { // ������� Ż��
				fprintf(fout, " !!! CirQ_Event is full --> skip generation and enqueueing of event. \n");
				printf(" !!! CirQ_Event is full --> skip generation and enqueueing of event. \n");
				break;
			}
			pEv = deCirQ(fout, pCirQ_Event); // �̾Ƴ���
			if (pEv != NULL) {
				fprintf(fout, "<<< Dequed event = ");
				fprintEvent(fout, pEv);
				fprintf(fout, "\n");
				processed_events[total_processed_events] = *pEv; // � ������ ó���ƴ��� Ȯ��
				total_processed_events++;
				num_processed_round++;
			}
			fprintCirQ(fout, pCirQ_Event);
		} // end for
		/* Monitoring simulation status */
		fprintf(fout, "Round(%2d): generated_in_this_round(%3d), total_generated_events(%3d), processed_in_this_round(% 3d), total_processed_events(% 3d), events_in_queue(% 3d)\n\n",
			round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pCirQ_Event->num_elements);
		printf("Round(%2d): generated_in_this_round(%3d), total_generated(%3d), processed_in_this_round(% 3d), total_processed_events(% 3d), events_in_queue(% 3d)\n",
			round, num_generated_round, total_generated_events,	num_processed_round, total_processed_events, pCirQ_Event->num_elements);
		if (total_processed_events >= TOTAL_NUM_EVENTS)
			break;
	} // end for()
	printf("Processed Events :\n");
	for (int i = 0; i < TOTAL_NUM_EVENTS; i++) 	{
		printf("Ev(id:%3d, pri:%3d), ", processed_events[i].event_no,
			processed_events[i].event_pri);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("\n");
	delCirQ(pCirQ_Event); // �ݳ�
}
void test_PriQ_Event(FILE* fout, int max_events_per_round) {
	PriQ_Ev* pPriQ_Ev;
	Event* pEv = NULL;
	Event processed_events[TOTAL_NUM_EVENTS];

	int data;
	int total_processed_events = 0;
	int total_generated_events = 0;
	int num_events = 0;
	int num_generated_round = 0;
	int num_processed_round = 0;

	fprintf(fout, "Testing Event Handling with Priority Queue\n");
	pPriQ_Ev = (PriQ_Ev*)malloc(sizeof(PriQ_Ev));
	if (pPriQ_Ev == NULL) {
		printf("Error in malloc() for PriorityQueue_Event !\n");
		fclose(fout);
		exit(-1);
	}
	printf("Initializing PriorityQueue_Event of capacity (%d)\n", INIT_PriQ_SIZE);
	initPriQ_Ev(pPriQ_Ev, "PriorityQueue_Event", INIT_PriQ_SIZE); // �ʱ�ȭ
	for (int round = 0; round < MAX_ROUND; round++) { // ����
		fprintf(fout, "\n*** Start of round(%2d)...\n", round);
		num_generated_round = 0;
		if (total_generated_events < TOTAL_NUM_EVENTS) { // ó���� ���� �����ִ� ���
			num_events = max_events_per_round;
			if ((total_generated_events + num_events) > TOTAL_NUM_EVENTS) // ���� ������ ����
				num_events = TOTAL_NUM_EVENTS - total_generated_events;
			fprintf(fout, ">>> enque %2d events\n", num_events);
			for (int i = 0; i < num_events; i++) {
				pEv = genEvent(pEv, 0, total_generated_events, TOTAL_NUM_EVENTS -
					total_generated_events - 1); // �̺�Ʈ ����
				if (pEv == NULL) {
					printf("Error in generation of event !!\n");
					fclose(fout);
					exit(-1);
				}
				fprintf(fout, " *** enqued event : ");
				fprintEvent(fout, pEv);
				insertPriQ_Ev(pPriQ_Ev, pEv); // �̺�Ʈ �߰�
				total_generated_events++;
				num_generated_round++;
				fprintPriQ_Ev(fout, pPriQ_Ev);
			}
		}
		//fprintf(fout, "\n======================================================\n");
		//fprintf(fout, "\nRemoving min data from Priority Queue . . . \n");
		num_events = max_events_per_round;
		if ((total_processed_events + num_events) > TOTAL_NUM_EVENTS)
			num_events = TOTAL_NUM_EVENTS - total_processed_events;
		fprintf(fout, "<<< dequeue %2d events\n", num_events);
		num_processed_round = 0;
		for (int i = 0; i < num_events; i++) {
			pEv = removeMinPriQ_Ev(pPriQ_Ev); // ����
			if (pEv == NULL) {
				fprintf(fout, " PriQ is empty\n");
				break;
			}
			fprintf(fout, " *** dequeued event : ");
			fprintEvent(fout, pEv);
			fprintPriQ_Ev(fout, pPriQ_Ev);
			processed_events[total_processed_events] = *pEv; // ���� ���
			total_processed_events++;
			num_processed_round++;
		}
		/* Monitoring simulation status */
		fprintf(fout, "Round(%2d): generated_in_this_round(%3d), total_generated_events(%3d), processed_in_this_round(% 3d), total_processed_events(% 3d), events_in_queue(% 3d)\n\n",
			round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pPriQ_Ev->priQ_size);
		printf("Round(%2d): generated_in_this_round(%3d), total_generated(%3d), processed_in_this_round(% 3d), total_processed_events(% 3d), events_in_queue(% 3d)\n",
			round, num_generated_round, total_generated_events, num_processed_round,
			total_processed_events, pPriQ_Ev->priQ_size);
		fflush(fout);
		if (total_processed_events >= TOTAL_NUM_EVENTS) // �ʰ� �� Ż��
			break;
	}
	printf("Processed Events :\n");
	for (int i = 0; i < TOTAL_NUM_EVENTS; i++) { // ó�� ���� ���
		printf("Ev(id:%3d, pri:%3d), ", processed_events[i].event_no, processed_events[i].event_pri);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("\n");
	deletePriQ_Ev(pPriQ_Ev); // ��ȯ
	fprintf(fout, "\n");
}