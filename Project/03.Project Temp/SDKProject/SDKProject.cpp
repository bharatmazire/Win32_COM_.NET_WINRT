#include<windows.h>
#include "SDKProject.h"
#include"PhysicsDll.h"
#include"MiddleDll.h"
#include"ChemistryServerLoader.h"

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

#pragma region FunctionDeclaration
void ClearPhysics(HWND);
void ClearChemistry(HWND);
void ClearMaths(HWND);
void ClearBiology(HWND);

void ResetPhysics(HWND);
void ResetChemistry(HWND);
void ResetMaths(HWND);
void ResetBiology(HWND);
#pragma endregion

// for dll's
static HMODULE hLibPhy = NULL;
static HMODULE hLibMaths = NULL;
static HMODULE hLibChem = NULL;

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
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
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

	hwnd = CreateWindow(szAppName, TEXT("WM_GESTURE"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	HDC			hdc, hdc1,hdc_old;
	PAINTSTRUCT ps;
	RECT		rc;
	BITMAP		bmp;
	HFONT		hFont;
	static	int	siInitialSpace, siInitialMessage = 0;

	switch (iMsg)
	{

#pragma region WM_CREATE
	case WM_CREATE:
		// loading bitmaps
		hBitMap = LoadBitmap((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(MY_BITMAP));
		if (!hBitMap)
		{
			MessageBox(hwnd, TEXT("Bitmap Loading Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		// loading physics library
		hLibPhy= LoadLibrary(TEXT("PhysicsDll.dll"));
		if (hLibPhy == NULL)
		{
			MessageBox(hwnd, TEXT("Physics DLL LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		// loading maths middleware library
		hLibMaths = LoadLibrary(TEXT("MiddleDll.dll"));
		if (hLibMaths == NULL)
		{
			MessageBox(hwnd, TEXT("Maths DLL LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		// loding chem middlemiddle library
		hLibChem = LoadLibrary(TEXT("ChemSrcLdrLoader.dll"));
		if (hLibChem == NULL)
		{
			MessageBox(hwnd, TEXT("Chemistry Dll Loading Fails !!"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		break;
#pragma endregion

#pragma region WM_PAINT
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hdc_old = hdc;
		GetClientRect(hwnd, &rc);
		hdc1 = CreateCompatibleDC(hdc);

		SelectObject(hdc1, hBitMap);
		GetObject(hBitMap, sizeof(BITMAP), (LPVOID)&bmp);

		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdc1, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

		//if (siInitialMessage == 0)
		//{
			hFont = CreateFont(30, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_MODERN, TEXT("Comic Sans MS"));

			SelectObject(hdc, hFont);

			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(0,0,0));
			DrawText(hdc, TEXT("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n PRESS  :                       .     TO CONTINUE \n  :               \t \t.       TO CLOSE"), -1, &rc, DT_CENTER);
			SetTextColor(hdc, RGB(255, 0, 0));
			DrawText(hdc, TEXT("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n.        'SPACEBAR'             \n'ESC'    \t \t  "), -1, &rc, DT_CENTER);

			
			DeleteObject(hFont);

			hFont = CreateFont(30, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_MODERN, TEXT("Courier New"));

			SelectObject(hdc, hFont);
			SetTextColor(hdc, RGB(0, 255, 255));
			//SetBkColor(hdc, RGB(211,211,211));
			DrawText(hdc, TEXT("\n. BATCH : Win32 SDK 2018 \n. NAME  : BHARAT S. MAZIRE"), -1, &rc, DT_LEFT);
		
			SetTextColor(hdc, RGB(0, 255, 255));
			//SetBkColor(hdc, RGB(211, 211, 211));
			DrawText(hdc, TEXT("\nWM_GESTURE  .\n ASTROMEDICOMP  ."), -1, &rc, DT_RIGHT);
		
		
		//}

		DeleteDC(hdc1);
		EndPaint(hwnd, &ps);
		break;
#pragma endregion

#pragma region WM_KEYDOWN
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			//if (siInitialSpace == 0)
			//{
			//	siInitialMessage = 1;
			//	siInitialSpace = 1;

				if (DialogBox((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(DATAENTRY), hwnd, (DLGPROC)MyDlgProc) == IDOK)
				{
				}
				else
				{
					//MessageBox(hwnd, TEXT("Dialog Box Creation Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
					//DestroyWindow(hwnd);
				}
				InvalidateRect(hwnd, NULL, FALSE);
			//}
			//else
			//{
			//	siInitialMessage = 0;
			//	siInitialSpace = 1;
			//	InvalidateRect(hwnd, NULL, FALSE);
			//}
			break;
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		break;
#pragma endregion

#pragma region WM_DESTROY
	case WM_DESTROY:
		FreeLibrary(hLibPhy);
		FreeLibrary(hLibMaths);
		FreeLibrary(hLibChem);
		PostQuitMessage(0);
		break;
	}
#pragma endregion

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK MyDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH hBrush;
	static int subject = 0;
	static CHAR str[20],str2[20],sstr[200],smass[20];
	int err;
	// physics
	static int planat = 0;
	static double g = 0.0;	// gravity to write in file
	static double ww = 0.0; // weight to write in file
	static double r = 0.0;
	// maths
	
	static double mx1 = 0.0;
	static double mx2 = 0.0;
	static double mx3 = 0.0;
	static double mx4 = 0.0;
	static double mx5 = 0.0;
	static double mx6 = 0.0;

	static double mx7 = 0.0;
	static double mx8 = 0.0;
	static double mx9 = 0.0;
	
	// chemistry
	static double cv1 = 0.0;
	static double cv2 = 0.0;
	static double cv3 = 0.0;
	static double cv4 = 0.0;


#pragma region PHYDLL
	// for physics dll
	typedef double(*pfnWeightCalculate) (double, double);
	static pfnWeightCalculate pfn = NULL;
	static double dWeight, dMass;
	static double dResult;
#pragma endregion

#pragma region MATHDLL
	// for maths part
	typedef HRESULT(*pfnSidesTriangle) (double , double , double , double , double , double , int* );
	static pfnSidesTriangle pfnSidesOfTriangle = NULL;

	typedef HRESULT(*pfnAngleTriangle) (double, double, double, int*);
	static pfnAngleTriangle pfnAngleOfTriangle = NULL;

	 
	// 1 : Equilateral \n 2 : Isosceles \n 3 : right angle \n 4 : Scelenes FOR SIDE
	// 1 : Equilateral \n 2 : Isosceles \n 3 : right angle \n 4 : obtuse \n 5.Acute \n 6.Scelenes  \n 7. Wrong input  FOR ANGLE
	static int iTypeOfTriangle;
	static int iMathMode; // 1 for side 2 for angle

	static CHAR x1[10], x2[10], x3[10], y1[10], y2[10], y3[10];
	static CHAR a[10], b[10], c[10];
#pragma endregion

#pragma region CHEMDLL
	// for chemistry part
	typedef HRESULT(*pfnChemistryCalculation) (int, double, double, double*);
	static pfnChemistryCalculation pfnChem = NULL;

	static int iChemMode = 1;
	static CHAR v1[10], v2[10];
	static double vv1, vv2 , q1, q2, w, e, cop;
	static double ret;
	static char strchem1[20], strchem2[20];
#pragma endregion

	FILE *stream;

	switch (iMsg)
	{

#pragma region WM_INITDIALOG
	case WM_INITDIALOG:
		// physics button disable
		EnableWindow(GetDlgItem(hwnd, IDCLEAR_PHY), FALSE);
		EnableWindow(GetDlgItem(hwnd, IDCOMPUTE_PHY), FALSE);
		
		ResetPhysics(hwnd);
		ResetMaths(hwnd);
		ResetChemistry(hwnd);
		ResetBiology(hwnd);
		SetDlgItemText(hwnd, ID_CHEMPOS1, "Enter Q1 : ");
		SetDlgItemText(hwnd, ID_CHEMPOS2, "Enter Q2 : ");
		SetDlgItemText(hwnd, ID_CHEMPOS3, "Effeciency : ");
		SetDlgItemText(hwnd, ID_CHEMPOS4, "Work Done : ");
		// maths button disable
		EnableWindow(GetDlgItem(hwnd, IDCLEAR_MATH), FALSE);
		EnableWindow(GetDlgItem(hwnd, IDCOMPUTE_MATH), FALSE);

		SetFocus(GetDlgItem(hwnd,IDCANCEL));
		break;
#pragma endregion


	case WM_CTLCOLORDLG:
	case WM_CTLCOLORBTN:
	//case WM_CTLCOLOREDIT:
	//case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORSTATIC:
	case WM_CTLCOLORMSGBOX:
		//SetBkColor((HDC)wParam, RGB(255, 255, 255));
		//SetBkMode((HDC)wParam, RGB(0, 0, 0));
		//SetTextColor((HDC)wParam, RGB(64, 224, 208));
		SetBkMode((HDC)wParam, RGB(255, 255, 255));
		SetTextColor((HDC)wParam, RGB(0, 0, 128));
		
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		return (INT_PTR)hBrush;

		break;

	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
		case CTLCOLOR_DLG:
			return TRUE;

		case CTLCOLOR_EDIT:
			return TRUE;
		}
		switch (LOWORD(wParam))
		{
#pragma region PHYSICS
		// physics part
		case ID_RBPHY:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				subject = 1;
				ResetChemistry(hwnd);
				ResetMaths(hwnd);
				ResetBiology(hwnd);

				EnableWindow(GetDlgItem(hwnd, IDCLEAR_PHY), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETGRAVITY), TRUE);
				EnableWindow(GetDlgItem(hwnd, IDCOMPUTE_PHY), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETWEIGHT), TRUE);
				//EnableWindow(GetDlgItem(hwnd, ID_ETMASS), TRUE);
				
				// radio button enable start
				EnableWindow(GetDlgItem(hwnd, ID_RBSUN), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_RBJUP), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_RBNEP), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_RBSAT), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_RBEAR), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_RBURA), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_RBVEN), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_RBMARS), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_RBMER), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_RBMOON), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_RBPLU), TRUE);
				// radio button enable end



				pfn = (pfnWeightCalculate)GetProcAddress(hLibPhy, "WeightCalculator");
				if (pfn == NULL)
				{
					MessageBox(hwnd, TEXT("PFN LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
					DestroyWindow(hwnd);
				}
				break;
			}
			break;

		case IDCOMPUTE_PHY:
			GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);
			GetDlgItemText(hwnd, ID_ETGRAVITY, str2, 20);

			dWeight = atof(str);
			
			dMass = dWeight / 9.798;
			dResult = pfn(dMass, atof(str2));
			r = dResult;
			if (ww == atof(str) && g == atof(str2) && dResult == r)
				subject = -1;
			else
			{
				ww = atof(str);
				g = atof(str2);
				r = dResult;
			}

			StringCbPrintfA(str, 20, "%f", dResult);
			StringCbPrintfA(smass, 20, "%f", dMass);
			

			
			SetDlgItemText(hwnd, ID_ETMASS, smass);
			SetDlgItemText(hwnd, ID_ETGRAVITY, str2);
			SetDlgItemText(hwnd, ID_ETWEIGHT2, str);

			break;

		case ID_RBSUN:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, ID_ETWEIGHT, str, 20);
				
				dWeight = atof(str);

				dMass = dWeight / 9.798;
				dResult = pfn(dMass, 274);
				
				if ( r == dResult && planat == 1 && ww == atof(str) && g == 274)
					subject = -1;
				else
				{
					planat = 1;
					ww = atof(str);
					g = 274;
					r = dResult;
				
				}

				StringCbPrintfA(str, 20, "%f", dResult);
				StringCbPrintfA(smass, 20, "%f", dMass);



				SetDlgItemText(hwnd, ID_ETMASS, smass);
				
				
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
				dResult = pfn(dMass, 24.92);

				if ( r == dResult && planat == 2 && ww == atof(str) && g == 24.92)
					subject = -1;
				else
				{
					planat = 2;
					ww = atof(str);
					g = 24.92;
					r = dResult;
				}


				StringCbPrintfA(str, 20, "%f", dResult);

				StringCbPrintfA(smass, 20, "%f", dMass);



				SetDlgItemText(hwnd, ID_ETMASS, smass);

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
				dResult = pfn(dMass, 11.15);

				if ( r == dResult && planat == 3 && ww == atof(str) && g == 11.15)
					subject = -1;
				else
				{
					planat = 3;
					ww = atof(str);
					g = 11.15;
					r = dResult;
				}

				StringCbPrintfA(str, 20, "%f", dResult);
				StringCbPrintfA(smass, 20, "%f", dMass);



				SetDlgItemText(hwnd, ID_ETMASS, smass);
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
				dResult = pfn(dMass, 10.44);

				if ( r == dResult && planat == 4 && ww == atof(str) && g == 10.44)
					subject = -1;
				else
				{
					planat = 4;
					ww = atof(str);
					g = 10.44;
					r = dResult;
				}

				StringCbPrintfA(str, 20, "%f", dResult);
				StringCbPrintfA(smass, 20, "%f", dMass);



				SetDlgItemText(hwnd, ID_ETMASS, smass);

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
				dResult = pfn(dMass, 9.798);

				if ( r == dResult && planat == 5 && ww == atof(str) && g == 9.798)
					subject = -1;
				else
				{
					planat = 5;
					ww = atof(str);
					g = 9.798;
					r = dResult;
				}
				
				StringCbPrintfA(str, 20, "%f", dResult);
				StringCbPrintfA(smass, 20, "%f", dMass);



				SetDlgItemText(hwnd, ID_ETMASS, smass);
				

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
				dResult = pfn(dMass, 8.87);

				if ( r == dResult && planat == 6 && ww == atof(str) && g == 8.87)
					subject = -1;
				else
				{
					planat = 6;
					ww = atof(str);
					g = 8.87;
					r = dResult;
				}


				StringCbPrintfA(str, 20, "%f", dResult);
				StringCbPrintfA(smass, 20, "%f", dMass);



				SetDlgItemText(hwnd, ID_ETMASS, smass);
				

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
				dResult = pfn(dMass, 8.87);

				if ( r == dResult && planat == 7 && ww == atof(str) && g == 8.87)
					subject = -1;
				else
				{
					planat = 7;
					ww = atof(str);
					g = 8.87;
					r = dResult;
				}

				StringCbPrintfA(str, 20, "%f", dResult);
				StringCbPrintfA(smass, 20, "%f", dMass);



				SetDlgItemText(hwnd, ID_ETMASS, smass);
				

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
				dResult = pfn(dMass, 3.71);


				if ( r == dResult && planat == 8 && ww == atof(str) && g == 3.71)
					subject = -1;
				else
				{
					planat = 8;
					ww = atof(str);
					g = 3.71;
					r = dResult;
				}

				StringCbPrintfA(str, 20, "%f", dResult);
				StringCbPrintfA(smass, 20, "%f", dMass);



				SetDlgItemText(hwnd, ID_ETMASS, smass);
				

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
				dResult = pfn(dMass, 3.7);

				if ( r == dResult && planat == 9 && ww == atof(str) && g == 3.7)
					subject = -1;
				else
				{
					planat = 9;
					ww = atof(str);
					g = 3.7;
					r = dResult;
				}

				StringCbPrintfA(str, 20, "%f", dResult);
				StringCbPrintfA(smass, 20, "%f", dMass);



				SetDlgItemText(hwnd, ID_ETMASS, smass);
				

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
				dResult = pfn(dMass, 1.68);

				if ( r == dResult && planat == 10 && ww == atof(str) && g == 1.68)
					subject = -1;
				else
				{
					planat = 10;
					ww = atof(str);
					g = 1.68;
					r = dResult;
				}

				StringCbPrintfA(str, 20, "%f", dResult);
				StringCbPrintfA(smass, 20, "%f", dMass);



				SetDlgItemText(hwnd, ID_ETMASS, smass);
				

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
				dResult = pfn(dMass, 0.58);

				if ( r == dResult && planat == 11 && ww == atof(str) && g == 0.58)
					subject = -1;
				else
				{
					planat = 11;
					ww = atof(str);
					g = 0.58;
					r = dResult;
				}

				StringCbPrintfA(str, 20, "%f", dResult);
				StringCbPrintfA(smass, 20, "%f", dMass);



				SetDlgItemText(hwnd, ID_ETMASS, smass);
				

				SetDlgItemText(hwnd, ID_ETGRAVITY, "0.58");
				SetDlgItemText(hwnd, ID_ETWEIGHT2, str);
				break;
			}
			break;

		case IDCLEAR_PHY:
			ClearPhysics(hwnd);
			break;
		

#pragma endregion

#pragma region CHEMISTRY
		// chemistry part
		case ID_RBCHEM:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				subject = 2;
				ClearPhysics(hwnd);
				ResetPhysics(hwnd);
				ResetMaths(hwnd);
				ClearMaths(hwnd);
				ResetBiology(hwnd);
				EnableWindow(GetDlgItem(hwnd, ID_ETCHEM), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_CHEMBTHEAT), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_CHEMBTNREF), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_CHEMBTAC), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_CHEMPOS1), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_CHEMPOS2), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_CHEMPOS3), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_CHEMPOS4), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_CHEMET1), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_CHEMET2), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_CHEMET3), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_CHEMET4), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_CHEMCOMPUTE), TRUE);


				pfnChem = (pfnChemistryCalculation)GetProcAddress(hLibChem, "ChemistryCalculation");
				if (pfnChem == NULL)
				{
					MessageBox(hwnd, TEXT("pfnChemistryCalculation LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
					DestroyWindow(hwnd);
				}
				break;
			}
			break;
		case ID_CHEMBTHEAT:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ClearChemistry(hwnd);
				SetDlgItemText(hwnd, ID_CHEMPOS1, "Enter Q1 : ");
				SetDlgItemText(hwnd, ID_CHEMPOS2, "Enter Q2 : ");
				SetDlgItemText(hwnd, ID_CHEMPOS3, "Effeciency : ");
				SetDlgItemText(hwnd, ID_CHEMPOS4, "Work Done : ");
				SetDlgItemText(hwnd, U1, "J");
				SetDlgItemText(hwnd, U2, "J");
				SetDlgItemText(hwnd, U3, "%");
				SetDlgItemText(hwnd, U4, "J");
				iChemMode = 1;
				break;
			}
			break;
		case ID_CHEMBTNREF:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ClearChemistry(hwnd);
				SetDlgItemText(hwnd, ID_CHEMPOS1, "Enter Q1 : ");
				SetDlgItemText(hwnd, ID_CHEMPOS2, "Enter W : ");
				SetDlgItemText(hwnd, ID_CHEMPOS3, "Q2 : ");
				SetDlgItemText(hwnd, ID_CHEMPOS4, "C. O. P. : ");
				SetDlgItemText(hwnd, U1, "J");
				SetDlgItemText(hwnd, U2, "J");
				SetDlgItemText(hwnd, U3, "J");
				SetDlgItemText(hwnd, U4, "C");

				iChemMode = 2;
				break;
			}
			break;
		case ID_CHEMBTAC:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ClearChemistry(hwnd);
				SetDlgItemText(hwnd, ID_CHEMPOS1, "Enter Q2 : ");
				SetDlgItemText(hwnd, ID_CHEMPOS2, "Enter W : ");
				SetDlgItemText(hwnd, ID_CHEMPOS3, "Q1 : ");
				SetDlgItemText(hwnd, ID_CHEMPOS4, "C. O. P. : ");
				SetDlgItemText(hwnd, U1, "J");
				SetDlgItemText(hwnd, U2, "J");
				SetDlgItemText(hwnd, U3, "J");
				SetDlgItemText(hwnd, U4, "C");

				iChemMode = 3;
				break;
			}
			break;

		case ID_CHEMCOMPUTE:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (iChemMode == 1)
				{
					//heat: ip q1 q2
					//w = q1 - q2
					//eff = w / q1
					
					GetDlgItemText(hwnd, ID_CHEMET1, v1, 10);
					GetDlgItemText(hwnd, ID_CHEMET2, v2, 10);
					vv1 = atof(v1);
					vv2 = atof(v2);
					
					


					w = vv1 - vv2;

					pfnChem(1, vv1, vv2, &ret);
					
					StringCbPrintfA(strchem1, 20, "%f", ret);
					StringCbPrintfA(strchem2, 20, "%f", w);

					if (cv1 == vv1 && cv2 == vv2 && cv3 == ret && cv4 == w)
						subject = -1;
					else
					{
						cv1 = vv1;
						cv2 = vv2;
						cv3 = ret;
						cv4 = w;
					}
						
					SetDlgItemText(hwnd, ID_CHEMET3, strchem1);
					SetDlgItemText(hwnd, ID_CHEMET4, strchem2);

				}
				else if (iChemMode == 2)
				{
				/*  ref: ip q1 w
					q2 = q1 + w
					cop = q2 / w or q2 / (q1 - q2)*/

					GetDlgItemText(hwnd, ID_CHEMET1, v1, 10);
					GetDlgItemText(hwnd, ID_CHEMET2, v2, 10);
					vv1 = atof(v1);
					vv2 = atof(v2);

					q2 = vv1 + vv2;

					pfnChem(1, vv1, vv2, &ret);

					StringCbPrintfA(strchem1, 20, "%f", ret);
					StringCbPrintfA(strchem2, 20, "%f", q2);

					if (cv1 == vv1 && cv2 == vv2 && cv3 == ret && cv4 == q2)
						subject = -1;
					else
					{
						cv1 = vv1;
						cv2 = vv2;
						cv3 = ret;
						cv4 = q2;
					}


					SetDlgItemText(hwnd, ID_CHEMET3, strchem1);
					SetDlgItemText(hwnd, ID_CHEMET4, strchem2);

				}
				else if (iChemMode == 3)
				{
					/*ac: ip q2 w
					q1 = q2 + w
					cop = q1 / w*/
					GetDlgItemText(hwnd, ID_CHEMET1, v1, 10);
					GetDlgItemText(hwnd, ID_CHEMET2, v2, 10);
					vv1 = atof(v1);
					vv2 = atof(v2);

					q1 = vv1 + vv2;

					pfnChem(1, vv1, vv2, &ret);

					StringCbPrintfA(strchem1, 20, "%f", ret);
					StringCbPrintfA(strchem2, 20, "%f", q1);

					if (cv1 == vv1 && cv2 == vv2 && cv3 == ret && cv4 == q1)
						subject = -1;
					else
					{
						cv1 = vv1;
						cv2 = vv2;
						cv3 = ret;
						cv4 = q1;
					}


					SetDlgItemText(hwnd, ID_CHEMET3, strchem1);
					SetDlgItemText(hwnd, ID_CHEMET4, strchem2);
				}

				break;
			}
			break;
