// ProcessA.cpp : Defines the entry point for the application.
// No use of env. variables
// No use of the handle inheritance flag because B's handle is not inheritable.

#include "stdafx.h"
#include <stdio.h>

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{

	// Prepare a STARTUPINFO structure for spawning processes.
	STARTUPINFO si = { sizeof(si) };
	SECURITY_ATTRIBUTES saProcess, saThread;
	PROCESS_INFORMATION piProcessB, piProcessC;
	TCHAR szPath[MAX_PATH];

	// Prepare to spawn Process B from Process A.
	// The handle identifying the new process 
	// object should NOT be inheritable.
	saProcess.nLength = sizeof(saProcess);
	saProcess.lpSecurityDescriptor = NULL;
	saProcess.bInheritHandle = FALSE; //noninheritable //TRUE;         //INHERITABLE

									  // The handle identifying the new thread 
									  // object should NOT be inheritable.
	saThread.nLength = sizeof(saThread);
	saThread.lpSecurityDescriptor = NULL;
	saThread.bInheritHandle = FALSE;  //NOT INHERITABLE   //TRUE;     

									  // Spawn Process B.
	lstrcpy(szPath, TEXT("ProcessB"));

	if (!CreateProcess(NULL, szPath, &saProcess, &saThread,
		FALSE, //B inherits nothing from A
		0,
		NULL, NULL, &si, &piProcessB)) {
		MessageBox(NULL, TEXT("ProcessB failed"), TEXT("1:ProcessA"), MB_OK);
		return(0);
	};

	////??   CloseHandle(piProcessB.hProcess);
	////??   CloseHandle(piProcessB.hThread);

	// The pi structure contains two handles 
	// relative to Process A:
	// pi.hProcess, which identifies Process B's process object and is NOT inheritable; and 
	// pi.hThread,  which identifies Process B's primary thread object and is NOT inheritable.

	// Prepare to spawn Process C from Process A.
	// Since NULL is passed for the " psaProcess and psaThread "
	// parameters, the handles to Process C's process and 
	// primary thread objects default to "noninheritable."

	// If Process A were to spawn another process, this new 
	// process would NOT inherit handles to Process C's process 
	// and thread objects.

	// Because TRUE is passed for the bInheritHandles parameter,
	// Process C will inherit the handle that identifies Process 
	// B's process object but will not inherit a handle to 
	// Process B's primary thread object.

	//lstrcpy(szPath, TEXT("ProcessC"));

	//A has pidA and piProcessB.hProcess to hand in C
	DWORD dwApid = GetCurrentProcessId();
	wsprintf(szPath, TEXT("ProcessC %i %i"), piProcessB.hProcess, dwApid);

	//C inherits nothing from A but it will receive	through the command string hB and Apid.
	//It does not  matter that the handle inheritance flag is set to TRUE.    
	if (!CreateProcess(
		NULL, szPath, NULL, NULL,
		TRUE,//  suitable   FALSE too
		NORMAL_PRIORITY_CLASS | CREATE_SUSPENDED,
		NULL, NULL, &si, &piProcessC))
	{ // hProcessB 
		MessageBox(NULL, TEXT("ProcessC failed"), TEXT("1:ProcessA"), MB_OK);
		return(0);
	};
	// TODO: Place code here.
	Sleep(5000);

	if (1 == ResumeThread(piProcessC.hThread))

	{
		Sleep(5000);

		MessageBox(NULL, TEXT("ProcessC resumed"), TEXT("1:ProcessA"), MB_OK);
	}

	if (WAIT_FAILED == WaitForSingleObject(piProcessB.hProcess, INFINITE)) {
		MessageBox(NULL, TEXT("WAIT_FAILED for ProcessB "), TEXT("1:ProcessA"), MB_OK);
	};

	if (WAIT_FAILED == WaitForSingleObject(piProcessC.hProcess, INFINITE))
	{
		MessageBox(NULL, TEXT("WAIT_FAILED for ProcessC"), TEXT("2:ProcessA"), MB_OK);
	};

	CloseHandle(piProcessB.hProcess);
	CloseHandle(piProcessB.hThread);

	CloseHandle(piProcessC.hProcess);
	CloseHandle(piProcessC.hThread);
	MessageBox(NULL, TEXT("ProcessA finished"), TEXT("2:ProcessA"), MB_OK);
	return 0;
}



