#define UNICODE

#include<windows.h>
#include<tlhelp32.h>
#include"ExeServerWithRegFile.h"

HRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class CSumSubtract :public ISum, ISubtract
{
private:
	long m_cRef;
public:
	CSumSubtract(void);
	~CSumSubtract(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwoIntegers(int, int, int *);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *);
};

class CSumSubtractClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	CSumSubtractClassFactory(void);
	~CSumSubtractClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;
IClassFactory *gpIClassFactory = NULL;
HWND ghwnd = NULL;
DWORD dwRegister;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	HRESULT StartMyClassFactories(void);
	void StopMyClassFactories(void);
	DWORD GetParentProcessID(void);

	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	HRESULT hr;
	int iDontShowWindow = 0;
	TCHAR AppName[] = TEXT("ExeServer");
	TCHAR szTokens[] = TEXT("-/");
	TCHAR *pszTokens;
	TCHAR lpszCmdLine[255];
	wchar_t *next_token = NULL;

	GetCurrentProcessId();

	hr = CoInitialize(NULL);
	if (FAILED(hr))
		return(0);

	MultiByteToWideChar(CP_ACP, 0, lpCmdLine, 255, lpszCmdLine, 255);
	pszTokens = wcstok_s(lpszCmdLine, szTokens, &next_token);

	while (pszTokens != NULL)
	{
		if (_wcsicmp(pszTokens, TEXT("Embedding")) == 0)
		{
			iDontShowWindow = 1;
			break;
		}
		else
		{
			MessageBox(NULL, TEXT("Bad Command Line Arguments.\nExiting the Application"), TEXT("Error"), MB_OK);
			exit(0);
		}
		pszTokens = wcstok_s(NULL, szTokens, &next_token);
	}

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName, TEXT("Exe Server With Reg File"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ghwnd = hwnd;

	if (iDontShowWindow != 1)
	{
		ShowWindow(hwnd, iCmdShow);
		UpdateWindow(hwnd);
		++glNumberOfServerLocks;
	}
	
	if (iDontShowWindow == 1)
	{
		hr = StartMyClassFactories();

		if (FAILED(hr))
		{
			DestroyWindow(hwnd);
			exit(0);
		}
	}

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (iDontShowWindow == 1)
	{
		StopMyClassFactories();
	}

	CoUninitialize();
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;

	switch (iMsg)
	{
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(0, 255, 0));
		DrawText(hdc, TEXT("This is a Com Exe server program, Not for you !!"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
			PostQuitMessage(0);
		break;
	case WM_CLOSE:
		--glNumberOfServerLocks;
		ShowWindow(hwnd, SW_HIDE);
		break;
	default:
		return(DefWindowProc(hwnd, iMsg, wParam, lParam));
	}
	return (0L);
}

CSumSubtract::CSumSubtract(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract ::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtract::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
			PostMessage(ghwnd,WM_QUIT,(WPARAM)0,(LPARAM)0L);
		return(0);
	}
	return(m_cRef);
}

HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int * pSum)
{
	*pSum = num1 + num2;
	return (S_OK);
}

HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int * pSubtraction)
{
	*pSubtraction = num1 - num2;
	return (S_OK);
}

CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cRef = 1;
}

CSumSubtractClassFactory :: ~CSumSubtractClassFactory(void)
{

}

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void ** ppv)
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

ULONG CSumSubtractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void ** ppv)
{
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCSumSubtract = new CSumSubtract;

	if (pCSumSubtract == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	return(hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		PostMessage(ghwnd, WM_QUIT, (WPARAM)0, (LPARAM)0L);
	
	return(S_OK);
}

HRESULT StartMyClassFactories(void)
{
	HRESULT hr;

	gpIClassFactory = new CSumSubtractClassFactory;
	if (gpIClassFactory == NULL)
		return(E_OUTOFMEMORY);

	gpIClassFactory->AddRef();

	hr = CoRegisterClassObject(CLSID_SumSubtract, static_cast<IUnknown *>(gpIClassFactory), CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &dwRegister);
	if (FAILED(hr))
	{
		gpIClassFactory->Release();
		return(E_FAIL);
	}
	return(S_OK);
}

void StopMyClassFactories(void)
{
	if (dwRegister != 0)
		CoRevokeClassObject(dwRegister);

	if (gpIClassFactory != NULL)
		gpIClassFactory->Release();
}

DWORD GetParentProcessID(void)
{
	HANDLE hProcessSnapshot = NULL;
	BOOL bRetCode = FALSE;
	PROCESSENTRY32 ProcessEntry = { 0 };
	DWORD dwPPID;
	TCHAR szNameOfThisProcess[_MAX_PATH];
	//TCHAR szNameOfParentProcess[_MAX_PATH];
	TCHAR szTemp[_MAX_PATH], str[_MAX_PATH], *ptr = NULL;

	hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnapshot == INVALID_HANDLE_VALUE)
		return(-1);

	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessSnapshot, &ProcessEntry))
	{
		GetModuleFileName(NULL, szTemp, _MAX_PATH);
		ptr = wcsrchr(szTemp, '\\');
		wcscpy_s(szNameOfThisProcess, ptr + 1);
		do
		{
			errno_t err;
			err = _wcslwr_s(szNameOfThisProcess, wcslen(szNameOfThisProcess) + 1);
			err = _wcsupr_s(ProcessEntry.szExeFile, wcslen(ProcessEntry.szExeFile) + 1);

			if (wcsstr(szNameOfThisProcess, ProcessEntry.szExeFile) != NULL)
			{
				wsprintf(str, TEXT("Current Process Name = %s\nCurrent Process Id = %ld\nParent Process Name = %s\nParent Process Id = %ld"), szNameOfThisProcess, ProcessEntry.th32ProcessID, ProcessEntry.szExeFile, ProcessEntry.th32ParentProcessID);
				MessageBox(NULL, str, TEXT("Parent Info"), MB_OK | MB_TOPMOST);
				dwPPID = ProcessEntry.th32ParentProcessID;
			}
		} while (Process32Next(hProcessSnapshot, &ProcessEntry));
		
	}
	CloseHandle(hProcessSnapshot);
	return(dwPPID);
}
