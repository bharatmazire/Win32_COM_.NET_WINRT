#include<windows.h>
#include"MiddleDllChemDll.h"

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

extern "C" HRESULT ChemistryCalculation(int t, double v1, double v2, double *ret)
{
	static HMODULE hLibChem = LoadLibrary(TEXT("ChemistryDef.dll"));
	if (hLibChem == NULL)
	{
		MessageBox(NULL, TEXT("Chemistry Dll Loading Fails !!"), TEXT("ERROR"), MB_OK);
		exit(0);
	}

	typedef HRESULT(*pfnChemistryCalculation) (int, double, double, double*);
	static pfnChemistryCalculation pfnChem = NULL;


	pfnChem = (pfnChemistryCalculation)GetProcAddress(hLibChem, "ChemistryCalculation");
	if (pfnChem == NULL)
	{
		MessageBox(NULL, TEXT("pfnChemistryCalculation LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
		exit(0);
	}

	pfnChem(t, v1, v2, ret);


	return (HRESULT)0;
}