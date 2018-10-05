#include<windows.h>
#include "MyHeader.h"
#include"PhysicsDll.h"
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
BOOL    CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);

typedef struct InputDataPhysics
{
	CHAR cMass[10],cPlanat[10];
}INPUT_DATA_PHY;

typedef struct InputDataBiology
{
	CHAR name[50], address[50], age[3];
	INT status;
}INPUT_DATA_BIO;

typedef struct InputDataChemistry
{
	CHAR name[50], address[50], age[3];
	INT status;
}INPUT_DATA_CHEM;

typedef struct InputDataMath
{
	CHAR name[50], address[50], age[3];
	INT status;
}INPUT_DATA_MATH;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("MY Data Entry");
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
	static	int	siInitialSpace, siInitialMessage = 0;
	static	HBITMAP	hBitMap;
	HDC			hdc, hdc1;
	PAINTSTRUCT ps;
	RECT		rc;
	BITMAP		bmp;
	HFONT		hFont;

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
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		hdc1 = CreateCompatibleDC(hdc);

		SelectObject(hdc1, hBitMap);
		GetObject(hBitMap, sizeof(BITMAP), (LPVOID)&bmp);

		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdc1, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

		if (siInitialMessage == 0)
		{
			hFont = CreateFont(40, 0, 0, 0, FW_THIN, TRUE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));

			SelectObject(hdc, hFont);

			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(0, 0, 0));
			DrawText(hdc, TEXT("\n\n\n\n\n\n\n\n\n\n\nWelcome !! \n\n\n Press Space bar to continue ..."), -1, &rc, DT_CENTER);
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
				siInitialMessage = 1;
				siInitialSpace = 1;
				
				if (DialogBox((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(DATAENTRY), hwnd, (DLGPROC)MyDlgProc) == IDOK)
				{
					//	MessageBox(hwnd, TEXT("MSG"), TEXT("SUCCESS"), MB_OK);
				}
				else
				{
					MessageBox(hwnd, TEXT("Dialog Box call FAIL"), TEXT("ERROR MESSAGE"), MB_OK | MB_ICONERROR);
					DestroyWindow(hwnd);
				}
				InvalidateRect(hwnd, NULL, FALSE);
			}
			//else
			//{
			//	siInitialMessage = 0;
			//	siInitialSpace = 1;
			//	InvalidateRect(hwnd, NULL, FALSE);
			//}
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

	INPUT_DATA_PHY IP_PHY;
	FILE *stream;

	// for dll

	HMODULE hLib = NULL;
	typedef int(*pfnWeightCalculate) (int,int);
	pfnWeightCalculate pfn = NULL;
	
	int r,m,p;
	m = 0;
	p = 0;
	r = 0;
	char * mm = NULL;
	char * pp = NULL;
//	TCHAR result[40];
	switch (iMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hwnd, ID_ETMASS));
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hwnd, ID_ETMASS, IP_PHY.cMass, 10);
			GetDlgItemText(hwnd, ID_COMBOBOX2, IP_PHY.cPlanat, 10);

			wsprintf(str, TEXT(" Entered MASS : %s \n Selected Planate : %s"),IP_PHY.cMass,IP_PHY.cPlanat);
			MessageBox(hwnd, str, TEXT("Accepted Info."), MB_OK);
			
			hLib = LoadLibrary(TEXT("PhysicsDll.dll"));
			if (hLib == NULL)
			{
				MessageBox(hwnd, TEXT("DLL LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
				DestroyWindow(hwnd);
			}
			else
			{
				MessageBox(hwnd, TEXT("DLL LOADING Successfull !!"), TEXT("NO ERROR"), MB_OK);
			}

			pfn = (pfnWeightCalculate)GetProcAddress(hLib, "WeightCalculator");
			if (pfn == NULL)
			{
				MessageBox(hwnd, TEXT("PFN LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
				DestroyWindow(hwnd);
			}
			else
			{
				MessageBox(hwnd, TEXT("PFN LOADING Successfull !!"), TEXT("NO ERROR"), MB_OK);
			}
			/*
			wsprintf(str, TEXT("m is  %s and p is %s"), m, p);
			MessageBox(hwnd, str, TEXT("result before atoi "), MB_OK);

			wsprintf(mm, TEXT("%s"), IP_PHY.cMass);
			wsprintf(pp, TEXT("%s"), IP_PHY.cPlanat);

			m = atoi(mm);
			p = atoi(pp);
			wsprintf(str, TEXT("m is  %d and p is %d"), m,p);
			MessageBox(hwnd, str, TEXT("result after atoi"), MB_OK);

			*/
			r = pfn(10,1);
			wsprintf(str, TEXT("resultant weight is  %s"), r);
			MessageBox(hwnd, str, TEXT("result"), MB_OK);


			err = fopen_s(&stream, "write.txt", "a+");
			if (err != 0)
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
