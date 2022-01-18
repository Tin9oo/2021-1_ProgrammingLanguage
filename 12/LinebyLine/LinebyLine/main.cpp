#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <thread>
#include <mutex>
#include "Thread.h"
#include "DLL_EvQ.h"
#include "Event.h"
#include "ConsoleDisplay.h"
#define NUM_THREADS 4
void main()
{
	HANDLE hThread[NUM_THREADS];
	DWORD ExitCode[NUM_THREADS] = { 0 };
	ThreadParam thrdParam[NUM_THREADS];
	CRITICAL_SECTION CS_console;
	unsigned int thread_id[NUM_THREADS];
	char flag_thread_terminate_control = 0;
	char turn = 'M'; // default turn is main() 
	char mark;
	char name[80] = "";
	InitializeCriticalSection(&CS_console);
	/* Creations and Activations of Threads */
	printf("Creating and activating %d threads .....\n", NUM_THREADS);
	for (int i = 0; i < NUM_THREADS; i++)
	{
		EnterCriticalSection(&CS_console);
		printf("main() : %d-th thread is under creation .....\n", i);
		LeaveCriticalSection(&CS_console);
		// . . . . 이 부분은 직접 구현할 것.
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, Simple_Thread,
			&thrdParam[i], 0, &thread_id[i]);
		EnterCriticalSection(&CS_console);
		printf("main() : %d-th thread (id: %d) is now successfully created !\n",
			i, thread_id[i]);
		LeaveCriticalSection(&CS_console);
	}
	// execution of main() thread
	char myMark = 'M';
	for (int round = 0; round < MAX_ROUND; round++)
	{
		while (turn != myMark)
			Sleep(10);
		EnterCriticalSection(&CS_console);
		printf("round (%3d)\n", round);
		printf(" Thread_M :: ");
		for (int j = 0; j < 50; j++)
			printf("%c", myMark);
		printf("\n");
		LeaveCriticalSection(&CS_console);
		turn = 'A';
		Sleep(1);
	}
	/* Turn-On terminate flag to terminate threads */
	flag_thread_terminate_control = 1;
	for (int i = 0; i < NUM_THREADS; i++)
	{
		EnterCriticalSection(&CS_console);
		printf("main() : Waiting the Thread[%d] (%d) to terminate by itself ...\n",
			i, thread_id[i]);
		LeaveCriticalSection(&CS_console);
		// 이 부분은 직접 구현할 것
		EnterCriticalSection(&CS_console);
		printf("main() : %s (id: %d) is terminated now with ExitCode (%d).\n",
			thrdParam[i].name, thread_id[i], ExitCode[i]);
		LeaveCriticalSection(&CS_console);
		CloseHandle(hThread[i]);
	}
	EnterCriticalSection(&CS_console);
	printf("main() : all threads are terminated now !!!\n");
	LeaveCriticalSection(&CS_console);
	DeleteCriticalSection(&CS_console);
} // end main()
