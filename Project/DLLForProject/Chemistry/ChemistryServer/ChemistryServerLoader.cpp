#import "ChemistryServer.tlb" no_namespace, raw_interfaces_only
#include "chemistryServer.tlh"

#include<windows.h>
#include"ChemistryServerLoader.h"

IChem *pIChem = NULL;

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
		if (pIChem != NULL)
		{
			pIChem->Release();
			pIChem = NULL;
		}
		CoUninitialize();
		break;
	}
	return(TRUE);
}

void ComInitialize()
{
	if (pIChem)
		return;
	// initializing com
	HRESULT hr = CoInitialize(NULL);
	CLSID clsidChem;
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Com Library Can not be initialized.\n Program will exit now."), TEXT("Program Error"), MB_OK);
		exit(0);
	}
	hr = CLSIDFromProgID(L"ManagedServerForInterop.Chemistry", &clsidChem);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed in getting Clsid from program ID"), TEXT("ERROR"), MB_OK);
		exit(0);
	}

	hr = CoCreateInstance(clsidChem, NULL, CLSCTX_INPROC_SERVER, __uuidof(IChem), (void**)&pIChem);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IChem Interface Cannot be obtained "), TEXT("Error"), MB_OK);
		//DestroyWindow(hwnd);
		return;
	}
	return;
}
extern "C" int ChemistryCalculation(int t, double val1, double val2, double *ret)
{
	/*IChem *pIChem = NULL;
	CLSID clsidChem;*/
	HRESULT hr;
	//// initializing com
	//HRESULT hr = CoInitialize(NULL);
	//
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, TEXT("Com Library Can not be initialized.\n Program will exit now."), TEXT("Program Error"), MB_OK);
	//	exit(0);
	//}
	ComInitialize();
	//hr = CLSIDFromProgID(L"ManagedServerForInterop.Chemistry", &clsidChem);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, TEXT("Failed in getting Clsid from program ID"), TEXT("ERROR"), MB_OK);
	//	exit(0);
	//}

	//hr = CoCreateInstance(clsidChem, NULL, CLSCTX_INPROC_SERVER, __uuidof(IChem), (void**)&pIChem);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, TEXT("IChem Interface Cannot be obtained "), TEXT("Error"), MB_OK);
	//	//DestroyWindow(hwnd);
	//	return -1;
	//}

	MessageBox(NULL,TEXT("Going to calculate"),TEXT("Success"),MB_OK);

	double ans;
	if (t == 1)
	{	// v1 = q1 and v2 = q2
		// fun (w, q1)
		hr = pIChem->HeatCalculation(val1 - val2, val1, &ans);
	}
	else if (t == 2)
	{
		// v1 = q1 and v2 = w
		// fun (q2, w)
		hr = pIChem->RefCalculation(val1 + val2, val2, &ans);
	}
	else
	{
		// v1 = q2 and v2 = w
		// fun (q1 , w)
		hr = pIChem->ACCalculation(val1 + val2, val2, &ans);
	}
	/*pIChem->Release();
	pIChem = NULL;*/

	//// uninitializing com
	//CoUninitialize();

	*ret = ans;
	
	return 0;
}
