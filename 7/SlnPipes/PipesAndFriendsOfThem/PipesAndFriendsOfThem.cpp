// PipesAndFriendsOfThem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

const char pathFormat[] = "%[^|]|";
const char filePathFormat[] = "%[^>]>";

int CountElements(const char*);
void GetPaths(char* cmd, int count, char **paths, char *outputPath);
void ErrorExit(LPTSTR);
BOOL CreateChildProcess(char* szCommandLine, PROCESS_INFORMATION *ppiProcInfo, HANDLE, HANDLE);

HANDLE *hReadPipes, *hWritePipes,//hReadPipe1, hWritePipe1, hReadPipe2, hWritePipe2, hReadPipe3, hWritePipe3,
	hFile;

PROCESS_INFORMATION *piProcInfos;//piProcInfo1, piProcInfo2, piProcInfo3;

int main(int argc, char* argv[])
{
	if (argc < 1) {
		ErrorExit(TEXT("Not enough arguments!"));
	}

	char cmd[200];
	//scanf_s("%s", cmd, (unsigned)_countof(cmd));
	int count = CountElements(cmd);

	char **paths = new char*[count];
	hReadPipes = new HANDLE[count];
	hWritePipes = new HANDLE[count];
	piProcInfos = new PROCESS_INFORMATION[count];
	char outputPath[100];

	for (int i = 0; i < count; i++) {
		paths[i] = new char[100];
	}

	GetPaths(cmd, count, paths, outputPath);

	SECURITY_ATTRIBUTES sa;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	/*if (!CreatePipe(&hReadPipe1, &hWritePipe1, &sa, 0))
	{
		ErrorExit(TEXT("Pipe creation failed :("));
	}

	if (!CreatePipe(&hReadPipe2, &hWritePipe2, &sa, 0))
	{
		ErrorExit(TEXT("Pipe creation failed :("));
	}

	if (!CreatePipe(&hReadPipe3, &hWritePipe3, &sa, 0))
	{
		ErrorExit(TEXT("Pipe creation failed :("));
	}*/

	for (int i = 0; i < count; i++) {
		if (!CreatePipe(&hReadPipes[i], &hWritePipes[i], &sa, 0))
		{
			ErrorExit(TEXT("Pipe creation failed :("));
		}
	}

	for (int j = 10; j < 20; j++)
	{
		DWORD dwBytesWritten;
		if (!WriteFile(
			hWritePipes[0],
			&j,
			sizeof(j),
			&dwBytesWritten,
			NULL))
		{
			ErrorExit(TEXT("holy shit!"));
		}
		_cprintf("The number %d is written to the pipe.\n", j);
	}

	CloseHandle(hWritePipes[0]);

	/*if (!CreateChildProcess(paths[0], &piProcInfo2, hReadPipe1, hWritePipe2))
	{
		ErrorExit(TEXT("Process creation failed"));
	}

	CloseHandle(hWritePipe2);

	CloseHandle(hReadPipe1);

	if (!CreateChildProcess(paths[1], &piProcInfo2, hReadPipe2, hWritePipe3))
	{
		ErrorExit(TEXT("Process creation failed"));
	}

	CloseHandle(hWritePipe3);

	CloseHandle(hReadPipe2);*/

	for (int i = 0; i < count - 1; i++)
	{
		if (!CreateChildProcess(paths[i], &piProcInfos[i], hReadPipes[i], hWritePipes[i+1]))
		{
			ErrorExit(TEXT("Process creation failed"));
		}

		CloseHandle(hWritePipes[i + 1]);

		CloseHandle(hReadPipes[i]);
	}

	SECURITY_ATTRIBUTES saAttr;

	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	hFile = CreateFileA(outputPath,
		GENERIC_READ | GENERIC_WRITE,
		0,//not shared,  for only one process
		&saAttr,//can be inherited 
		CREATE_ALWAYS,//OPEN_ALWAYS - not clean  the old contents
		FILE_ATTRIBUTE_ARCHIVE,
		NULL); //always for Windows-95

	if (!CreateChildProcess(paths[count - 1], &piProcInfos[count - 1], hReadPipes[count - 1], hFile))
	{
		ErrorExit(TEXT("Process creation failed"));
	}

	CloseHandle(hReadPipes[count - 1]);

	/*CloseHandle(piProcInfo2.hProcess);
	CloseHandle(piProcInfo2.hThread);

	CloseHandle(piProcInfo1.hProcess);
	CloseHandle(piProcInfo1.hThread);

	CloseHandle(piProcInfo3.hProcess);
	CloseHandle(piProcInfo3.hThread);*/

	for (int i = 0; i < count; i++)
	{
		CloseHandle(piProcInfos[i].hProcess);
		CloseHandle(piProcInfos[i].hThread);
	}

	system("pause");
}

int CountElements(const char* cmd) 
{
	int counter = 0;
	const char *ptr;
	ptr = strchr(cmd, '|');
	while (ptr != NULL) {
		counter++;
		ptr = strchr(ptr+1, '|');
	}
	return counter;
}

void GetPaths(char* cmd, int count, char **paths, char *outputPath) 
{
	char *ptrToNext = cmd;
	for (int i = 0; i < count; i++) {
		sscanf(ptrToNext, pathFormat, paths[i]);
		ptrToNext = strchr(ptrToNext, '|');
		ptrToNext++;
	}
	sscanf(ptrToNext, filePathFormat, outputPath);
}

void ErrorExit(LPTSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);
	system("pause");
	ExitProcess(1);
}

BOOL CreateChildProcess(char * szCommandLine, PROCESS_INFORMATION * ppiProcInfo)
{
	return 0;
}

BOOL CreateChildProcess(char* szCommandLine, PROCESS_INFORMATION *ppiProcInfo, HANDLE hRead, HANDLE hWrite)
{
	STARTUPINFOA si;

	ZeroMemory(&si, sizeof(STARTUPINFOA));
	si.cb = sizeof(STARTUPINFOA);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = hRead;
	si.hStdOutput = hWrite;
	si.hStdError = hWrite;

	ZeroMemory(ppiProcInfo, sizeof(PROCESS_INFORMATION));

	return CreateProcessA(NULL, szCommandLine, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, ppiProcInfo);
}

