/* DLL_EvQ.cpp */
#include "DLL_EvQ.h"

void initDLL_EvQ(DLL_EvQ* pEvQ, int pri) {
	pEvQ->cs_EvQ.lock(); // 누가 사용할지 모르기 때문에 락??
	pEvQ->priority = pri;
	pEvQ->front = pEvQ->back = NULL;
	pEvQ->num_event = 0;
	pEvQ->cs_EvQ.unlock();
}
Event* enDLL_EvQ(DLL_EvQ* pEvQ, Event* pEv) {
	DLLN_Ev* pLN_Ev;
	if (pEv == NULL) { // 전달 받은 이벤트가 NULL이면 NULL 반환
		printf("Error in enDLL_EvQ :: DLL_EvQ is NULL !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev = (DLLN_Ev*)calloc(1, sizeof(DLLN_Ev));
	if (pLN_Ev == NULL)	{ // 동적할당에 실패하면 NULL 반환
		printf("Error in enDLL_EvQ :: memory allocation for new DLLN failed !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev->pEv = pEv; // 새로운 이벤트
	pEvQ->cs_EvQ.lock();
	if (pEvQ->num_event == 0) { // 큐가 비어있는 경우
		pEvQ->front = pEvQ->back = pLN_Ev; // front와 back은 동일
		pLN_Ev->prev = pLN_Ev->next = NULL; // 큐 내부에 하나의 이벤트만 존재하기 때문에 양 옆은 NULL
		pEvQ->num_event = 1; // 큐 내부에 하나의 이벤트만 존재
	}
	else { // 큐가 비어있지 않은 경우
		pLN_Ev->prev = pEvQ->back; // 큐의 끝에 연결
		pEvQ->back->next = pLN_Ev; // 큐의 끝에 연결
		pEvQ->back = pLN_Ev;       // 큐의 끝에 연결
		pLN_Ev->next = NULL; // 큐의 back임을 명시
		pEvQ->num_event++; // 큐 내부 수 1만큼 증가
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
		return NULL; // 큐가 비어있으면 NULL 반환
	}
	else {
		pLN_Ev_OldFront = pEvQ->front; // 추출할 이벤트
		pEv = pEvQ->front->pEv;        // 추출할 이벤트 저장
		pEvQ->front = pEvQ->front->next; // front 재조정
		if (pEvQ->front != NULL) // 새로운 front가 NULL이 아닌 경우
			pEvQ->front->prev = NULL; // 큐의 front임을 명시
		pEvQ->num_event--; // 큐 내부 수 1만큼 감소
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