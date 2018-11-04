#include<windows.h>
#include "SDKProject.h"
#include"PhysicsDll.h"
#include"MiddleDll.h"
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

		break;
#pragma endregion

#pragma region WM_PAINT
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
#pragma endregion

#pragma region WM_KEYDOWN
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
#pragma endregion

#pragma region WM_DESTROY
	case WM_DESTROY:
		FreeLibrary(hLibPhy);
		PostQuitMessage(0);
		break;
	}
#pragma endregion

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK MyDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static CHAR str[20],str2[20];
	int err;
	static double dWeight,dMass;

	// for physics dll
	typedef double(*pfnWeightCalculate) (double, double);
	static pfnWeightCalculate pfn = NULL;

	static double dResult;

	// for maths part
	typedef HRESULT(*pfnSidesTriangle) (double , double , double , double , double , double , int* );
	static pfnSidesTriangle pfnSidesOfTriangle = NULL;

	typedef HRESULT(*pfnAngleTriangle) (double, double, double, int*);
	static pfnAngleTriangle pfnAngleOfTriangle = NULL;

	static int iTypeOfTriangle; 
	// 1 : Equilateral \n 2 : Isosceles \n 3 : right angle \n 4 : Scelenes FOR SIDE
	// 1 : Equilateral \n 2 : Isosceles \n 3 : right angle \n 4 : obtuse \n 5.Acute \n 6.Scelenes  \n 7. Wrong input  FOR ANGLE

	static int iMathMode; // 1 for side 2 for angle

	static CHAR x1[10], x2[10], x3[10], y1[10], y2[10], y3[10];
	static CHAR a[10], b[10], c[10];



	
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
		
		// maths button disable
		EnableWindow(GetDlgItem(hwnd, IDCLEAR_MATH), FALSE);
		EnableWindow(GetDlgItem(hwnd, IDCOMPUTE_MATH), FALSE);

		SetFocus(GetDlgItem(hwnd,IDCANCEL));
		break;
#pragma endregion



	case WM_COMMAND:
		
		switch (LOWORD(wParam))
		{
#pragma region PHYSICS
		// physics part
		case ID_RBPHY:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ResetChemistry(hwnd);
				ResetMaths(hwnd);
				ResetBiology(hwnd);
				
				EnableWindow(GetDlgItem(hwnd, IDCLEAR_PHY), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETGRAVITY), TRUE);
				EnableWindow(GetDlgItem(hwnd, IDCOMPUTE_PHY), TRUE);
				EnableWindow(GetDlgItem(hwnd, ID_ETWEIGHT), TRUE);
				
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

			StringCbPrintfA(str, 20, "%f", dResult);

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
				dResult = pfn(dMass, 24.92);

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
				dResult = pfn(dMass, 11.15);

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
				dResult = pfn(dMass, 10.44);

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
				dResult = pfn(dMass, 9.798);

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
				dResult = pfn(dMass, 8.87);

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
				dResult = pfn(dMass, 8.87);

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
				dResult = pfn(dMass, 3.71);

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
				dResult = pfn(dMass, 3.7);

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
				dResult = pfn(dMass, 1.68);

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
				dResult = pfn(dMass, 0.58);

				StringCbPrintfA(str, 20, "%f", dResult);

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
				ClearPhysics(hwnd);
				ResetPhysics(hwnd);
				ResetMaths(hwnd);
				ResetBiology(hwnd);
				EnableWindow(GetDlgItem(hwnd, ID_ETCHEM), TRUE);
				
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
			err = fopen_s(&stream, "write.txt", "a+");
			if (err != 0)
				MessageBox(hwnd, TEXT("UNABLE TO OPEN FILE"), TEXT("ERROR!!"), MB_OK);
			else
				fprintf_s(stream, "%s", str);

			fclose(stream);
			EndDialog(hwnd, wParam);
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
	//SetDlgItemText(hwnd, ID_RBEAR, 0);
	//SetDlgItemInt(hwnd, ID_RBEAR, 0, 0);
}
void ClearChemistry(HWND hwnd)
{
	SetDlgItemText(hwnd, ID_ETCHEM, "");
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
	EnableWindow(GetDlgItem(hwnd, ID_ETCHEM), FALSE);
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

