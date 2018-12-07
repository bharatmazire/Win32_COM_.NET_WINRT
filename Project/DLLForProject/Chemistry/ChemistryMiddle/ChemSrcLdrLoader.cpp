#include<windows.h>
#include"ChemistryServerLoader.h"

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

extern "C" int ChemistryCalculation(int t, double val1, double val2, double *ret)
{
	static HMODULE hLibChem = NULL;
	hLibChem = LoadLibrary(TEXT("ChemistryServerLoader.dll"));
	if (hLibChem == NULL)
	{
		MessageBox(NULL,TEXT("Error \n Chemistry Dll loading falis"),TEXT("ERROR"),MB_OK);
		return (0);
	}

	typedef HRESULT(*pfnChemistryCalculation) (int, double, double, double*); // i guess here return type should be int, instead of HRESULT
	static pfnChemistryCalculation pfnChem = NULL;


		pfnChem = (pfnChemistryCalculation)GetProcAddress(hLibChem, "ChemistryCalculation");
		if (pfnChem == NULL)
		{
			MessageBox(NULL, TEXT("pfnChemistryCalculation LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
		}
		double ans;
		pfnChem(t, val1, val2, &ans);
		*ret = ans;

	FreeLibrary(hLibChem);
	return (0);
}
