#import "Chemistry.tlb" no_namespace, raw_interfaces_only
#include "Debug/chemistry.tlh"
#include<windows.h>
#include<stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("CCW COM CLIENT");
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library Can not be Initialized.\n Program will now exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register above class
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("CCW COM CLIENT"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CoUninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void ComErrorDescriptionString(HWND, HRESULT);

	HRESULT hr;
	long iNum1, iNum2, iMultiply, iDivision;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
	{
		CLSID clsidChem;
		iNum1 = 10;
		iNum2 = 10;
		iMultiply = 0;
		iDivision = 0;

		IChem *app; // for auto.dual = _Math *app

		hr = CLSIDFromProgID(L"ManagedServerForInterop.Chemistry", &clsidChem);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("Bro I did't get clsid out there"), TEXT("Msg from hr"),MB_OK);
			ComErrorDescriptionString(hwnd, hr);
			DestroyWindow(hwnd);
		}

		hr = CoCreateInstance(clsidChem, NULL, CLSCTX_INPROC_SERVER, __uuidof(IChem), (void **)&app);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("Here is common msg\n I am unable to create instance, i  think\n registration not done...\n GOOD LUCK"), TEXT("Msg from co create instance ..."), MB_OK);
			ComErrorDescriptionString(hwnd, hr);
			DestroyWindow(hwnd);
		}

		int t = rand() % 3+1;
		double val1 = rand() % 100;
		double val2 = rand() % 100;

		double ans;
		if (t == 1)
		{	// v1 = q1 and v2 = q2
			// fun (w, q1)
			hr = app->HeatCalculation(val1 - val2, val1, &ans);
		}
		else if (t == 2)
		{
			hr = app->RefCalculation(val1 + val2, val2, &ans);
		}
		else
		{
			hr = app->ACCalculation(val1 + val2, val2, &ans);;
		}

		wsprintf(str, TEXT("%d of %d and %d is %d "), t, val1, val2, ans);
		MessageBox(hwnd, str, TEXT("Heat calculation"), MB_OK);
		app->Release();
		app = NULL;

		CoUninitialize();
		DestroyWindow(hwnd);
	}
	break;
	case WM_DESTROY:
		//SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	TCHAR *szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&szErrorMessage, 0, NULL) != 0)
	{
		wsprintf(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
		wsprintf(str, TEXT("[Could not find a description for error # %#x.]\n"), hr);

	MessageBox(hwnd, str, TEXT("COM ERROR"), MB_OK);
}