#pragma endregion

#pragma region MATHS
		// maths part
		case ID_RBMATHS:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				subject = 3;
				ResetPhysics(hwnd);
				ClearPhysics(hwnd);
				ResetChemistry(hwnd);
				ResetBiology(hwnd);

				EnableWindow(GetDlgItem(hwnd, ID_RBSIDE), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_RBANGLE), TRUE);

				/*EnableWindow(GetDlgItem(hwnd, ID_ETMATHX1), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHX2), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHX3), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHY1), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHY2), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHY3), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHA), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHB), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHC), TRUE);*/

				/*EnableWindow(GetDlgItem(hwnd, IDCLEAR_MATH), TRUE);
				EnableWindow(GetDlgItem(hwnd, IDCOMPUTE_MATH), TRUE);*/
								
				break;
			}
			break;

		case ID_RBSIDE:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ClearMaths(hwnd);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHX1), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHX2), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHX3), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHY1), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHY2), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHY3), TRUE);

				EnableWindow(GetDlgItem(hwnd, ID_ETMATHA), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHB), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHC), FALSE);

				EnableWindow(GetDlgItem(hwnd, IDCLEAR_MATH), TRUE);
				EnableWindow(GetDlgItem(hwnd, IDCOMPUTE_MATH), TRUE);
				

				iMathMode = 1;
				pfnSidesOfTriangle = (pfnSidesTriangle)GetProcAddress(hLibMaths, "SidesOfTriangle");
				if (pfnSidesOfTriangle == NULL)
				{
					MessageBox(hwnd, TEXT("pfnSidesOfTriangle LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
					DestroyWindow(hwnd);
				}
				break;
			}
			break;

		case ID_RBANGLE:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ClearMaths(hwnd);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHX1), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHX2), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHX3), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHY1), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHY2), FALSE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHY3), FALSE);

				EnableWindow(GetDlgItem(hwnd, ID_ETMATHA), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHB), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETMATHC), TRUE);

				EnableWindow(GetDlgItem(hwnd, IDCLEAR_MATH), TRUE);
				EnableWindow(GetDlgItem(hwnd, IDCOMPUTE_MATH), TRUE);
				

				iMathMode = 2;
				pfnAngleOfTriangle = (pfnAngleTriangle)GetProcAddress(hLibMaths, "AngleOfTriangle");
				if (pfnAngleOfTriangle == NULL)
				{
					MessageBox(hwnd, TEXT("pfnAngleOfTriangle LOADING FAILS !!"), TEXT("ERROR"), MB_OK);
					DestroyWindow(hwnd);
				}
				
				
				break;
			}
			break;

		case IDCOMPUTE_MATH:
			if (iMathMode == 1)
			{
				GetDlgItemText(hwnd, ID_ETMATHX1, x1, 10);
				GetDlgItemText(hwnd, ID_ETMATHX2, x2, 10);
				GetDlgItemText(hwnd, ID_ETMATHX3, x3, 10);
				GetDlgItemText(hwnd, ID_ETMATHY1, y1, 10);
				GetDlgItemText(hwnd, ID_ETMATHY2, y2, 10);
				GetDlgItemText(hwnd, ID_ETMATHY3, y3, 10);

				pfnSidesOfTriangle(atof(x1), atof(x2), atof(x3), atof(y1), atof(y2), atof(y3), &iTypeOfTriangle);
				if (mx1 == atof(x1) &&
					mx2 == atof(x2) &&
					mx3 == atof(x3) &&
					mx4 == atof(y1) &&
					mx5 == atof(y2) &&
					mx6 == atof(y3))
					subject = -1;
				else
				{
					mx1 = atof(x1);
					mx2 = atof(x2);
					mx3 = atof(x3);
					mx4 = atof(y1);
					mx5 = atof(y2);
					mx6 = atof(y3);
				}
				
				// 1 : Equilateral \n 2 : Isosceles \n 3 : right angle \n 4 : Scelenes FOR SIDE
				switch (iTypeOfTriangle)
				{
				case 1:
					wsprintf(str, "Equilateral");
					break;
				case 2:
					wsprintf(str, "Isosceles");
					break;
				case 3:
					wsprintf(str, "right angle");
					break;
				case 4:
					wsprintf(str, "Scelenes");
					break;
				default:
					wsprintf(str, "wrong input");
					break;
				}
			}
			else if(iMathMode == 2)
			{
				GetDlgItemText(hwnd, ID_ETMATHA, a, 10);
				GetDlgItemText(hwnd, ID_ETMATHB, b, 10);
				GetDlgItemText(hwnd, ID_ETMATHC, c, 10);

				pfnAngleOfTriangle(atof(a), atof(b), atof(c), &iTypeOfTriangle);
				if (mx7 == atof(a) && mx8 == atof(b) && mx9 == atof(c)) 
					subject = -1;
				else
				{
					mx7 = atof(a);
					mx8 = atof(b);
					mx9 = atof(c);
				}
				
				// 1 : Equilateral \n 2 : Isosceles \n 3 : right angle \n 4 : obtuse \n 5.Acute \n 6.Scelenes  \n 7. Wrong input  FOR ANGLE
				switch (iTypeOfTriangle)
				{
				case 1:
					wsprintf(str, "Equilateral");
					break;
				case 2:
					wsprintf(str, "Isosceles");
					break;
				case 3:
					wsprintf(str, "right anngle");
					break;
				case 4:
					wsprintf(str, "Obtuse angle");
					break;
				case 5:
					wsprintf(str, "Acute angle");
					break;
				case 6:
					wsprintf(str, "Scelenes");
					break;
				case 7:
					wsprintf(str, "wrong input");
					break;
				default:
					wsprintf(str, "wrong input");
					break;
				}
				
			}
			SetDlgItemText(hwnd, ID_ETMATHRES, str);
			break;
