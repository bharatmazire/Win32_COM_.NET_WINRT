#define UNICODE

#include<windows.h>
#include<math.h>
#include"MathsDll.h"

class CSideAngle : public ISide, IAngle
{
private:
	long m_cRef;
public:
	CSideAngle(void);
	~CSideAngle(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SidesOfTriangle(double, double, double, double, double, double,int*);
	HRESULT __stdcall AngleOfTriangle(double, double , double, int *);
};

class CSideAngleClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	CSideAngleClassFactory(void);
	~CSideAngleClassFactory(void);

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

#pragma region COCLASS
CSideAngle::CSideAngle(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSideAngle ::~CSideAngle(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CSideAngle::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISide *>(this);
	else if (riid == IID_ISide)
		*ppv = static_cast<ISide *>(this);
	else if (riid == IID_IAngle)
		*ppv = static_cast<IAngle *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSideAngle::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSideAngle::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CSideAngle::SidesOfTriangle(double x1, double y1, double x2, double y2, double x3, double y3, int* pType)
{
	// if value of *pType is -
	// 1 : Equilateral \n 2 : Isosceles \n 3 : right angle \n 4 : Scelenes


	double s1, s2, s3 = 0;
	s1 = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	s2 = sqrt(pow((x3 - x2), 2) + pow((y3 - y2), 2));
	s3 = sqrt(pow((x3 - x1), 2) + pow((y3 - y1), 2));
	
	// check for right angle triangle
	int cond1 = 0;
	int cond2 = 0;
	int cond3 = 0;

	if (pow(s1, 2) + pow(s2, 2) == pow(s3, 2))
		cond1 = 1;
	else if (pow(s1, 2) + pow(s3, 2) == pow(s2, 2))
		cond2 = 1;
	else if (pow(s2, 2) + pow(s3, 2) == pow(s1, 2))
		cond3 = 1;


	if (s1 == s2 && s2 == s3)
		*pType = 1;
	else if (s1 == s2 || s2 == s3 || s3 == s1)
		*pType = 2;
	else if (cond1 || cond2 || cond3)
	{
		*pType = 3;
	}
	else if (s1 != s2 && s2 != s3 && s3 != s1)
		*pType = 4;
	
	return (S_OK);
}

HRESULT CSideAngle::AngleOfTriangle(double a, double b, double c, int* pType)
{
	// if value of *pType is -
	// 1 : Equilateral \n 2 : Isosceles \n 3 : right angle \n 4 : obtuse \n 5.Acute \n 6.Scelenes  \n 7. Wrong input 
	
	if ((a + b + c) != 180 )
		*pType = 7;
	else if (a == b && b == c)
		*pType = 1;
	else if (a == b || b == c || a == c)
		*pType = 2;
	else if (a == 90 || b == 90 || c == 90)
		*pType = 3;
	else if (a > 90 || b > 90 || c > 90)
		*pType = 4;
	else if (a < 90 && b < 90 && c < 90)
		*pType = 5;
	else
		*pType = 6;

	return (S_OK);
}
#pragma endregion

#pragma region CLASSFACTORY

CSideAngleClassFactory::CSideAngleClassFactory(void)
{
	m_cRef = 1;
}

CSideAngleClassFactory :: ~CSideAngleClassFactory(void)
{

}

HRESULT CSideAngleClassFactory::QueryInterface(REFIID riid, void ** ppv)
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

ULONG CSideAngleClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSideAngleClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CSideAngleClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void ** ppv)
{
	CSideAngle *pCSideAngle = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCSideAngle = new CSideAngle;

	if (pCSideAngle == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSideAngle->QueryInterface(riid, ppv);
	pCSideAngle->Release();
	return(hr);
}

HRESULT CSideAngleClassFactory::LockServer(BOOL fLock)
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
	CSideAngleClassFactory *pCSideAngleClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SideAngle)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCSideAngleClassFactory = new CSideAngleClassFactory;
	if (pCSideAngleClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSideAngleClassFactory->QueryInterface(riid, ppv);
	pCSideAngleClassFactory->Release();
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

