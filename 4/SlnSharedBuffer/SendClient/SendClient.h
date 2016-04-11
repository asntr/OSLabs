// SendClient.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "SharedBufferDll.h"

#include "Winuser.h"


// CSendClientApp:
// See SendClient.cpp for the implementation of this class
//

class CSendClientApp : public CWinApp
{
public:
	CSendClientApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSendClientApp theApp;