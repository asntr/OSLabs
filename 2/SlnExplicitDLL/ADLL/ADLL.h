// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ADLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ADLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ADLL_EXPORTS
#define ADLL_API __declspec(dllexport)
#else
#define ADLL_API __declspec(dllimport)
#endif

// This class is exported from the ADLL.dll
class ADLL_API CADLL {
private:
	int left;
	int right;
public:
	CADLL(int, int);
	int getSum(void);
	int getProduct(void);
};

extern "C" ADLL_API int nADLL;

extern "C" ADLL_API int fnADLL(int);

extern "C" ADLL_API void __stdcall MyFunc(int a, int b);
