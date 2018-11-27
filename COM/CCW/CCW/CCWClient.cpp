#import "Math.tlb" no_namespace, raw_interfaces_only
#include "Debug\math.tlh"

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
		CLSID clsidMath;
		iNum1 = 10;
		iNum2 = 10;
		iMultiply = 0;
		iDivision = 0;
		
		IMath *app; // for auto.dual = _Math *app

		hr = CLSIDFromProgID(L"ManagedServerForInterop.Math", &clsidMath);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			DestroyWindow(hwnd);
		}

		hr = CoCreateInstance(clsidMath, NULL, CLSCTX_INPROC_SERVER, __uuidof(IMath), (void **)&app);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			DestroyWindow(hwnd);
		}

		hr = app->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMultiply);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			DestroyWindow(hwnd);
		}
		wsprintf(str, TEXT("Multiplication of %d and %d is %d "), iNum1, iNum2, iMultiply);
		MessageBox(hwnd, str, TEXT("Multiplication Of Two Integers "), MB_OK);


		hr = app->DivisionOfTwoIntegers(iNum1, iNum2, &iDivision);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			DestroyWindow(hwnd);
		}

		wsprintf(str, TEXT("Division of %d and %d is %d "), iNum1, iNum2, iDivision);
		MessageBox(hwnd, str, TEXT("Division Of Two Integers "), MB_OK);

		DestroyWindow(hwnd);
	}
		break;
	case WM_DESTROY:
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
