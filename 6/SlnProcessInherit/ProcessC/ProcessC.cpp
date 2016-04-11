#include "stdafx.h"
#include <stdlib.h>
#include <conio.h>
#include <assert.h>
int main(int argc, char* argv[])
{
	char szIdValue[200], szHandlerValue[200];
	DWORD lenValue = GetEnvironmentVariableA("PBID", szIdValue, sizeof(szIdValue));

	if (!lenValue) {
		perror("The variable PBID was not found!");
		return 1;
	};
	
	lenValue = GetEnvironmentVariableA("PBHANDLER", szHandlerValue, sizeof(szHandlerValue));

	if (!lenValue) {
		perror("The variable HANDLE_PARENT was not found!");
		return 1;
	};

	char s[256];
	sprintf(s, "ProcessC resumed by ProcessA, hProcessB = %s, B's PID = %s",
		szIdValue, szHandlerValue);

	MessageBoxA(NULL, s, "1:ProcessC", MB_OK);

	DWORD  dwBProcessId = atoi(szIdValue);
	HANDLE hargB = (HANDLE)atoi(szHandlerValue);

	HANDLE hProcessB = OpenProcess(PROCESS_DUP_HANDLE,
		FALSE,//FALSE means hProcessB is noninheritable
		dwBProcessId);
	assert(hProcessB);
	assert(hProcessB != hargB);

	if (TerminateProcess(hargB, 2)) //exit code 2	 
		MessageBox(NULL, TEXT("Inherited ProcessB terminated"), TEXT("2:ProcessC"), MB_OK);
	else
		MessageBox(NULL, TEXT("ProcessB failed to be terminated"), TEXT("2:ProcessC"), MB_OK);

	CloseHandle(hargB);
	CloseHandle(hProcessB);

	printf("\nHello World! from ProcessC\nPress any key to exit!\n");
	getch();
	return 0;
}



