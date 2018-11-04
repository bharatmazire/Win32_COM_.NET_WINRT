#include<windows.h>
#include"MiddleDll.h"
#include"MathsDll.h"


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

extern "C" HRESULT SidesOfTriangle(double x1, double y1, double x2, double y2, double x3, double y3, int* pType)
{
	ISide *pISide = NULL;

	// initializing com
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Com Library Can not be initialized.\n Program will exit now."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	hr = CoCreateInstance(CLSID_SideAngle, NULL, CLSCTX_INPROC_SERVER, IID_ISide, (void**)&pISide);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("ISide Interface Cannot be obtained "), TEXT("Error"), MB_OK);
		//DestroyWindow(hwnd);
		return -1;
	}

	pISide->SidesOfTriangle(x1, y1, x2, y2, x3, y3, pType);
	pISide->Release();
	pISide = NULL;

	// uninitializing com
	CoUninitialize();

	return (S_OK);
}

extern "C" HRESULT AngleOfTriangle(double a, double b, double c, int* pType)
{
	IAngle *pIAngle = NULL;
	
	// initializing com
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Com Library Can not be initialized.\n Program will exit now."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	hr = CoCreateInstance(CLSID_SideAngle, NULL, CLSCTX_INPROC_SERVER, IID_IAngle, (void**)&pIAngle);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IAngle Interface Cannot be obtained "), TEXT("Error"), MB_OK);
		//DestroyWindow(hwnd);
		return -1;
	}

	pIAngle->AngleOfTriangle(a, b, c, pType);
	pIAngle->Release();
	pIAngle = NULL;

	// uninitializing com
	CoUninitialize();

	return (S_OK);
}