#pragma endregion

#pragma region BIOLOGY
		// biology part
		case ID_RBBIO:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ClearPhysics(hwnd);
				ResetPhysics(hwnd);
				ResetChemistry(hwnd);
				ResetMaths(hwnd);

				EnableWindow(GetDlgItem(hwnd, ID_ETBIO), TRUE);
				break;
			}
			break;

		case ID_RBBIO1: 
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				SetDlgItemText(hwnd, ID_TESTBIO, "AA");
				break;
			}
			break;

		case ID_RBBIO2:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				SetDlgItemText(hwnd, ID_TESTBIO, "BB");
				break;
			}
			break;
#pragma endregion

#pragma region RESET_KEY
		// common part
		case IDRESET:
			ClearPhysics(hwnd);
			ClearChemistry(hwnd);
			ClearMaths(hwnd);
			ClearBiology(hwnd);
			
			ResetPhysics(hwnd);
			ResetChemistry(hwnd);
			ResetMaths(hwnd);
			ResetBiology(hwnd);
			
			SetFocus(GetDlgItem(hwnd, IDCANCEL));
			break;
#pragma endregion



#pragma region SAVE_KEY
		case IDOK:
			if (subject == 0)
			{
				MessageBox(hwnd,TEXT("DATA NOT PRESENT !!!"),TEXT("ERROR"),MB_OK | MB_ICONERROR);
			}
			else if (subject == -1)
			{
				MessageBox(hwnd, TEXT("Data Already Present !!"), TEXT("STOP"), MB_OK);
				//EndDialog(hwnd, wParam);
				//return TRUE;
			}
			else if (subject == 1)
			{
				// physics part
				err = fopen_s(&stream, "physics.txt", "a+");
				if (err != 0)
					MessageBox(hwnd, TEXT("UNABLE TO OPEN FILE"), TEXT("ERROR!!"), MB_OK);
				else
				{
					switch (planat)
					{
					case 1: wsprintf(sstr,"SUN");
						break;
					case 2:wsprintf(sstr, "JUPITOR");
						break;
					case 3:wsprintf(sstr, "NAPTUNE");
						break;
					case 4:wsprintf(sstr, "SATURN");
						break;
					case 5:wsprintf(sstr, "EARTH");
						break;
					case 6:wsprintf(sstr, "URANIUS");
						break;
					case 7:wsprintf(sstr, "VENUS");
						break;
					case 8:wsprintf(sstr, "MARS");
						break;
					case 9:wsprintf(sstr, "MERCURY");
						break;
					case 10:wsprintf(sstr, "MOON");
						break;
					case 11:wsprintf(sstr, "PLUTO");
						break;
					default:
						break;
					}
					fprintf_s(stream, "\n...............\n Planate : %s \n Gravitation : %f \n Weight : %f \n Result : %f ", sstr,g,ww,r);
				}
				
				fclose(stream);
			}
			else if (subject == 2)
			{
				// chemistry
				err = fopen_s(&stream, "Chemistry.txt", "a+");
				if (err != 0)
					MessageBox(hwnd, TEXT("UNABLE TO OPEN FILE"), TEXT("ERROR!!"), MB_OK);
				else
				{
					if(iChemMode == 1)
						fprintf_s(stream, "\n...............\n Q1 : %f \n Q2 : %f \n Eff : %f \n Work Done : %f ",cv1,cv2,cv3,cv4);
					else if(iChemMode == 2)
						fprintf_s(stream, "\n...............\n Q1 : %f \n W : %f \n Q2 : %f \n C.O.P. : %f ", cv1, cv2, cv3, cv4);
					else if(iChemMode == 3)
						fprintf_s(stream, "\n...............\n Q2 : %f \n W : %f \n Q1 : %f \n C.O.P. : %f ", cv1, cv2, cv3, cv4);
				}
				fclose(stream);
			}
			else if (subject == 3)
			{
				// maths
				err = fopen_s(&stream, "Maths.txt", "a+");
				if (err != 0)
					MessageBox(hwnd, TEXT("UNABLE TO OPEN FILE"), TEXT("ERROR!!"), MB_OK);
				else
				{
					if (iMathMode == 1)
						fprintf_s(stream, "\n...............\n x1: %f \n x2: %f \n x3: %f \n y1: %f \n y2: %f \n y3: %f \n Type: %s \n", mx1, mx2, mx3, mx4, mx5, mx6, str);
					else if (iMathMode == 2)
						fprintf_s(stream, "\n...............\n a: %f \n b: %f \n c: %f \n Type: %s ", mx7,mx8,mx9,str);
				}
				fclose(stream);
			}
			//EndDialog(hwnd, wParam);
			return TRUE;
