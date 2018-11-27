#include<Windows.h>
#include"MiddleDllChem.h"
#include "MiddleDllChemDll.h"

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


extern "C" HRESULT ChemistryCalculation(int t, double val1, double val2, double *ret)
{
	IChemCalculation * pIChemCalculation = NULL;

	// initializing com
	HRESULT hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Com Library Can not be initialized.\n Program will exit now."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	hr = CoCreateInstance(CLSID_Chemistry, NULL, CLSCTX_INPROC_SERVER, IID_IChemCalculation, (void**)&pIChemCalculation);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("ISide Interface Cannot be obtained "), TEXT("Error"), MB_OK);
		//DestroyWindow(hwnd);
		return -1;
	}

	pIChemCalculation->ChemistryCalculation(t,val1,val2,ret);
	pIChemCalculation->Release();
	pIChemCalculation = NULL;

	// uninitializing com
	CoUninitialize();

	return (S_OK);
}
