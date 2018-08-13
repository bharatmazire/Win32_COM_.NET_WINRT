#include<windows.h>
#include "Header.h"
#include <io.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <errno.h>  
#include <share.h> 
#include <tchar.h>
#include <strsafe.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);

typedef struct InputData
{
	CHAR name[50], address[50];
	CHAR age[3];
}INPUT_DATA;

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
	static int siInitialSpace,siInitialMessage = 0;
	static HBITMAP hBitMap;
	HDC hdc, hdc1;
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
		HFONT hFont;
		hdc1 = CreateCompatibleDC(hdc);

		SelectObject(hdc1, hBitMap);
		GetObject(hBitMap, sizeof(BITMAP), (LPVOID)&bmp);
		
		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdc1, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		if(siInitialMessage == 0)
		{	
			hFont = CreateFont(40, 0, 0, 0, FW_THIN, TRUE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH | FF_ROMAN, TEXT("Impact"));

			SelectObject(hdc, hFont);
			
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(255, 255, 255));
			DrawText(hdc, TEXT("Welcome !! \n Press Space bar to continue ..."), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
		
		//TextOut(hdc, 0, 0, TEXT("WELCOME"), 7);

		DeleteDC(hdc1);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			if (siInitialSpace == 0)
			{
				siInitialMessage = 1;
				siInitialSpace = 1;
				MessageBox(hwnd, TEXT("SPACE PRESSED !!"), TEXT("MESSAGE"), MB_OK);
				if (DialogBox((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(DATAENTRY), hwnd, (DLGPROC)MyDlgProc) == IDOK)
				{
					MessageBox(hwnd, TEXT("MSG"), TEXT("SUCCESS"), MB_OK);
				}
				else
				{
					MessageBox(hwnd, TEXT("MSG"), TEXT("FAIL"), MB_OK);
				}
				InvalidateRect(hwnd, FALSE, NULL);
			}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK MyDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[500];
	INPUT_DATA ip;

	int fileHandle = 0;
	//DWORD bytesWritten = 0;
	unsigned    bytesWritten = 0;
	HANDLE fhndl;


	switch (iMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hwnd, ID_ETNAME));
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hwnd, ID_ETNAME, ip.name, 50);
			GetDlgItemText(hwnd, ID_ETADDRESS, ip.address, 50);
			GetDlgItemText(hwnd, ID_ETAGE, ip.age, 3);
			//GetDlgItemInt(hwnd, ID_ETAGE, IpData->age, NULL, TRUE);
			wsprintf(str, TEXT(" Entered Name : %s \n Entered Address : %s \n Entered Age : %s"), ip.name,ip.address,ip.age);
			MessageBox(hwnd, str, TEXT("TITLE"), MB_OK);
			
			//fhndl = CreateFile(TEXT("Write.txt"),GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
			//WriteFile(fhndl, str, sizeof(str),&bytesWritten,NULL);
			//CloseHandle(fhndl);

			_sopen_s(&fileHandle, "write.txt", _O_RDWR | _O_CREAT, _SH_DENYNO, _S_IREAD | _S_IWRITE);
			bytesWritten = _write(fileHandle, str, sizeof(str));
			_close(fileHandle);
			
			EndDialog(hwnd, wParam);
			return TRUE;
		case IDCANCEL:
			EndDialog(hwnd, wParam);
			return TRUE;
		}
	}
	return FALSE;
}
