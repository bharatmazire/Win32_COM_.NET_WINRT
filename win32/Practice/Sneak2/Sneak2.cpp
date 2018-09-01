#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI MyThreadProcOne(LPVOID);


int iWho = 1;
int iLeft, iTop, iRight, iBottom;
int iLeftMove = 0;
int iTopMove = 0;
int iRightMove = 0;
int iBottomMove = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("MY SNAKE APP !");
	HWND hwnd;
	MSG msg;

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
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

	hwnd = CreateWindow(szAppName, TEXT("MY SNAKE APP"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	RECT rc;
	HBRUSH hBrushBlack, hBrushWhite;
	int iLen;
	int iTemp1, iTemp2;

	//static int iLeft, iTop, iRight, iBottom;

	//static int iLeftMove = 0;
	//static int iTopMove = 0;
	//static int iRightMove = 0;
	//static int iBottomMove = 0;

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
		case 'A':
			//iRightMove = iRightMove - 20;
			iWho = 1;
			break;
		case 'W':
			//iBottomMove = iBottomMove - 20;
			iWho = 2;
			break;
		case 'D':
			//iRightMove = iRightMove + 20;
			iWho = 4;
			break;
		case 'S':
			//iBottomMove = iBottomMove + 20;
			iWho = 3;
			break;
		case VK_RIGHT:
			//iRightMove = iRightMove + 20;
			iWho = 4;
			break;
		case VK_LEFT:
			//iRightMove = iRightMove - 20;
			iWho = 1;
			break;
		case VK_UP:
			//iBottomMove = iBottomMove - 20;
			iWho = 2;
			break;
		case VK_DOWN:
			//iBottomMove = iBottomMove + 20;
			iWho = 3;
			break;
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);

		iTemp1 = rc.bottom - rc.top;
		iTemp2 = rc.right - rc.left;

		if (iTemp1 < iTemp2)
			iLen = iTemp1;
		else
			iLen = iTemp2;

		if (iRightMove >= iLen)
			iRightMove = 0;
		else if (iRightMove < rc.left)
			iRightMove = iLen;

		if (iBottomMove >= iLen)
			iBottomMove = 0;
		else if (iBottomMove < 0)
			iBottomMove = iLen;

		//iLeft = rc.left / 20 + iRightMove;
		//iTop = rc.top / 20 + iBottomMove;
		iLeft = iLen / 20 - 20 + iRightMove;
		iTop = iLen / 20 - 20 + iBottomMove;
		iRight = iLen / 20 + iRightMove;
		iBottom = iLen / 20 + iBottomMove;

		hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, hBrushBlack);

		Rectangle(hdc, rc.left, rc.top, iLen, iLen);

		hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, hBrushWhite);
		Rectangle(hdc, iLeft, iTop, iRight, iBottom);

		break;

	case WM_DESTROY:
		MessageBox(hwnd, TEXT("THANKS RU7W1K !!"), TEXT("END NOTE "), MB_OK);
		PostQuitMessage(0);
		break;

	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI MyThreadProcOne(LPVOID param)
{

	HWND hwnd;
	hwnd = (HWND)param;

	while (1)
	{
		if (iWho == 1)
			iRightMove = iRightMove - 20;
		else if (iWho == 2)
			iBottomMove = iBottomMove - 20;
		else if (iWho == 3)
			iBottomMove = iBottomMove + 20;
		else if (iWho == 4)
			iRightMove = iRightMove + 20;

		Sleep(90);
		InvalidateRect(hwnd, NULL, false);

	}
	
	
	return 0;
}




