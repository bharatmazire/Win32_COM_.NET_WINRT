#define UNICODE
#include<windows.h>
#include"ClassFactoryDllServerWithRegFile.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

ISum *pISum = NULL;
ISubtract *pISubtract = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("MY CLASS FACTORY ASSIGNMENT 1");
	HWND hwnd;
	MSG msg;
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("INITIALIZATION FAILD"), TEXT("PROGRAM ERROR"), MB_OK);
		exit(0);
	}



	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	
	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL, TEXT("CLASS REGISTRATION FAILD"), TEXT("PROGRAM ERROR"), MB_OK);
		exit(0);
	}
	
	hwnd = CreateWindow(szAppName, TEXT("MyClasFactoryClient"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void SafeInterfaceRelease(void);
	//MessageBox(NULL, TEXT("IN WNDPROC"), TEXT("MSG"), MB_OK);
	HRESULT hr;
	int iNum1, iNum2, iSum;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		MessageBox(NULL, TEXT("IN WM_CREATE"), TEXT("MSG"), MB_OK);
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum interface cannot be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		MessageBox(NULL, TEXT("Done with cocreateinstance"), TEXT("MSG"), MB_OK);
		iNum1 = 10;
		iNum2 = 20;

		pISum->SumOfTwoIntergers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Sum of %d and %d is %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract interface cannot be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISum->Release();
		pISum = NULL;

		iNum1 = 100;
		iNum2 = 90;

		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSum);
		pISubtract->Release();
		pISubtract = NULL;

		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);
		
		DestroyWindow(hwnd);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
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