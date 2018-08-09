#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI MyThreadProcOne(LPVOID);

HWND hwnd;
HDC hdc;
HBRUSH hBrush;
RECT rc;
PAINTSTRUCT ps;

static int R, G, B = 0;

typedef struct ColorStruct
{
	HWND hwnd;
	//HDC hdc;
	//RECT rc;
}COLORSTRUCT,*PCOLORSTRUCT;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyColourThreadedApp");

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

	hwnd = CreateWindow(szAppName, TEXT("My 2nd Thread Application with colour"), WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,	NULL,hInstance,	NULL);

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
	static HANDLE hThread1 = NULL;

	switch (iMsg)
	{
	case WM_CREATE:
		

		COLORSTRUCT ColorStruct;
		ColorStruct.hwnd = hwnd;

		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcOne,(LPVOID)&ColorStruct, 0, NULL);
		if (hThread1 == NULL)
		{
			MessageBox(hwnd, TEXT("Thread 1 creation failed "), TEXT("ERROR MSG"), MB_OK);
			DestroyWindow(hwnd);
		}


	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		hBrush = CreateSolidBrush(RGB(R,G,B));

		FillRect(hdc, &rc, hBrush);
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
	
	//MessageBox(hwnd, TEXT("inside thread "), TEXT("ERROR MSG"), MB_OK);
	//Sleep(10000);
	//for (int i = 0; i < 255; i++)
	//{
	//	for (int j = 0; j < 255; j++)
	//	{
	//		for (int k = 0; k < 255; k++)
	//		{
	//			R = i;
	//			G = j;
	//			B = k;
	//			InvalidateRect(hwnd,NULL, TRUE);
	//			Sleep(10);
	//		}
	//	}
	//}

	while (true)
	{
		for (int p = 0; p < 255; p++)
		{
			R = p;
			InvalidateRect(hwnd, NULL, TRUE);
			Sleep(25);
		}
		for (int q = 0; q < 255; q++)
		{
			G = q;
			InvalidateRect(hwnd, NULL, TRUE);
			Sleep(25);
		}
		for (int r = 0; r < 255; r++)
		{
			B = r;
			InvalidateRect(hwnd, NULL, TRUE);
			Sleep(25);
		}
	}
	
	return 0;
}
