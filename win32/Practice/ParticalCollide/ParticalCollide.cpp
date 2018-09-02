#include<windows.h>
#include<stdlib.h>
#include<stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI MyThreadProcOne(LPVOID);


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

	HWND hwnd = (HWND)param;
	RECT rc;
	GetClientRect(hwnd, &rc);
	int a = 1;
	while (a)
	{
		if ((iRight > RightMove && iBottom == (rc.bottom - 20)) || (iLeft < LeftMove && iBottom == (rc.bottom) - 20))
		{
			MessageBox(hwnd, TEXT("LOOSE"), TEXT("LOOSE"), MB_OK);
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
			Sleep(((rand()%10)));
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}

	return 0;
}
