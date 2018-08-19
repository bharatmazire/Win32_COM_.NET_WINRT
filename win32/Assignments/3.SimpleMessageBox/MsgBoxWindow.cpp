// header file
#include<windows.h>

// global function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// variable declaration
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("MY WINDOW");
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

	// registering above class
	RegisterClassEx(&wndclass);

	// create handle
	hwnd = CreateWindow(szAppName, TEXT("MY SAMPLE WINDOW"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	// show and update window
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}

// WndProc()
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	switch (iMsg)
	{
	case WM_CREATE:
		MessageBox(hwnd, TEXT("WM_CREATE HANDLED"), TEXT("WM_CREATE BOX"), MB_OK | MB_ICONEXCLAMATION);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("WM_LBUTTONDOWN HANDLED"), TEXT("WM_LBUTTONDOWN BOX"), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_MOVE:
		MessageBox(hwnd, TEXT("WM_MOVE HANDLED"), TEXT("WM_MOVE BOX"), MB_OK | MB_ICONQUESTION);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hwnd, WM_DESTROY, 0, 0L);
			break;
		}
		MessageBox(hwnd, TEXT("WM_KEYDOWN HANDLED"), TEXT("WM_KEYDOWN BOX"), MB_OK | MB_ICONSTOP);
		break;

	case WM_SIZE:
		MessageBox(hwnd, TEXT("WM_SIZE HANDLED"), TEXT("WM_SIZE BOX"), MB_OK | MB_ICONERROR);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
