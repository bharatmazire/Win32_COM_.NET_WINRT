// This is 1st modification is MyWindow.cpp
// Additional changes
// 1. SPACE BAR to close
// 2. key 'q' to close
// 3. Hello world in message box on pressing 's' :: 's' for show 
// 4. use of WM_CREATE
// 5. Map keyboard key to mouse key


// Headers
#include<windows.h>

// global function declaration
LRESULT CALLBACK WndProc(HWND, UINT , WPARAM , LPARAM );

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	// code
	// initialization of WNDCLASSEX
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	
	// register above class
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(szAppName, TEXT("MyNewWindow"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int iMsgBox = 0;
	switch(iMsg)
	{
		case WM_CREATE:
			iMsgBox = MessageBox(hwnd, TEXT("Want to Start ?"), TEXT("INITIAL QUESTION"), MB_YESNO | MB_ICONQUESTION);
			if (iMsgBox == IDYES)
			{
				MessageBox(hwnd, TEXT("Press OK to Continue"), TEXT("Welcome Note"), MB_OK);
			}
			else
			{
				SendMessage(hwnd, WM_DESTROY, 0, 0);
			}
			break;

		case WM_KEYDOWN:									// WM_CHAR (for case change)
			switch(wParam)
			{
				case VK_SPACE:
					DestroyWindow(hwnd);					// one method to quite (API way)
					break;
				case 'Q':									// old way VK_Q [other ways : 'q' / hex value of q]
					SendMessage(hwnd, WM_DESTROY, 0, 0L);	// without API (automation can be done)
					break;
				case 'S':
					MessageBox(hwnd, TEXT("HELLO WORLD !!!"), TEXT("MyMessage"), MB_OK | MB_ICONASTERISK | MB_TOPMOST);
					break;
				case 'L':
					SendMessage(hwnd, WM_LBUTTONDOWN, 0, 0L);	// KeyBoard Mapping
					break;
			}
			break;

		case WM_LBUTTONDOWN:
			MessageBox(hwnd, TEXT("LEFT KEY DOWN"), TEXT("INFORMATION"), MB_ICONINFORMATION);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}