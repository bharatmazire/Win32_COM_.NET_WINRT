#import "Chemistry.tlb" no_namespace, raw_interfaces_only
#include "chemistry.tlh"

#include<Windows.h>
#include"MiddleDllChem.h"


class CChemistry : public IChemCalculation
{
private:
	long m_cRef;
public:
	CChemistry(void);
	~CChemistry(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall ChemistryCalculation(int, double, double, double *);
};

class CChemistryClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	CChemistryClassFactory(void);
	~CChemistryClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;


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

#pragma region coclass
CChemistry::CChemistry(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CChemistry ::~CChemistry(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CChemistry::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IChemCalculation *>(this);
	else if (riid == IID_IChemCalculation)
		*ppv = static_cast<IChemCalculation *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CChemistry::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CChemistry::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CChemistry::ChemistryCalculation(int t, double val1, double val2, double *ret)
{
	IChem *pIChem = NULL;
	CLSID clsidChem;
	// initializing com
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Com Library Can not be initialized.\n Program will exit now."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	hr = CLSIDFromProgID(L"ManagedServerForInterop.Chemistry", &clsidChem);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Error while getting CLSID"), TEXT("ERROR"), MB_OK);
		exit(0);
	}
	hr = CoCreateInstance(clsidChem, NULL, CLSCTX_INPROC_SERVER, __uuidof(IChem), (void**)&pIChem);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMath Interface Cannot be obtained "), TEXT("Error"), MB_OK);
		//DestroyWindow(hwnd);
		return -1;
	}
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
	pIChem->Release();
	pIChem = NULL;

	// uninitializing com
	CoUninitialize();
	*ret = ans;

	return hr;
}

#pragma endregion

#pragma region CLASSFACTORY

CChemistryClassFactory::CChemistryClassFactory(void)
{
	m_cRef = 1;
}

CChemistryClassFactory :: ~CChemistryClassFactory(void)
{

}

HRESULT CChemistryClassFactory::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CChemistryClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CChemistryClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CChemistryClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void ** ppv)
{
	CChemistry *pCChemistry = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCChemistry = new CChemistry;

	if (pCChemistry == NULL)
		return(E_OUTOFMEMORY);

	hr = pCChemistry->QueryInterface(riid, ppv);
	pCChemistry->Release();
	return(hr);
}

HRESULT CChemistryClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

#pragma endregion



#pragma region GLOBAL_FUNCTION
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void ** ppv)
{
	CChemistryClassFactory *pCChemistryClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_Chemistry)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCChemistryClassFactory = new CChemistryClassFactory;
	if (pCChemistryClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCChemistryClassFactory->QueryInterface(riid, ppv);
	pCChemistryClassFactory->Release();
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}
#pragma endregion

// old chemcalculation

//extern "C" double ChemCalculation(int t, double val1, double val2)
//{
//	IChem *pIChem = NULL;
//	CLSID clsidChem;
//	// initializing com
//	HRESULT hr = CoInitialize(NULL);
//	if (FAILED(hr))
//	{
//		MessageBox(NULL, TEXT("Com Library Can not be initialized.\n Program will exit now."), TEXT("Program Error"), MB_OK);
//		exit(0);
//	}
//
//	hr = CLSIDFromProgID(L"ManagedServerForInterop.Chemistry", &clsidChem);
//	if (FAILED(hr))
//	{
//		MessageBox(NULL, TEXT("Error while getting CLSID"),TEXT("ERROR"),MB_OK);
//		exit(0);
//	}
//	hr = CoCreateInstance(clsidChem, NULL, CLSCTX_INPROC_SERVER, __uuidof(IChem), (void**)&pIChem);
//	if (FAILED(hr))
//	{
//		MessageBox(NULL, TEXT("IMath Interface Cannot be obtained "), TEXT("Error"), MB_OK);
//		//DestroyWindow(hwnd);
//		return -1;
//	}
//	double ans;
//	if (t == 1)
//	{	// v1 = q1 and v2 = q2
//		// fun (w, q1)
//		hr = pIChem->HeatCalculation(val1 - val2, val1, &ans);
//	}
//	else if (t == 2)
//	{
//		// v1 = q1 and v2 = w
//		// fun (q2, w)
//		hr = pIChem->RefCalculation(val1 - val2 ,val2 , &ans);
//	}
//	else
//	{
//		// v1 = q2 and v2 = w
//		// fun (q1 , w)
//		hr = pIChem->ACCalculation(val1 + val2 ,val2, &ans);
//	}
//	pIChem->Release();
//	pIChem = NULL;
//
//	// uninitializing com
//	CoUninitialize();
//
//	return (ans);
//}