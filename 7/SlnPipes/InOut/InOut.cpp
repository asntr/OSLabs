// InOut.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	int c, n = 0;
	while ((c = getc(stdin)) != EOF) {
		putc(c, stdout);
		putc(c, stdout);
	}
}

