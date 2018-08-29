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
DWORD WINAPI MyThreadProcOne(LPVOID);
DWORD WINAPI MyThreadProcTwo(LPVOID);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc2(HWND, UINT, WPARAM, LPARAM);

typedef struct InputData
{
	CHAR name[50], address[50], age[3];
	INT status;
}INPUT_DATA;

typedef struct Choice
{
	INT choice;
}CHOICE_CH;
int gender = 0;

HWND hwnd;
HDC hdc;
HBRUSH hBrush;
RECT rc;
PAINTSTRUCT ps;

static int R, G, B = 0;

typedef struct ColorStruct
{
	HWND hwnd;
}COLORSTRUCT, *PCOLORSTRUCT;

typedef struct ColorStruct2
{
	HWND hwnd2;
}COLORSTRUCT2, *PCOLORSTRUCT2;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyColourThreadedWithDlgApp");

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

	hwnd = CreateWindow(szAppName, TEXT("My Thread Application with colour and Dlg"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	static HANDLE hThread1 = NULL;
	static HANDLE hThread2 = NULL;

	switch (iMsg)
	{
	case WM_CREATE:

		if (DialogBox((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(CHOICE), hwnd, (DLGPROC)MyDlgProc2) == IDOK)
		{
			//MessageBox(hwnd, TEXT("CHOICE ACCEPTED !!!"), TEXT("SUCCESS"), MB_OK);	
		}
		else
		{
			MessageBox(hwnd, TEXT("Dialog Box call FAIL"), TEXT("ERROR MESSAGE"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		COLORSTRUCT ColorStruct;
		ColorStruct.hwnd = hwnd;

		COLORSTRUCT2 ColorStruct2;
		ColorStruct2.hwnd2 = hwnd;


		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcOne, (LPVOID)&ColorStruct, 0, NULL);
		if (hThread1 == NULL)
		{
			MessageBox(hwnd, TEXT("Thread 1 creation failed "), TEXT("ERROR MSG"), MB_OK);
			DestroyWindow(hwnd);
		}
		
		hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcTwo, (LPVOID)&ColorStruct2, 0, NULL);
		if (hThread2 == NULL)
		{
			MessageBox(hwnd, TEXT("Thread 2 creation failed "), TEXT("ERROR MSG"), MB_OK);
			DestroyWindow(hwnd);
		}
			
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		hBrush = CreateSolidBrush(RGB(R, G, B));

		FillRect(hdc, &rc, hBrush);
		break;

	case WM_DESTROY:
		CloseHandle(hThread1);
		CloseHandle(hThread2);
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


	//while (true)
	//{
	//	for (int p = 0; p < 255; p++)
	//	{
	//		R = p;
	//		InvalidateRect(hwnd, NULL, TRUE);
	//		Sleep(25);
	//	}
	//	for (int q = 0; q < 255; q++)
	//	{
	//		G = q;
	//		InvalidateRect(hwnd, NULL, TRUE);
	//		Sleep(25);
	//	}
	//	for (int r = 0; r < 255; r++)
	//	{
	//		B = r;
	//		InvalidateRect(hwnd, NULL, TRUE);
	//		Sleep(25);
	//	}
	//}

	if (gender == 1)
	{
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
		}
	}
	else if(gender == 2)
	{
		while (true)
		{
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
	}

	return 0;
}

DWORD WINAPI MyThreadProcTwo(LPVOID param)
{
	COLORSTRUCT2 *PColorStruct = (PCOLORSTRUCT2)param;

	hwnd = PColorStruct->hwnd2;

	if (DialogBox((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(DATAENTRY), hwnd, (DLGPROC)MyDlgProc) == IDOK)
	{
			MessageBox(hwnd, TEXT("MSG"), TEXT("SUCCESS"), MB_OK);
	}
	else
	{
		MessageBox(hwnd, TEXT("Dialog Box call FAIL"), TEXT("ERROR MESSAGE"), MB_OK | MB_ICONERROR);
		DestroyWindow(hwnd);
	}
	//InvalidateRect(hwnd, FALSE, NULL);

	return 0;
}


BOOL CALLBACK MyDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[500];
	INPUT_DATA ip;

	TCHAR status[10];
	TCHAR Gender[10];

	int err;
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

			if (gender == 1)
				wsprintf(Gender, TEXT("FEMALE"));
			else
				wsprintf(Gender, TEXT("MALE"));

			wsprintf(str, TEXT(" Entered Name : %s \n Entered Address : %s \n Entered Age : %s \n Entered Status : %s \n  Gender : %s \n"), ip.name, ip.address, ip.age, status,Gender);
			MessageBox(hwnd, str, TEXT("TITLE"), MB_OK);

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


BOOL CALLBACK MyDlgProc2(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	CHOICE_CH ch;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hwnd, ID_ETNAME));
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			ch.choice = SendDlgItemMessage(hwnd, ID_RBFEMALE, BM_GETCHECK, 0, 0);
			if (ch.choice)
				gender = 1;
			else
				gender = 2;

			EndDialog(hwnd, wParam);
			return TRUE;

		case IDCANCEL:
			EndDialog(hwnd, wParam);
			return TRUE;
		}
	}
	return FALSE;
}
