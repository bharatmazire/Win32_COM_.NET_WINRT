#include<windows.h>
#include "Header.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI MyThreadProcOne(LPVOID);
DWORD WINAPI MyThreadProcTwo(LPVOID);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);

typedef struct InputData
{
	CHAR name[50], address[50], age[3];
	INT status;
}INPUT_DATA;


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


		COLORSTRUCT ColorStruct;
		ColorStruct.hwnd = hwnd;

		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcOne, (LPVOID)&ColorStruct, 0, NULL);
		if (hThread1 == NULL)
		{
			MessageBox(hwnd, TEXT("Thread 1 creation failed "), TEXT("ERROR MSG"), MB_OK);
			DestroyWindow(hwnd);
		}
		hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcTwo, (LPVOID)&ColorStruct, 0, NULL);
		if (hThread2 == NULL)
		{
			MessageBox(hwnd, TEXT("Thread 2 creation failed "), TEXT("ERROR MSG"), MB_OK);
			DestroyWindow(hwnd);
		}
		
		//InvalidateRect(hwnd, FALSE, NULL);


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
		for (int r = 0; r < 255; r++)
		{
			B = r;
			InvalidateRect(hwnd, NULL, TRUE);
			Sleep(25);
		}
	}

	return 0;
}

DWORD WINAPI MyThreadProcTwo(LPVOID param)
{
	COLORSTRUCT *PColorStruct = (PCOLORSTRUCT)param;

	hwnd = PColorStruct->hwnd;

	if (DialogBox((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(DATAENTRY), hwnd, (DLGPROC)MyDlgProc) == IDOK)
	{
			MessageBox(hwnd, TEXT("MSG"), TEXT("SUCCESS"), MB_OK);
	}
	else
	{
		MessageBox(hwnd, TEXT("Dialog Box call FAIL"), TEXT("ERROR MESSAGE"), MB_OK | MB_ICONERROR);
		DestroyWindow(hwnd);
	}
	InvalidateRect(hwnd, FALSE, NULL);

	return 0;
}


BOOL CALLBACK MyDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[500];
	INPUT_DATA ip;

	TCHAR status[10];
	int fileHandle = 0;
	unsigned    bytesWritten = 0;


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
			wsprintf(str, TEXT(" Entered Name : %s \n Entered Address : %s \n Entered Age : %s \n Entered Status : %s"), ip.name, ip.address, ip.age, status);
			MessageBox(hwnd, str, TEXT("TITLE"), MB_OK);


			EndDialog(hwnd, wParam);
			return TRUE;

		case IDCANCEL:
			EndDialog(hwnd, wParam);
			return TRUE;
		}
	}
	return FALSE;
}

