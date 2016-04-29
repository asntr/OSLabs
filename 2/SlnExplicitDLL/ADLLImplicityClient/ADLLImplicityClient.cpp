// ADLLImplicityClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int* pv;
	int (*pfn1)(int);
	void (__stdcall* pfn2)(int, int);


	HMODULE hLib = LoadLibraryA("ADLL.dll");
	if (!hLib)
	{
		std::cout << "Error = " << GetLastError() << std::endl;
		system("pause");
		return 1;
	}

	pv = (int*)GetProcAddress(hLib,"nADLL");
	if(pv)
	{
		std::cout << "variable from DLL: " << (*pv) << std::endl;
	}
	else
	{
		std::cout << "Error = " << GetLastError() << std::endl;
		system("pause");
		return 1;
	}

	pfn1 = (int(_cdecl*)(int))GetProcAddress(hLib,"fnADLL");
	if(pfn1)
	{
		std::cout << "result of method fnADLL(5): " << pfn1(5) << std::endl;
	}
	else
	{
		std::cout << "Error = " << GetLastError() << std::endl;
		system("pause");
		return 1;
	}

	//pfn2 = (void(__stdcall*)(int, int))GetProcAddress(hLib,"_MyFunc@8");
	pfn2 = (void(__stdcall*)(int, int))GetProcAddress(hLib,"MyFunc");
	if(pfn2)
	{
		std::cout << "result of method MyFunc(9, 23): ";
		pfn2(9, 23);
	}
	else
	{
		std::cout << "Error = " << GetLastError() << std::endl;
		system("pause");
		return 1;
	}

	FreeLibrary(hLib);

	system("pause");
	return 0;
}

