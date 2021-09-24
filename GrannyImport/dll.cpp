#include "includes.h"

extern ClassDesc2* GetGrannyImportDesc();
extern ClassDesc2* GetGrannyExportDesc();
HINSTANCE hInstance ;
BOOL WINAPI DllMain(HINSTANCE hinstDLL, ULONG fdwReason, LPVOID /*lpvReserved*/)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		// Hang on to this DLL's instance handle.
		hInstance = hinstDLL;
		DisableThreadLibraryCalls(hInstance);
	}
	return(TRUE);
}

__declspec(dllexport)  const TCHAR* LibDescription()
{
	return (TCHAR*)"Granny Import/Export";
}
__declspec(dllexport)  int LibNumberClasses()
{
	return 2;
}
__declspec(dllexport)  ClassDesc* LibClassDesc(int i)
{
	switch (i) 
	{
	case 0: return GetGrannyImportDesc();
	case 1: return GetGrannyExportDesc();
	//case 2: return GetmaxniftoolsexporterDesc();
	default: return 0;
	}
}
__declspec(dllexport)  ULONG LibVersion()
{
	return VERSION_3DSMAX;
}
__declspec(dllexport)  int LibInitialize(void)
{
	return TRUE;
}
__declspec(dllexport)  int LibShutdown(void)
{
	return TRUE;
}

TCHAR* GetString(int id)
{
	static TCHAR buf[256];

	if (hInstance)
		return LoadString(hInstance, id, buf, sizeof(buf)) ? buf : NULL;
	return NULL;
}
