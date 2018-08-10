#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI MyThreadProcOne(LPVOID);
DWORD WINAPI MyThreadProcTwo(LPVOID);

HWND hwnd;
HDC hdc;
HBRUSH hBrush;
RECT rc;
PAINTSTRUCT ps;
HRGN  hrgn;
static int R, G, B = 0;
//static int left,right,top,bottom = 0;

typedef struct ColorStruct
{
	HWND hwnd;
	RECT rc;
}COLORSTRUCT, *PCOLORSTRUCT;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyColourThreadedApp2");

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

	hwnd = CreateWindow(szAppName, TEXT("My 3rd Thread Application with colour"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	static HANDLE hThread1, hThread2 = NULL;
	GetClientRect(hwnd, &rc);
	switch (iMsg)
	{
	case WM_CREATE:


		COLORSTRUCT ColorStruct1, ColorStruct2;
		ColorStruct1.hwnd = hwnd;
		ColorStruct1.rc = rc;
		ColorStruct2.hwnd = hwnd;
		ColorStruct2.rc = rc;
		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcOne, (LPVOID)&ColorStruct1, 0, NULL);
		if (hThread1 == NULL)
		{
			MessageBox(hwnd, TEXT("Thread 1 creation failed "), TEXT("ERROR MSG"), MB_OK);
			DestroyWindow(hwnd);
		}

		hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcTwo, (LPVOID)&ColorStruct2, 0, NULL);
		if (hThread1 == NULL)
		{
			MessageBox(hwnd, TEXT("Thread 2 creation failed "), TEXT("ERROR MSG"), MB_OK);
			DestroyWindow(hwnd);
		}

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//GetClientRect(hwnd, &rc);
		hBrush = CreateSolidBrush(RGB(R, G, B));
		SelectObject(hdc, hBrush);
		FillRgn(hdc, hrgn, hBrush);
		//Rectangle(hdc, left, top, right, bottom);
		//FillRect(hdc, &rc, hBrush);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI MyThreadProcOne(LPVOID param)
{
	COLORSTRUCT *PColorStruct = (PCOLORSTRUCT)param;

	hwnd = PColorStruct->hwnd;
	rc = PColorStruct->rc;

	RECT rc1;
	rc1.left = rc.left;
	rc1.top = rc.top;
	rc1.right = rc.right / 2;
	rc1.bottom = rc.bottom / 2;

	while (true)
	{
		for (int p = 0; p < 255; p++)
		{
			R = p;
			InvalidateRect(hwnd, &rc1, TRUE);
			Sleep(25);
		}
		for (int q = 0; q < 255; q++)
		{
			G = q;
			InvalidateRect(hwnd, &rc1, TRUE);
			Sleep(25);
		}
		for (int r = 0; r < 255; r++)
		{
			B = r;
			InvalidateRect(hwnd, &rc1, TRUE);
			Sleep(25);
		}
	}

	return 0;
}

DWORD WINAPI MyThreadProcTwo(LPVOID param)
{
	COLORSTRUCT *PColorStruct = (PCOLORSTRUCT)param;

	hwnd = PColorStruct->hwnd;
	rc = PColorStruct->rc;

	RECT rc2;
	rc2.left = rc.left*2;
	rc2.top = rc.top*2;
	rc2.right = rc.right;
	rc2.bottom = rc.bottom;

	while (true)
	{
		for (int p = 0; p < 255; p++)
		{
			B = p;
			InvalidateRect(hwnd, &rc2, TRUE);
			Sleep(25);
		}
		for (int q = 0; q < 255; q++)
		{
			G = q;
			InvalidateRect(hwnd, &rc2, TRUE);
			Sleep(25);
		}
		for (int r = 0; r < 255; r++)
		{
			R = r;
			InvalidateRect(hwnd, &rc2, TRUE);
			Sleep(25);
		}
	}

	return 0;
}
