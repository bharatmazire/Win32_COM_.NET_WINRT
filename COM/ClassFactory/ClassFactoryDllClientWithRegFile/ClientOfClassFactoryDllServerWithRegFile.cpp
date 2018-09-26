#define UNICODE
#include<windows.h>
#include"ClassFactoryDllServerWithRegFile.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

ISum *pISum = NULL;
ISubtract *pISubtract = NULL;

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ClassFactoryClient");
	HRESULT hr;
	// code

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Com Library Can not be initialized.\n Program will exit now."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	// initialization of WNDCLASSEX
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
		TEXT("My Application"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
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
	void SafeInterfaceRelease(void);
	HRESULT hr;
	int iNum1, iNum2, iSum,iSubtract;
	TCHAR str[255];

	//code

	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("ISum Interface Cannot be obtained "), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		iNum1 = 20;
		iNum2 = 10;

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Sum of %d and %d is %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("ISubtract Interface Cannot be obtained "), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISum->Release();
		pISum = NULL;

		iNum1 = 120;
		iNum2 = 100;

		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtract);
		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), iNum1, iNum2, iSubtract);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		pISubtract->Release();
		pISubtract = NULL;
		DestroyWindow(hwnd);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SafeInterfaceRelease(void)
{
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}
}

