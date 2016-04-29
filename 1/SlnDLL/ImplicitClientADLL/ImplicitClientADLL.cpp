// ImplicitClientADLL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ADLL.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << nADLL << std::endl;
	std::cout << fnADLL(5) << std::endl;
	CADLL a(-5, 5);
	std::cout << a.getSum() << std::endl;
	std::cout << a.getProduct() << std::endl;
	system("pause");
}

