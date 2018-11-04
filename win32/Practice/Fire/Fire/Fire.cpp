#include<windows.h>
#include<stdlib.h>
#include "Fire.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI MyThreadProcOne(LPVOID);
static int R = 250;
static int G, B = 0;
static int iFire = 1;
static int x, y = 0;
static int i = 1;
static int r = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Fire");

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

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("Fire"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_MAXIMIZE);
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
	static HDC hdc;
	static HBRUSH hBrush;
	static RECT rc;
	static PAINTSTRUCT ps;
	HPEN hPen;

	static char str[255];

	static HANDLE hThread1 = NULL;

	switch (iMsg)
	{
	case WM_CREATE:
		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcOne, (LPVOID)hwnd, 0, NULL);
		if (hThread1 == NULL)
		{
			MessageBox(hwnd, TEXT("Thread 1 creation failed "), TEXT("ERROR MSG"), MB_OK);
			DestroyWindow(hwnd);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);

		hBrush = CreateSolidBrush(RGB(R, G, B));
		hPen = CreatePen(PS_SOLID, 1, RGB(R, G, B));
		SelectObject(hdc, hBrush);
		SelectObject(hdc, hPen);

		switch (iFire)
		{
		case 1:
			Chord(hdc, 100 * i + x, 50 * i + y + r, 250 * i + x, 400 * i + y, 140 * i + x, 50 * i + y, 230 * i + x, 370 * i + y );				// main back l
			Chord(hdc, 150 * i + x, 50 * i + y + r, 330 * i + x, 350 * i + y, 200 * i + x, 50 * i + y, 230 * i + x, 370 * i + y );				// main back r
			Chord(hdc, 50 * i + x, 100 * i + y + r, 200 * i + x, 350 * i + y, 70 * i + x, 90 * i + y, 200 * i + x, 300 * i + y );				// front left
			Chord(hdc, 140 * i + x, 100 * i + y + r, 290 * i + x, 350 * i + y, 180 * i + x, 250 * i + y, 240 * i + x, 100 * i + y );			// front right
			Chord(hdc, 20 * i + x, 130 * i + y + r, 170 * i + x, 380 * i + y, 20 * i + x, 150 * i + y, 150 * i + x, 370 * i + y );				// front front left
			
			//Chord(hdc, 180 * i + x, 150 * i + y, 330 * i + x, 400 * i + y, 300 * i + x, 100 * i + y, 220 * i + x, 400 * i + y );				// front front right
			Chord(hdc, 180 *  i + x, 150 * i + y + r, 330 * i + x, 400 * i + y, 220 * i + x, 300 * i + y, 320 * i + x, 50 * i + y );				// front front right
			break;
		case 2:
			Chord(hdc, 100 * i + x, 30 * i + y - r, 250 * i + x, 400 * i + y, 140 * i + x, 50 * i + y, 230 * i + x, 370 * i + y );				// main back l 
			Chord(hdc, 150 * i + x, 30 * i + y - r, 330 * i + x, 250 * i + y, 200 * i + x, 50 * i + y, 230 * i + x, 370 * i + y );				// main back r
			Chord(hdc, 50 * i + x, 100 * i + y - r, 200 * i + x, 350 * i + y, 80 * i + x, 80 * i + y, 200 * i + x, 300 * i + y );				// front left
			Chord(hdc, 140 * i + x, 70 * i + y - r, 270 * i + x, 350 * i + y, 180 * i + x, 250 * i + y, 240 * i + x, 100 * i + y );				// front right
			Chord(hdc, 20 * i + x, 130 * i + y - r, 170 * i + x, 380 * i + y, 20 * i + x, 150 * i + y, 150 * i + x, 370 * i + y );				// front front left
			// dont change below 2 to set same base
			//Chord(hdc, 180 * i + x, 150 * i + y, 330 * i + x, 400 * i + y, 300 * i + x, 100 * i + y, 220 * i + x, 400 * i + y );				// front front right
			//Chord(hdc, 180 * i + x, 150 * i + y, 330 * i + x, 400 * i + y, 220 * i + x, 400 * i + y, 220 * i + x, 400 * i + y );				// front front right
			Chord(hdc, 180 * i + x, 150 * i + y - r, 330 * i + x, 400 * i + y, 220 * i + x, 300 * i + y, 320 * i + x, 50 * i + y);
			break;
		}
		Chord(hdc, 20 * i + x, 50 * i + y , 330 * i + x, 450 * i + y, 20 * i + x, 300 * i + y, 330 * i + x, 300 * i + y);

		/*hBrush = CreateSolidBrush(RGB(0, 0, 0));
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(hdc, hBrush);
		SelectObject(hdc, hPen);
		Chord(hdc, 240 * i + x, 150 * i + y, 330 * i + x, 400 * i + y, 260 * i + x, 400 * i + y, 220 * i + x, 400 * i + y);
*/
		/*BeginPath(hdc);
		SelectObject(hdc, hBrush);
		MoveToEx(hdc, rc.right / 2, rc.bottom / 2, (LPPOINT) NULL);
		AngleArc(hdc, rc.right / 2, rc.bottom / 2, 50, 30, 90);
		LineTo(hdc, rc.right / 2, rc.bottom / 2);
		EndPath(hdc);
		StrokeAndFillPath(hdc);*/
		//FillRect(hdc, &rc, hBrush);
		wsprintf(str, TEXT("r :  %d"), r);
		DrawText(hdc, str, -1, &rc, DT_LEFT);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			x = x - 10;
			break;
		case VK_RIGHT:
			x = x + 10;
			break;
		case VK_UP:
			y = y - 10;
			break;
		case VK_DOWN:
			y = y + 10;
			break;
		case 'I':
			i = i + 1;
			break;
		case 'O':
			if (i != 0.2)
				i = i - 0.2;
			break;
		case 'M':
			r = r + 4;
			break;
		case 'N':
			r = r - 4;
			break;
		}
		break;

	case WM_DESTROY:
		SuspendThread(hThread1);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI MyThreadProcOne(LPVOID param)
{
	HWND hwnd = HWND(param);
	while (1)
	{
		if (R == 250)
		{
			R = 170;
		}
		else
		{
			R = R + 1;
		}
		if (G == 50)
		{
			G = 0;
		}
		else
		{
			G = G + 1;
		}
		//iFire = rand() % 2;
		if (iFire == 1)
			iFire = 2;
		else
			iFire = 1;
		r = rand() % 30;
		InvalidateRect(hwnd, NULL, TRUE);
		Sleep(100);
	}
	return 0;
}