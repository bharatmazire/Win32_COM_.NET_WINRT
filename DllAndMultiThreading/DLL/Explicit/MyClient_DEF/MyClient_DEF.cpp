#include<windows.h>
//#include"MyDll_DEF.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("MY DLL WINDOW TWO");
	HWND hwnd;
	MSG msg;

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("MY EXPLICIT DLL WINDOW"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	static HMODULE hLib = NULL;
	typedef int(* pfnMakeSquare) (int);
	pfnMakeSquare pfn = NULL;

	static int iNum = 0;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		hLib = LoadLibrary(TEXT("MyDll_DEF.dll"));
		if (hLib == NULL)
		{
			MessageBox(hwnd, TEXT("DLL LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		//else
		//{
		//	MessageBox(hwnd, TEXT("DLL LOADING Successfull !!"), TEXT("NO ERROR"), MB_OK);
		//}

		break;

	case WM_LBUTTONDOWN:
		iNum = iNum + 1;
		pfn = (pfnMakeSquare)GetProcAddress(hLib, "MySquareDef");
		//if (pfn == NULL)
		//{
		//	MessageBox(hwnd, TEXT("Function LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
		//	DestroyWindow(hwnd);
		//}
		//else
		//{
		//	MessageBox(hwnd, TEXT("Function LOADING Successfull !!"), TEXT("NO ERROR"), MB_OK);
		//}
		wsprintf(str, TEXT("SQUARE OF %d is : %d"), iNum, pfn(iNum));
		MessageBox(hwnd, str, TEXT("MySQuareOutput"), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hwnd, WM_DESTROY, 0, 0L);
			break;
		}
		break;

	case WM_DESTROY:
		FreeLibrary(hLib);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
