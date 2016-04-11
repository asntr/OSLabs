// ADLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ADLL.h"
#include <iostream>


// This is an example of an exported variable
ADLL_API int nADLL = 2016;

// This is an example of an exported function.
ADLL_API int fnADLL(int arg)
{
	return arg*arg;
}

// This is the constructor of a class that has been exported.
// see ADLL.h for the class definition
CADLL::CADLL(int a, int b)
{
	left = a;
	right = b;
}

int CADLL::getSum() 
{
	return left+right;
}

int CADLL::getProduct()
{
	return left*right;
}

void _stdcall MyFunc(int a, int b)
{
	std::cout << a << " " << b << std::endl;
}