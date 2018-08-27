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


LRESULT CALLBACK WndProc  (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);


typedef struct InputData
{
	CHAR name[50], address[50],age[3];
	INT status;
}INPUT_DATA;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("MY Data Entry");
	HWND hwnd;
	MSG msg;

	wndclass.cbClsExtra		= 0;
	wndclass.cbSize			= sizeof(wndclass);
	wndclass.cbWndExtra		= 0;
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance		= hInstance;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.lpszClassName	= szAppName;
	wndclass.lpszMenuName	= NULL;
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL, TEXT("CLASS REGISTRATION FAILD !!"), TEXT("ERROR MESSAGE"), MB_OK | MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("MY Data Entry"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	static	int			siInitialSpace,siInitialMessage = 0;
	static	HBITMAP		hBitMap;
	static	HBITMAP		hBitMap2;
	HDC			hdc, hdc1;
	PAINTSTRUCT ps;
	RECT		rc;
	BITMAP		bmp;
	HFONT		hFont;
	static int iInitialImage = 0;
	
	hFont = CreateFont(40, 0, 0, 0, FW_THIN, TRUE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	
	switch (iMsg)
	{
	case WM_CREATE:
		//GetWindowLong(hwnd, GWL_HINSTANCE); // For getting hInstance in WndProc
		hBitMap = LoadBitmap((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(MY_BITMAP));
		if (!hBitMap)
		{
			MessageBox(hwnd, TEXT("ERROR Loading Bitmap"), TEXT("ERROR MSG"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}
		hBitMap2 = LoadBitmap((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(MY_BITMAP2));
		if (!hBitMap2)
		{
			MessageBox(hwnd, TEXT("ERROR Loading Bitmap"), TEXT("ERROR MSG"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		hdc1 = CreateCompatibleDC(hdc);
		if (iInitialImage == 0)
		{
			SelectObject(hdc1, hBitMap2);
			GetObject(hBitMap2, sizeof(BITMAP), (LPVOID)&bmp);

			SetStretchBltMode(hdc, HALFTONE);
			StretchBlt(hdc, 0, 0, rc.right , rc.bottom , hdc1, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
			
			SelectObject(hdc, hFont);

			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(255, 255, 255));
			DrawText(hdc, TEXT("\n\n\n\n\n\n\nLoading......"), -1, &rc, DT_CENTER);

			
			Sleep(10000);
			iInitialImage++;
		}

		SelectObject(hdc1, hBitMap);
		GetObject(hBitMap, sizeof(BITMAP), (LPVOID)&bmp);
		
		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdc1, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		
		if(siInitialMessage == 0)
		{	
		//	hFont = CreateFont(40, 0, 0, 0, FW_THIN, TRUE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		//		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));

			SelectObject(hdc, hFont);
			
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(255,255, 255));
			DrawText(hdc, TEXT("\n\n\n\n\n\n\nWelcome !! \nPress Space bar to continue ..."), -1, &rc, DT_CENTER);
			DeleteObject(hFont);
		}
		
		DeleteDC(hdc1);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			if (siInitialSpace == 0)
			{
				siInitialMessage	= 1;
				siInitialSpace		= 1;
				
				//MessageBox(hwnd, TEXT("SPACE PRESSED !!"), TEXT("MESSAGE"), MB_OK);
				if (DialogBox((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(DATAENTRY), hwnd, (DLGPROC)MyDlgProc) == IDOK)
				{
				//	MessageBox(hwnd, TEXT("MSG"), TEXT("SUCCESS"), MB_OK);
				}
				else
				{
					MessageBox(hwnd, TEXT("Dialog Box call FAIL"), TEXT("ERROR MESSAGE"), MB_OK | MB_ICONERROR);
					DestroyWindow(hwnd);
				}
				InvalidateRect(hwnd, FALSE, NULL);
			}
			break;
		case VK_ESCAPE:
			MessageBox(hwnd, TEXT("Terminated !!"), TEXT("Closing Window"), MB_OK);
			DestroyWindow(hwnd);
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
	TCHAR status[10];
	int err;

	INPUT_DATA ip;
	FILE *stream;
		

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
			ip.status = SendDlgItemMessage(hwnd, ID_RBMARRIED, BM_GETCHECK, 0, 0);
			if (ip.status)
				wsprintf(status, TEXT("MARRIED"));
			else
				wsprintf(status, TEXT("UNMARRIED"));

			wsprintf(str, TEXT(" Entered Name : %s \n Entered Address : %s \n Entered Age : %s \n Entered Status : %s\n"), ip.name,ip.address,ip.age, status);
			MessageBox(hwnd, str, TEXT("TITLE"), MB_OK);
			
			err = fopen_s(&stream,"write.txt","a+");
			if(err != 0)
				MessageBox(hwnd, TEXT("UNABLE TO OPEN FILE"), TEXT("ERROR!!"), MB_OK);
			else
				fprintf_s(stream, "%s", str);

			fclose(stream);
			EndDialog(hwnd, wParam);
			return TRUE;
		
		case IDCANCEL:
			EndDialog(hwnd, wParam);
			return TRUE;
		}
	}
	return FALSE;
}
