#include "stdafx.h"
#include <stdlib.h>
#include <conio.h>
#include <assert.h>
int main(int argc, char* argv[])
{
	if (argc < 3)// is equal to assert(argc >= 3);
	{
		printf("\nHello World! from ProcessC :Error argc < 3\nPress any key to exit!\n");
		getch();
		return 0;
	}

	char s[256];
	sprintf(s, "ProcessC resumed by ProcessA, hProcessB = %s, A's PID = %s",
		argv[1], argv[2]);

	MessageBoxA(NULL, s, "1:ProcessC", MB_OK);

	DWORD  dwAProcessId = atoi(argv[2]);
	HANDLE hargB = (HANDLE)atoi(argv[1]);

	HANDLE hProcessA = OpenProcess(PROCESS_DUP_HANDLE,
		FALSE,//FALSE means hProcessB is noninheritable
		dwAProcessId);
	assert(hProcessA);

	HANDLE hBC = 0;

	DuplicateHandle(hProcessA, hargB, GetCurrentProcess(), &hBC, 0,
		FALSE, DUPLICATE_SAME_ACCESS);

	if (TerminateProcess(hBC, 2)) //exit code 2	 
		MessageBox(NULL, TEXT("Inherited ProcessB terminated"), TEXT("2:ProcessC"), MB_OK);
	else
		MessageBox(NULL, TEXT("ProcessB failed to be terminated"), TEXT("2:ProcessC"), MB_OK);

	//CloseHandle(hProcessA);
	CloseHandle(hBC);

	printf("\nHello World! from ProcessC\nPress any key to exit!\n");
	getch();
	return 0;
}

