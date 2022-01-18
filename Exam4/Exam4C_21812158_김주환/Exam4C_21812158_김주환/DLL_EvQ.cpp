/* DLL_EvQ.cpp */
#include "DLL_EvQ.h"

// doubly linked list node (DLLN)
void initDLL_EvQ(DLL_EvQ* DLL_EvQ, int priority) {
	DLL_EvQ->cs_EvQ.lock(); // 누가 사용할지 모르기 때문에 락??
	DLL_EvQ->priority = priority;
	DLL_EvQ->front = DLL_EvQ->back = NULL;
	DLL_EvQ->num_event = 0;
	DLL_EvQ->cs_EvQ.unlock();
}
Event* enDLL_EvQ(DLL_EvQ* DLL_EvQ, Event* pEv) {
	DLLN_Ev* pLN_Ev;
	if (pEv == NULL) { // 전달 받은 이벤트가 NULL이면 NULL 반환
		printf("Error in enDLL_EvQ :: DLL_EvQ is NULL !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev = (DLLN_Ev*)calloc(1, sizeof(DLLN_Ev));
	if (pLN_Ev == NULL) { // 동적할당에 실패하면 NULL 반환
		printf("Error in enDLL_EvQ :: memory allocation for new DLLN failed !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev->pEv = pEv; // 새로운 이벤트
	DLL_EvQ->cs_EvQ.lock();
	if (DLL_EvQ->num_event == 0) { // 큐가 비어있는 경우
		DLL_EvQ->front = DLL_EvQ->back = pLN_Ev; // front와 back은 동일
		pLN_Ev->prev = pLN_Ev->next = NULL; // 큐 내부에 하나의 이벤트만 존재하기 때문에 양 옆은 NULL
		DLL_EvQ->num_event = 1; // 큐 내부에 하나의 이벤트만 존재
	}
	else { // 큐가 비어있지 않은 경우
		pLN_Ev->prev = DLL_EvQ->back; // 큐의 끝에 연결
		DLL_EvQ->back->next = pLN_Ev; // 큐의 끝에 연결
		DLL_EvQ->back = pLN_Ev;       // 큐의 끝에 연결
		pLN_Ev->next = NULL; // 큐의 back임을 명시
		DLL_EvQ->num_event++; // 큐 내부 수 1만큼 증가
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
		return NULL; // 큐가 비어있으면 NULL 반환
	}
	else {
		pLN_Ev_OldFront = DLL_EvQ->front; // 추출할 이벤트
		pEv = DLL_EvQ->front->pEv;        // 추출할 이벤트 저장
		DLL_EvQ->front = DLL_EvQ->front->next; // front 재조정
		if (DLL_EvQ->front != NULL) // 새로운 front가 NULL이 아닌 경우
			DLL_EvQ->front->prev = NULL; // 큐의 front임을 명시
		DLL_EvQ->num_event--; // 큐 내부 수 1만큼 감소
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