#pragma endregion

#pragma region CANCEL_KEY
		case IDCANCEL:
			EndDialog(hwnd, wParam);
			return TRUE;
#pragma endregion
		
		} 
	}
	return FALSE;
}

#pragma region CLEAR
void ClearPhysics(HWND hwnd)
{
	SetDlgItemText(hwnd, ID_ETWEIGHT, "");
	SetDlgItemText(hwnd, ID_ETGRAVITY, "");
	SetDlgItemText(hwnd, ID_ETWEIGHT2, "");
	SetDlgItemText(hwnd, ID_ETMASS, "");
	//SetDlgItemText(hwnd, ID_RBEAR, 0);
	//SetDlgItemInt(hwnd, ID_RBEAR, 0, 0);
}
void ClearChemistry(HWND hwnd)
{
	SetDlgItemText(hwnd, ID_ETCHEM, "");
	/*SetDlgItemText(hwnd, ID_CHEMPOS1, "");
	SetDlgItemText(hwnd, ID_CHEMPOS2, "");
	SetDlgItemText(hwnd, ID_CHEMPOS3, "");
	SetDlgItemText(hwnd, ID_CHEMPOS4, "");
	*/SetDlgItemText(hwnd, ID_CHEMET1, "");
	SetDlgItemText(hwnd, ID_CHEMET2 , "");
	SetDlgItemText(hwnd, ID_CHEMET3, "");
	SetDlgItemText(hwnd, ID_CHEMET4, "");
}
void ClearMaths(HWND hwnd)
{
	SetDlgItemText(hwnd, ID_ETMATHX1,"");
	SetDlgItemText(hwnd, ID_ETMATHX2,"");
	SetDlgItemText(hwnd, ID_ETMATHX3,"");
	SetDlgItemText(hwnd, ID_ETMATHY1,"");
	SetDlgItemText(hwnd, ID_ETMATHY2,"");
	SetDlgItemText(hwnd, ID_ETMATHY3,"");
	SetDlgItemText(hwnd, ID_ETMATHA, "");
	SetDlgItemText(hwnd, ID_ETMATHB, "");
	SetDlgItemText(hwnd, ID_ETMATHC, "");
	SetDlgItemText(hwnd, ID_ETMATHRES, "");
}
void ClearBiology(HWND hwnd)
{
	SetDlgItemText(hwnd, ID_ETBIO, "");
}
#pragma endregion

