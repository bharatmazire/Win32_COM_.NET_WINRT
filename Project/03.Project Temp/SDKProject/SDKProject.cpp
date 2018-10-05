#include<windows.h>
#include "SDKProject.h"
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

static HMODULE hLibPhy = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("SDK Project");
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
		MessageBox(NULL, TEXT("Class Registration Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("SDK Educational Project"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	static	HBITMAP	hBitMap;
	HDC			hdc, hdc1;
	PAINTSTRUCT ps;
	RECT		rc;
	BITMAP		bmp;
	HFONT		hFont;
	static	int	siInitialSpace, siInitialMessage = 0;

	switch (iMsg)
	{
	case WM_CREATE:
		hBitMap = LoadBitmap((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(MY_BITMAP));
		if (!hBitMap)
		{
			MessageBox(hwnd, TEXT("Bitmap Loading Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		hLibPhy= LoadLibrary(TEXT("PhysicsDll.dll"));
		if (hLibPhy == NULL)
		{
			MessageBox(hwnd, TEXT("DLL LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
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
			SetTextColor(hdc, RGB(255, 255, 255));
			DrawText(hdc, TEXT("\n\n\n\n\n\n\n\n\n\n\n\n\n... PRESS SPACEBAR TO CONTINUE ..."), -1, &rc, DT_CENTER);
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
				}
				else
				{
					MessageBox(hwnd, TEXT("Dialog Box Creation Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
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
		FreeLibrary(hLibPhy);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK MyDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static CHAR str[20];
	int err;
	static double dWeight,dMass;

	// for dll
	typedef double(*pfnWeightCalculate) (double, int);
	static pfnWeightCalculate pfn = NULL;

	static double dResult;
	FILE *stream;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		EnableWindow(GetDlgItem(hwnd, IDCLEAR_PHY), FALSE);
		SetFocus(GetDlgItem(hwnd,IDCANCEL));
		break;

	case WM_COMMAND:
		
		switch (LOWORD(wParam))
		{

		// physics part
		case ID_RBPHY:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				EnableWindow(GetDlgItem(hwnd, IDCLEAR_PHY), TRUE);

				EnableWindow(GetDlgItem(hwnd, ID_ETWEIGHT), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETCHEM), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATH), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETBIO), FALSE);

				pfn = (pfnWeightCalculate)GetProcAddress(hLibPhy, "WeightCalculator");
				if (pfn == NULL)
				{
					MessageBox(hwnd, TEXT("PFN LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
					DestroyWindow(hwnd);
				}
				break;
			}
			break;

		case ID_RBSUN:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);
				
				dWeight = atof(str);

				dMass = dWeight / 9.798;
				dResult = pfn(dMass, 1);
				
				StringCbPrintfA(str, 20, "%f", dResult);
				
				SetDlgItemText(hwnd, ID_ETGRAVITY, "274");
				SetDlgItemText(hwnd, ID_ETWEIGHT2, str);
				break;
			}
			break;
		
		case ID_RBJUP:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);

				dWeight = atof(str);
				
				dMass = dWeight / 9.798;
				dResult = pfn(dMass, 2);

				StringCbPrintfA(str, 20, "%f", dResult);

				SetDlgItemText(hwnd, ID_ETGRAVITY, "24.92");
				SetDlgItemText(hwnd, ID_ETWEIGHT2, str);
				break;
			}
			break;

		case ID_RBNEP:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);

				dWeight = atof(str);
				
				dMass = dWeight / 9.798;
				dResult = pfn(dMass, 3);

				StringCbPrintfA(str, 20, "%f", dResult);

				SetDlgItemText(hwnd, ID_ETGRAVITY, "11.15");
				SetDlgItemText(hwnd, ID_ETWEIGHT2, str);
				
				break;
			}
			break;

		case ID_RBSAT:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);

				dWeight = atof(str);
				
				dMass = dWeight / 9.798;
				dResult = pfn(dMass, 4);

				StringCbPrintfA(str, 20, "%f", dResult);

				SetDlgItemText(hwnd, ID_ETGRAVITY, "10.44");
				SetDlgItemText(hwnd, ID_ETWEIGHT2, str);
				break;
			}
			break;

		case ID_RBEAR:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);

				dWeight = atof(str);
				
				dMass = dWeight / 9.798;
				dResult = pfn(dMass, 5);

				StringCbPrintfA(str, 20, "%f", dResult);

				SetDlgItemText(hwnd, ID_ETGRAVITY, "9.798");
				SetDlgItemText(hwnd, ID_ETWEIGHT2, str);
				break;
			}
			break;

		case ID_RBURA:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);

				dWeight = atof(str);

				dMass = dWeight / 9.798;
				dResult = pfn(dMass, 6);

				StringCbPrintfA(str, 20, "%f", dResult);

				SetDlgItemText(hwnd, ID_ETGRAVITY, "8.87");
				SetDlgItemText(hwnd, ID_ETWEIGHT2, str);
				break;
			}
			break;

		case ID_RBVEN:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);

				dWeight = atof(str);
				
				dMass = dWeight / 9.798;
				dResult = pfn(dMass, 7);

				StringCbPrintfA(str, 20, "%f", dResult);

				SetDlgItemText(hwnd, ID_ETGRAVITY, "8.87");
				SetDlgItemText(hwnd, ID_ETWEIGHT2, str);
				break;
			}
			break;

		case ID_RBMARS:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);

				dWeight = atof(str);
				
				dMass = dWeight / 9.798;
				dResult = pfn(dMass, 8);

				StringCbPrintfA(str, 20, "%f", dResult);

				SetDlgItemText(hwnd, ID_ETGRAVITY, "3.71");
				SetDlgItemText(hwnd, ID_ETWEIGHT2, str);
				break;
			}
			break;

		case ID_RBMER:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);

				dWeight = atof(str);

				dMass = dWeight / 9.798;
				dResult = pfn(dMass, 9);

				StringCbPrintfA(str, 20, "%f", dResult);

				SetDlgItemText(hwnd, ID_ETGRAVITY, "3.7");
				SetDlgItemText(hwnd, ID_ETWEIGHT2, str);
				break;
			}
			break;

		case ID_RBMOON:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);

				dWeight = atof(str);
				
				dMass = dWeight / 9.798;
				dResult = pfn(dMass, 10);

				StringCbPrintfA(str, 20, "%f", dResult);

				SetDlgItemText(hwnd, ID_ETGRAVITY, "1.68");
				SetDlgItemText(hwnd, ID_ETWEIGHT2, str);
				break;
			}
			break;

		case ID_RBPLU:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);

				dWeight = atof(str);

				dMass = dWeight / 9.798;
				dResult = pfn(dMass, 11);

				StringCbPrintfA(str, 20, "%f", dResult);

				SetDlgItemText(hwnd, ID_ETGRAVITY, "0.58");
				SetDlgItemText(hwnd, ID_ETWEIGHT2, str);
				break;
			}
			break;

		case IDCLEAR_PHY:
			SetDlgItemText(hwnd, ID_ETWEIGHT, "");
			SetDlgItemText(hwnd, ID_ETGRAVITY, "");
			SetDlgItemText(hwnd, ID_ETWEIGHT2, "");
			break;
		
		/*
		case IDCOMPUTE_PHY:
			//GetDlgItemTextA(hwnd, ID_ETWEIGHT, str, 20);
			//wsprintf(str, "%f", atof(str));
			//MessageBox(hwnd, str, TEXT("SEE"), MB_OK);
			SetDlgItemText(hwnd, ID_ETGRAVITY, "gravity");
			SetDlgItemText(hwnd, ID_ETWEIGHT2, "weight");
			break;
		*/

		// chemistry part
		case ID_RBCHEM:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				EnableWindow(GetDlgItem(hwnd, IDCLEAR_PHY), FALSE);

				EnableWindow(GetDlgItem(hwnd, ID_ETWEIGHT), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETCHEM), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATH), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETBIO), FALSE);
				break;
			}
			break;


		// maths part
		case ID_RBMATHS:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				EnableWindow(GetDlgItem(hwnd, IDCLEAR_PHY), FALSE);

				EnableWindow(GetDlgItem(hwnd, ID_ETWEIGHT), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETCHEM), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATH), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETBIO), FALSE);
				break;
			}
			break;


		// biology part
		case ID_RBBIO:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				EnableWindow(GetDlgItem(hwnd, IDCLEAR_PHY), FALSE);

				EnableWindow(GetDlgItem(hwnd, ID_ETWEIGHT), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETCHEM), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATH), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETBIO), TRUE);
				break;
			}
			break;

		// common part
		case IDRESET:
			SetDlgItemText(hwnd, ID_ETWEIGHT, "");
			SetDlgItemText(hwnd, IDCLEAR_PHY, "");
			SetDlgItemText(hwnd, ID_ETWEIGHT2, "");
			SetDlgItemText(hwnd, ID_ETGRAVITY, "");
			
			
			SetDlgItemText(hwnd, ID_ETCHEM, "");
			SetDlgItemText(hwnd, ID_ETMATH, "");
			SetDlgItemText(hwnd, ID_ETBIO, "");


			EnableWindow(GetDlgItem(hwnd, IDCLEAR_PHY), FALSE);

			EnableWindow(GetDlgItem(hwnd, ID_ETWEIGHT), FALSE);
			EnableWindow(GetDlgItem(hwnd, ID_ETCHEM), FALSE);
			EnableWindow(GetDlgItem(hwnd, ID_ETMATH), FALSE);
			EnableWindow(GetDlgItem(hwnd, ID_ETBIO), FALSE);
			
			SetFocus(GetDlgItem(hwnd, IDCANCEL));
			break;

		case IDOK:
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
