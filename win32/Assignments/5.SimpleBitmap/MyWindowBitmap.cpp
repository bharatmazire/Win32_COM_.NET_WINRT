#include<windows.h>
#include"MyResource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("MY WINDOW BITMAP");
	HWND hwnd;
	MSG msg;

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(wndclass);
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
	
	hwnd = CreateWindow(szAppName, TEXT("MY WINDOW WITH BITMAP"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBitMap;
	HDC hdc,hdc1;
	PAINTSTRUCT ps;
	RECT rc;
	BITMAP bmp;
	
	switch (iMsg)
	{
	case WM_CREATE:
		//GetWindowLong(hwnd, GWL_HINSTANCE); // For getting hInstance in WndProc
		hBitMap = LoadBitmap((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(MY_BITMAP));
		if (!hBitMap)
		{
			MessageBox(hwnd, TEXT("ERROR Loading Bitmap"), TEXT("ERROR MSG"), MB_OK);
		}
		break;

	case WM_PAINT:
		//MessageBox(hwnd, TEXT("IN PAINT"), TEXT("PAINT BOX"), MB_OK);
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);

		hdc1 = CreateCompatibleDC(hdc);
		
		SelectObject(hdc1, hBitMap);
		GetObject(hBitMap, sizeof(BITMAP),(LPVOID)&bmp);

		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(hdc, 0, 0, rc.right, rc.bottom,  hdc1, 0, 0, bmp.bmWidth, bmp.bmHeight,  SRCCOPY);

			

		//BitBlt(hdc, 0, 0, bmp.bmWidth,bmp.bmHeight, hdc1, 0, 0, SRCCOPY);
		
		DeleteDC(hdc1);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
