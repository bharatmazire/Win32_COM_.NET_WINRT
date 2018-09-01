#include<windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MY APP");

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpszClassName = szAppName;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); 
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hInstance = hInstance;
	wndclass.lpszMenuName = NULL;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbSize = sizeof(WNDCLASSEX);


	if(!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL,TEXT(""),TEXT(""),MB_OK);
	}
	// HWND CreateWindowExA(DWORD,LPCSTR,LPCSTR,DWORD,int,int,int,int,HWND,HMENU,HINSTANCE,LPVOID)
	hwnd = CreateWindow(szAppName,TEXT("MY APP"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);	

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	}
	return (DefWindowProc(hwnd,iMsg,wParam,lParam));
}
