#include<windows.h>

struct XYPOINT
{
	double X;
	double Y;
}E,F,G,H,A,B,C,D;

// Declaring points of cube
double PointEX[8][3] = { {0,100,0},{100,100,0},{100,0,0}, {0,0,0},{0,100,0},{100,100,0},{100,0,0}, {0,0,0} };
/*
int PointE[3] = { 0,100,0 };
int PointF[3] = { 100,100,0 };
int PointG[3] = { 100,0,0 };
int PointH[3] = { 0,0,0 };
int PointA[3] = { 0,100,0 };
int PointB[3] = { 100,100,0 };
int PointC[3] = { 100,0,0 };
int PointD[3] = { 0,0,0 };
*/

int iInitialX;
int iInitialY;
int iInitialZ;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
VOID DrawCube(HDC, XYPOINT, XYPOINT, XYPOINT, XYPOINT, XYPOINT, XYPOINT, XYPOINT, XYPOINT);
//VOID RotateAlongX(INT);
VOID RotateAlongY(INT,HWND);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("CUBE");
	HWND hwnd;
	MSG msg;

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL, TEXT("Class Registration Failed"), TEXT("ERROR MESSAGE"), MB_OK | MB_ICONERROR);
		return -1;
	}

	hwnd = CreateWindow(szAppName, TEXT("CUBE"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	HGDIOBJ hPen = NULL;
	LOGBRUSH lb;

	switch (iMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);

		lb.lbStyle = BS_SOLID;
		lb.lbColor = RGB(0, 0, 0);
		lb.lbHatch = 0;
		
		iInitialX = rc.right / 2;
		iInitialY = rc.bottom / 2;
		iInitialZ = rc.right / 2;


		E.X = iInitialX + PointEX[0][0];
		E.Y = iInitialY + PointEX[0][1];

		F.X = iInitialX + PointEX[1][0];
		F.Y = iInitialY + PointEX[1][1];

		G.X = iInitialX + PointEX[2][0];
		G.Y = iInitialY + PointEX[2][1];

		H.X = iInitialX + PointEX[3][0];
		H.Y = iInitialY + PointEX[3][1];

		A.X = iInitialX + PointEX[4][0];
		A.Y = iInitialY + PointEX[4][1];

		B.X = iInitialX + PointEX[5][0];
		B.Y = iInitialY + PointEX[5][1];

		C.X = iInitialX + PointEX[6][0];
		C.Y = iInitialY + PointEX[6][1];

		D.X = iInitialX + PointEX[7][0];
		D.Y = iInitialY + PointEX[7][1];
/*
		E.X = iInitialX + PointE[0];
		E.Y = iInitialY + PointE[1];

		F.X = iInitialX + PointF[0];
		F.Y = iInitialY + PointF[1];

		G.X = iInitialX + PointG[0];
		G.Y = iInitialY + PointG[1];

		H.X = iInitialX + PointH[0];
		H.Y = iInitialY + PointH[1];

		A.X = iInitialX + PointA[0];
		A.Y = iInitialY + PointA[1];

		B.X = iInitialX + PointB[0];
		B.Y = iInitialY + PointB[1];

		C.X = iInitialX + PointC[0];
		C.Y = iInitialY + PointC[1];

		D.X = iInitialX + PointD[0];
		D.Y = iInitialY + PointD[1];
		*/

		hPen = ExtCreatePen(PS_COSMETIC | PS_SOLID, 1, &lb, 0, NULL);
		DrawCube(hdc, E, F, G, H, A, B, C, D);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
/*
		case VK_UP:
			y = y - 10;
			break;
		case VK_DOWN:
			y = y + 10;
			break;
*/
		case VK_LEFT:
			MessageBox(hwnd, TEXT("Hi"), TEXT("<- "), MB_OK);
			RotateAlongY(30,hwnd);
			break;
		case VK_RIGHT:
			MessageBox(hwnd, TEXT("Hi"), TEXT(" ->"), MB_OK);
			RotateAlongY(270,hwnd);
			break;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

VOID DrawCube(HDC hdc, XYPOINT E, XYPOINT F, XYPOINT G, XYPOINT H, XYPOINT A, XYPOINT B, XYPOINT C, XYPOINT D)
{
	MoveToEx(hdc, E.X, E.Y, NULL);
	LineTo(hdc, H.X, H.Y);

	MoveToEx(hdc, E.X, E.Y, NULL);
	LineTo(hdc, F.X, F.Y);

	MoveToEx(hdc, G.X, G.Y, NULL);
	LineTo(hdc, H.X, H.Y);

	MoveToEx(hdc, G.X, G.Y, NULL);
	LineTo(hdc, F.X, F.Y);
	// ... End ...

	// Front face 
	// ... Start ...
	MoveToEx(hdc, A.X, A.Y, NULL);
	LineTo(hdc, D.X, D.Y);

	MoveToEx(hdc, A.X, A.Y, NULL);
	LineTo(hdc, B.X, B.Y);

	MoveToEx(hdc, C.X, C.Y, NULL);
	LineTo(hdc, D.X, D.Y);

	MoveToEx(hdc, C.X, C.Y, NULL);
	LineTo(hdc, B.X, B.Y);


	// ... end ...

	// Surface Joining line
	// ... start ...
	MoveToEx(hdc, E.X, E.Y, NULL);
	LineTo(hdc, A.X, A.Y);

	MoveToEx(hdc, F.X, F.Y, NULL);
	LineTo(hdc, B.X, B.Y);

	MoveToEx(hdc, G.X, G.Y, NULL);
	LineTo(hdc, C.X, C.Y);

	MoveToEx(hdc, H.X, H.Y, NULL);
	LineTo(hdc, D.X, D.Y);

	// .. end ...
}

VOID RotateAlongY(INT Degree,HWND hwnd)
{
	TCHAR str[1000];
	double sin, cos;
	if (Degree == 30)
	{
		sin = 0.5;
		cos = 0.866;
	}
	else
	{
		sin = -1;
		cos = 0;
	}

	double y[3][3] = { {cos,0,sin},{0,1,0},{-sin,0,cos} };
//	int y2[3] = {0,1,0};
//	int y3[3] = {-sin,0,cos};
//	int temp = 0;

	for (int k = 0; k < 8; k++)
	{
		
		for (int l = 0; l < 3; l++)
		{
			double temp = 0;
			for (int m = 0; m < 3; m++)
			{
				temp += y[l][m] * PointEX[k][m];
			}
			PointEX[k][l] = temp;
			wsprintf(str, "%d ", temp);
			MessageBox(hwnd, str, TEXT("str"), MB_OK);
		}
	}
	
}
