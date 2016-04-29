// SharedBufferDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SharedBufferDll.h"

#pragma data_seg("SharedSection")
  SHAREDBUFFERDLL_API bool bIsMessageInBuffer = false;
  SHAREDBUFFERDLL_API WCHAR wcSharedBufferDLL[500]= {0,};
  SHAREDBUFFERDLL_API UINT uMsgId = 0;
#pragma data_seg()

#pragma comment(linker,"/Section:SharedSection,RWS")