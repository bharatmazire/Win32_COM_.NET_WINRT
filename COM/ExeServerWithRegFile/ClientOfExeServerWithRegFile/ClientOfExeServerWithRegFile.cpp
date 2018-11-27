#define UNICODE

#include<windows.h>
#include<process.h>
#include"ExeServerWithRegFile.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	// variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("Client");
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
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register above class
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(AppName,
		TEXT("Client Of Exe Server"),
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
	//CoUninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	ISum *pISum = NULL;
	ISubtract *pISubtract = NULL;
	HRESULT hr;
	int error, n1, n2, n3;
	TCHAR szWinSysDir[255];
	static TCHAR szPath[_MAX_PATH];
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		GetSystemDirectory(szWinSysDir, 255);
		wsprintf(szPath, TEXT("%s\\regsvr32.exe"), szWinSysDir);
		error = _wspawnlp(P_WAIT, szPath, szPath, TEXT("/s"), TEXT("ProxyStub.dll"), NULL);
		if (error == -1)
		{
			MessageBox(hwnd, TEXT("ProxyStub Dll can not be registered"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}
		
		hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("COM Library can not be initialized"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}

		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_LOCAL_SERVER, IID_ISum, (void **)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("Component can be created"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}
		n1 = 25;
		n2 = 5;
		pISum->SumOfTwoIntegers(n1, n2, &n3);
		wsprintf(str, TEXT("Sum of %d and %d is %d"), n1, n2, n3);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("ISubtract Interface Cannot be obtained "), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISum->Release();
		pISum = NULL;
		
		pISubtract->SubtractionOfTwoIntegers(n1, n2, &n3);
		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), n1, n2, n3);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		pISubtract->Release();
		pISubtract = NULL;
		DestroyWindow(hwnd);

		break;

	case WM_DESTROY:
		CoUninitialize();
		error = _wspawnlp(P_WAIT, szPath, szPath, TEXT("/u"), TEXT("/s"), TEXT("ProxyStub.dll"), NULL);
		if (error == -1)
			MessageBox(hwnd, TEXT("ProxyStub Dll not be un-registerd"), TEXT("Error"), MB_OK);
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
