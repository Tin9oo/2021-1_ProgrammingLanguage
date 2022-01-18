/* DLL_EvQ.cpp */
#include "DLL_EvQ.h"

void initDLL_EvQ(DLL_EvQ* pEvQ, int pri) {
	pEvQ->cs_EvQ.lock(); // ���� ������� �𸣱� ������ ��??
	pEvQ->priority = pri;
	pEvQ->front = pEvQ->back = NULL;
	pEvQ->num_event = 0;
	pEvQ->cs_EvQ.unlock();
}
Event* enDLL_EvQ(DLL_EvQ* pEvQ, Event* pEv) {
	DLLN_Ev* pLN_Ev;
	if (pEv == NULL) { // ���� ���� �̺�Ʈ�� NULL�̸� NULL ��ȯ
		printf("Error in enDLL_EvQ :: DLL_EvQ is NULL !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev = (DLLN_Ev*)calloc(1, sizeof(DLLN_Ev));
	if (pLN_Ev == NULL)	{ // �����Ҵ翡 �����ϸ� NULL ��ȯ
		printf("Error in enDLL_EvQ :: memory allocation for new DLLN failed !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev->pEv = pEv; // ���ο� �̺�Ʈ
	pEvQ->cs_EvQ.lock();
	if (pEvQ->num_event == 0) { // ť�� ����ִ� ���
		pEvQ->front = pEvQ->back = pLN_Ev; // front�� back�� ����
		pLN_Ev->prev = pLN_Ev->next = NULL; // ť ���ο� �ϳ��� �̺�Ʈ�� �����ϱ� ������ �� ���� NULL
		pEvQ->num_event = 1; // ť ���ο� �ϳ��� �̺�Ʈ�� ����
	}
	else { // ť�� ������� ���� ���
		pLN_Ev->prev = pEvQ->back; // ť�� ���� ����
		pEvQ->back->next = pLN_Ev; // ť�� ���� ����
		pEvQ->back = pLN_Ev;       // ť�� ���� ����
		pLN_Ev->next = NULL; // ť�� back���� ���
		pEvQ->num_event++; // ť ���� �� 1��ŭ ����
	}
	pEvQ->cs_EvQ.unlock();
	return pLN_Ev->pEv;
}
Event* deDLL_EvQ(DLL_EvQ* pEvQ) {
	Event* pEv;
	DLLN_Ev* pLN_Ev_OldFront;
	pEvQ->cs_EvQ.lock();
	if (pEvQ->num_event <= 0) {
		pEvQ->cs_EvQ.unlock();
		return NULL; // ť�� ��������� NULL ��ȯ
	}
	else {
		pLN_Ev_OldFront = pEvQ->front; // ������ �̺�Ʈ
		pEv = pEvQ->front->pEv;        // ������ �̺�Ʈ ����
		pEvQ->front = pEvQ->front->next; // front ������
		if (pEvQ->front != NULL) // ���ο� front�� NULL�� �ƴ� ���
			pEvQ->front->prev = NULL; // ť�� front���� ���
		pEvQ->num_event--; // ť ���� �� 1��ŭ ����
		free(pLN_Ev_OldFront); // release memory for the current front DLLN
		pEvQ->cs_EvQ.unlock();
		return pEv;
	}
}
void printDLL_EvQ(DLL_EvQ* pEvQ) {
	int index = 0;
	int count;
	Event* pEv;
	DLLN_Ev* pLN_Ev;
	if (pEvQ == NULL) {
		printf("Error in printDLL_EvQ :: DLL_EvQ is NULL !!");
		printf("Press any key to continue ...\n");
		getc(stdin);
	}
	//printf("DLL_EvQ(num_event: %2d):\n ", pEvQ->num_event);
	if (pEvQ->num_event <= 0)
		return;
	pLN_Ev = pEvQ->front;
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