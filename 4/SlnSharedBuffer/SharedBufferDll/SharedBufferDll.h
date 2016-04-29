// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SHAREDBUFFERDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SHAREDBUFFERDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SHAREDBUFFERDLL_EXPORTS
#define SHAREDBUFFERDLL_API __declspec(dllexport)
#else
#define SHAREDBUFFERDLL_API __declspec(dllimport)
#endif

extern SHAREDBUFFERDLL_API bool bIsMessageInBuffer;
extern SHAREDBUFFERDLL_API WCHAR wcSharedBufferDLL[500];
extern SHAREDBUFFERDLL_API UINT uMsgId;
