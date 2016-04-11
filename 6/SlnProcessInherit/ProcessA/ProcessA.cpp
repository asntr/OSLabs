#include "stdafx.h"

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{

	// Prepare a STARTUPINFO structure for spawning processes.
	STARTUPINFO         si = { sizeof(si) };
	SECURITY_ATTRIBUTES saProcess,
		saThread;
	PROCESS_INFORMATION piProcessB,
		piProcessC;
	TCHAR szPath[MAX_PATH];

	// Prepare to spawn Process B from Process A.
	// The handle identifying the new process object is to be INHERITABLE.

	saProcess.nLength = sizeof(saProcess);
	saProcess.lpSecurityDescriptor = NULL;
	saProcess.bInheritHandle = TRUE;  // TRUE means INHERITABLE //FALSE NOT INHERITABLE   

									  // The handle identifying the new thread object is NOT to be INHERITABLE.

	saThread.nLength = sizeof(saThread);
	saThread.lpSecurityDescriptor = NULL;
	saThread.bInheritHandle = FALSE;    //NOT INHERITABLE    //TRUE  means INHERITABLE

										// Spawn Process B.
										//The handle returned by the CreateProcess function
										// always  has PROCESS_ALL_ACCESS access to the process object.
										//The current directory specified by the lpcurrentDirectory parameter
										//    is the current directory for the child process.
										//The current directory specified in item 2 under the lpCommandLine parameter
										//    is the current directory for the parent process.

	lstrcpy(szPath, TEXT("ProcessB"));

	// CREATE ProcessB
	if (!CreateProcess(NULL, szPath, //Command  line
		&saProcess, &saThread,
		FALSE, //B inherits nothing from A, TRUE is suitable too.
		0,	  //Creation Flags: priority , suspended, er. mode, detached console ...
			  //0 means NORMAL_PRIORITY_CLASS and not suspendid ... by default.
		NULL,  //Env. block from A
		NULL,  //Current dir. from A. So it is  defined by the command line in this call
		&si,   // Specifies the main window appearence(by default in this call)
		&piProcessB))
	{
		MessageBox(NULL, TEXT("ProcessB failed"), TEXT("1:ProcessA"), MB_OK);
		return(0);
	};

	//?????  CloseHandle(piProcessB.hProcess);
	//CloseHandle(piProcessB.hThread);

	TCHAR BprocessID[100], BprocessHandler[100];

	wsprintf(BprocessID, TEXT("%i"), piProcessB.dwProcessId);
	wsprintf(BprocessHandler, TEXT("%i"), piProcessB.hProcess);

	SetEnvironmentVariableW(TEXT("PBID"), BprocessID);
	SetEnvironmentVariableW(TEXT("PBHANDLER"), BprocessHandler);
	swprintf(szPath, TEXT("ProcessC"));
	// CREATE ProcessC

	if (!CreateProcess(
		NULL, szPath,

		NULL, NULL,//BOTH C's HANDLES are NOT INHERITABLE
		TRUE,// FALSE would mean that C has NOTHING inherit  from A 
			 // TRUE means C inherits B's handle!

		NORMAL_PRIORITY_CLASS | CREATE_SUSPENDED,
		NULL, NULL,
		&si, &piProcessC))
	{
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

	//Wait for Terminating Process B

	if (WAIT_FAILED == WaitForSingleObject(piProcessB.hProcess, INFINITE))
	{
		MessageBox(NULL, TEXT("WAIT_FAILED for ProcessB"), TEXT("2:ProcessA"), MB_OK);
	};
	//Wait for Finishing Process C

	if (WAIT_FAILED == WaitForSingleObject(piProcessC.hProcess, INFINITE))
	{
		MessageBox(NULL, TEXT("WAIT_FAILED for ProcessC"), TEXT("2:ProcessA"), MB_OK);
	};

	CloseHandle(piProcessB.hProcess);
	CloseHandle(piProcessB.hThread);

	CloseHandle(piProcessC.hProcess);
	CloseHandle(piProcessC.hThread);

	SetEnvironmentVariableA("PBID", NULL);
	SetEnvironmentVariableA("PBHANDLER", NULL);

	MessageBox(NULL, TEXT("ProcessA finished"), TEXT("2:ProcessA"), MB_OK);

	return 0;
}



