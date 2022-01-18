/* DLL_EvQ.cpp */
#include "DLL_EvQ.h"

// doubly linked list node (DLLN)
void initDLL_EvQ(DLL_EvQ* DLL_EvQ, int priority) {
	DLL_EvQ->cs_EvQ.lock(); // ���� ������� �𸣱� ������ ��??
	DLL_EvQ->priority = priority;
	DLL_EvQ->front = DLL_EvQ->back = NULL;
	DLL_EvQ->num_event = 0;
	DLL_EvQ->cs_EvQ.unlock();
}
Event* enDLL_EvQ(DLL_EvQ* DLL_EvQ, Event* pEv) {
	DLLN_Ev* pLN_Ev;
	if (pEv == NULL) { // ���� ���� �̺�Ʈ�� NULL�̸� NULL ��ȯ
		printf("Error in enDLL_EvQ :: DLL_EvQ is NULL !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev = (DLLN_Ev*)calloc(1, sizeof(DLLN_Ev));
	if (pLN_Ev == NULL) { // �����Ҵ翡 �����ϸ� NULL ��ȯ
		printf("Error in enDLL_EvQ :: memory allocation for new DLLN failed !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev->pEv = pEv; // ���ο� �̺�Ʈ
	DLL_EvQ->cs_EvQ.lock();
	if (DLL_EvQ->num_event == 0) { // ť�� ����ִ� ���
		DLL_EvQ->front = DLL_EvQ->back = pLN_Ev; // front�� back�� ����
		pLN_Ev->prev = pLN_Ev->next = NULL; // ť ���ο� �ϳ��� �̺�Ʈ�� �����ϱ� ������ �� ���� NULL
		DLL_EvQ->num_event = 1; // ť ���ο� �ϳ��� �̺�Ʈ�� ����
	}
	else { // ť�� ������� ���� ���
		pLN_Ev->prev = DLL_EvQ->back; // ť�� ���� ����
		DLL_EvQ->back->next = pLN_Ev; // ť�� ���� ����
		DLL_EvQ->back = pLN_Ev;       // ť�� ���� ����
		pLN_Ev->next = NULL; // ť�� back���� ���
		DLL_EvQ->num_event++; // ť ���� �� 1��ŭ ����
	}
	DLL_EvQ->cs_EvQ.unlock();
	return pLN_Ev->pEv;
}
Event* deDLL_EvQ(DLL_EvQ* DLL_EvQ) {
	Event* pEv;
	DLLN_Ev* pLN_Ev_OldFront;
	DLL_EvQ->cs_EvQ.lock();
	if (DLL_EvQ->num_event <= 0) {
		DLL_EvQ->cs_EvQ.unlock();
		return NULL; // ť�� ��������� NULL ��ȯ
	}
	else {
		pLN_Ev_OldFront = DLL_EvQ->front; // ������ �̺�Ʈ
		pEv = DLL_EvQ->front->pEv;        // ������ �̺�Ʈ ����
		DLL_EvQ->front = DLL_EvQ->front->next; // front ������
		if (DLL_EvQ->front != NULL) // ���ο� front�� NULL�� �ƴ� ���
			DLL_EvQ->front->prev = NULL; // ť�� front���� ���
		DLL_EvQ->num_event--; // ť ���� �� 1��ŭ ����
		free(pLN_Ev_OldFront); // release memory for the current front DLLN
		DLL_EvQ->cs_EvQ.unlock();
		return pEv;
	}
}
void printDLL_EvQ(DLL_EvQ* DLL_EvQ) {
	int index = 0;
	int count;
	Event* pEv;
	DLLN_Ev* pLN_Ev;
	if (DLL_EvQ == NULL) {
		printf("Error in printDLL_EvQ :: DLL_EvQ is NULL !!");
		printf("Press any key to continue ...\n");
		getc(stdin);
	}
	//printf("DLL_EvQ(num_event: %2d):\n ", pEvQ->num_event);
	if (DLL_EvQ->num_event <= 0)
		return;
	pLN_Ev = DLL_EvQ->front;
	count = 0;
	while (pLN_Ev != NULL) {
		pEv = pLN_Ev->pEv;
		if (pEv == NULL)
			break;
		printEvent(pEv); printf(" ");
		count++;
		if ((count % 5) == 0)
			printf("\n ");
		pLN_Ev = pLN_Ev->next;
	}
}