#pragma region RESET
void ResetPhysics(HWND hwnd)
{
	ClearPhysics(hwnd);
	EnableWindow(GetDlgItem(hwnd, IDCOMPUTE_PHY), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDCLEAR_PHY), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_ETGRAVITY), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_ETWEIGHT), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_ETMASS), FALSE);

	EnableWindow(GetDlgItem(hwnd, ID_RBSUN), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_RBJUP), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_RBNEP), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_RBSAT), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_RBEAR), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_RBURA), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_RBVEN), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_RBMARS), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_RBMER), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_RBMOON), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_RBPLU), FALSE);
}
void ResetChemistry(HWND hwnd)
{
	ClearChemistry(hwnd);
	EnableWindow(GetDlgItem(hwnd, ID_CHEMCOMPUTE), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_ETCHEM), FALSE);
	EnableWindow(GetDlgItem(hwnd,ID_CHEMBTHEAT), FALSE);
	EnableWindow(GetDlgItem(hwnd,ID_CHEMBTNREF), FALSE);
	EnableWindow(GetDlgItem(hwnd,ID_CHEMBTAC  ), FALSE);
	/*EnableWindow(GetDlgItem(hwnd,ID_CHEMPOS1  ), FALSE);
	EnableWindow(GetDlgItem(hwnd,ID_CHEMPOS2  ), FALSE);
	EnableWindow(GetDlgItem(hwnd,ID_CHEMPOS3  ), FALSE);
	EnableWindow(GetDlgItem(hwnd,ID_CHEMPOS4  ), FALSE);
	*/EnableWindow(GetDlgItem(hwnd,ID_CHEMET1   ), FALSE);
	EnableWindow(GetDlgItem(hwnd,ID_CHEMET2	  ), FALSE);
	EnableWindow(GetDlgItem(hwnd,ID_CHEMET3   ), FALSE);
	EnableWindow(GetDlgItem(hwnd,ID_CHEMET4   ), FALSE);


}
void ResetMaths(HWND hwnd)
{
	ClearMaths(hwnd);
	EnableWindow(GetDlgItem(hwnd, ID_ETMATHX1), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_ETMATHX2), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_ETMATHX3), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_ETMATHY1), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_ETMATHY2), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_ETMATHY3), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_ETMATHA), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_ETMATHB), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_ETMATHC), FALSE);

	EnableWindow(GetDlgItem(hwnd, IDCOMPUTE_MATH), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDCLEAR_MATH), FALSE);

	EnableWindow(GetDlgItem(hwnd, ID_RBSIDE), FALSE);
	EnableWindow(GetDlgItem(hwnd, ID_RBANGLE), FALSE);
}
void ResetBiology(HWND hwnd)
{
	ClearBiology(hwnd);
	EnableWindow(GetDlgItem(hwnd, ID_ETBIO), FALSE);
}
#pragma endregion

