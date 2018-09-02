#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include "MyHeader.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI MyThreadProcOne(LPVOID);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);

int iLeft = 0;
int iTop = 0;
int iRight = 20;
int iBottom = 20;

int l,t,r,b;

int ud = 0;
int lr = 0;

int Brclr = 0;

int LeftMove = 0;
int RightMove = 120;

int Speed = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("BRICKS CATCH GAME");
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
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL, TEXT("Class Registration Failed"), TEXT("ERROR MESSAGE"), MB_OK | MB_ICONERROR);
		return -1;
	}

	hwnd = CreateWindow(szAppName, TEXT("BRICKS CATCH GAME"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rc;
	GetClientRect(hwnd, &rc);
	HBRUSH hBrush, hBrushBar;
	static int iChoice;

	static HANDLE hThread1 = NULL;
	
	switch (iMsg)
	{

	case WM_CREATE:
		
		iChoice = MessageBox(hwnd, TEXT("Rules to play game : \n '>>... DO NOT RESIZE WINDOW ...<< '\n\n 1. Use Right and Left Arrow Keys to move Sticker \n 2. Close Window when you Loose \n\n\n Click 'OK' to start "), TEXT("RULES !!!"), MB_ICONINFORMATION | MB_OKCANCEL);
		if (iChoice == 1)
		{
			if (DialogBox((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(SPEED), hwnd, (DLGPROC)MyDlgProc) == IDOK)
			{
			//		MessageBox(hwnd, TEXT("MSG"), TEXT("SUCCESS"), MB_OK);
			}
			else
			{
				MessageBox(hwnd, TEXT("Dialog Box call FAIL"), TEXT("ERROR MESSAGE"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}

			Sleep(200);

			hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcOne, (LPVOID)hwnd, 0, NULL);
			if (hThread1 == NULL)
			{
				MessageBox(hwnd, TEXT("Thread 1 creation failed "), TEXT("ERROR MSG"), MB_OK);
				DestroyWindow(hwnd);
			}
		}
		else
		{
			MessageBox(hwnd, TEXT("THANK YOU !!"), TEXT("QUIT GAME"), MB_OK);
			DestroyWindow(hwnd);
		}
		
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if (LeftMove == rc.left)
				LeftMove = 0;
			else
				LeftMove -= 20;
			RightMove = LeftMove + 120;
			break;

		case VK_RIGHT:
			if (RightMove == rc.right)
				RightMove = rc.right;
			else
				RightMove += 20;
			LeftMove = RightMove - 120;
			break;

		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//GetClientRect(hwnd, &rc);
		if(Brclr == 0)
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
		else if(Brclr == 1)
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
		else if(Brclr == 2)
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
		else
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
		
		
		SelectObject(hdc, hBrush);
		Rectangle(hdc, iLeft, iTop, iRight, iBottom);


		hBrushBar = CreateSolidBrush(RGB(128, 128, 128));
		SelectObject(hdc, hBrushBar);
		Rectangle(hdc, LeftMove, (rc.bottom - 20), RightMove, rc.bottom);

		DeleteObject(hBrush);
		DeleteObject(hBrushBar);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		CloseHandle(hThread1);
		PostQuitMessage(0);
		break;

	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI MyThreadProcOne(LPVOID param)
{
	int Score = 0;
	TCHAR str[30];

	int sp;
	if (Speed == 0)
		sp = 5;
	else if (Speed == 1)
		sp = 10;

	int a = 1;

	HWND hwnd = (HWND)param;
	RECT rc;
	GetClientRect(hwnd, &rc);
	while (a)
	{
		if ((iRight > (RightMove+20) && iBottom == (rc.bottom - 20)) || (iLeft < (LeftMove-20) && iBottom == (rc.bottom) - 20))
		{
			MessageBox(hwnd, TEXT("YOU LOOSE"), TEXT("GAME STATUS"), MB_OK);
			a = 0;
			wsprintf(str, TEXT("YOUR SCORE : %d"), Score);
			MessageBox(hwnd, str, TEXT("SCORE "), MB_OK);
			//DestroyWindow(hwnd);
		}
		else
		{
			
			if (ud == 0 && lr == 0)
			{
				if (iRight < rc.right)
				{
					iRight++;
					iLeft = iRight - 20;
				}
				else
				{
					lr = 1;
					Brclr = 1;
				}

				if (iBottom < rc.bottom)
				{
					iBottom++;
					iTop = iBottom - 20;
				}
				else
				{
					ud = 1;
					Brclr = 0;
					Score++;
				}
			}
			else if (ud == 1 && lr == 0)
			{
				if (iRight < rc.right)
				{
					iRight++;
					iLeft = iRight - 20;
				}
				else
				{
					lr = 1;
					Brclr = 1;
				}

				if (iTop > rc.top)
				{
					iTop--;
					iBottom = iTop + 20;
				}
				else
				{
					ud = 0;
					Brclr = 2;
				}
			}
			else if (ud == 0 && lr == 1)
			{
				if (iLeft > rc.left)
				{
					iLeft--;
					iRight = iLeft + 20;
				}
				else
				{
					lr = 0;
					Brclr = 3;
				}

				if (iBottom < rc.bottom)
				{
					iBottom++;
					iTop = iBottom - 20;
				}
				else
				{
					ud = 1;
					Brclr = 0;
					Score++;
				}
			}
			else
			{
				if (iLeft > rc.left)
				{
					iLeft--;
					iRight = iLeft + 20;
				}
				else
				{
					lr = 0;
					Brclr = 3;
				}

				if (iTop > rc.top)
				{
					iTop--;
					iBottom = iTop + 20;
				}
				else
				{
					ud = 0;
					Brclr = 2;
					
				}
			}
			Sleep(sp);
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	return 0;
}

BOOL CALLBACK MyDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//TCHAR str[30];
	
	switch (iMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			Speed = SendDlgItemMessage(hwnd, ID_RBEASY, BM_GETCHECK, 0, 0);
			//wsprintf(str, "%d", Speed);
			//MessageBox(hwnd, str, TEXT("see"), MB_OK);
			EndDialog(hwnd, wParam);
			return TRUE;

		case IDCANCEL:
			EndDialog(hwnd, wParam);
			return TRUE;
		}
	}
	return FALSE;
}
