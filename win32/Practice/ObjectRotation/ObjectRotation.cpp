#include<windows.h>

struct XYPOINT
{
	int X;
	int Y;
}E,F,G,H,A,B,C,D;

// Declaring points of cube
double PointEX[8][3] = { {0,100,0},{100,100,0},{100,0,0}, {0,0,0},{0,100,100},{100,100,100},{100,0,100}, {0,0,100} };
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

int t = 100; // for time 

double y[3][3];

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
VOID DrawCube(HDC, XYPOINT, XYPOINT, XYPOINT, XYPOINT, XYPOINT, XYPOINT, XYPOINT, XYPOINT);
VOID RotateAlong(INT,INT,HWND);
DWORD WINAPI MyThreadProcOne(LPVOID);
DWORD WINAPI MyThreadProcTwo(LPVOID);
DWORD WINAPI MyThreadProcThree(LPVOID);
//VOID RotateAlongY(INT,HWND);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("CUBE");
	HWND hwnd;
	MSG msg;

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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
	HPEN hPen;

	static HANDLE hThread1 = NULL;
	static HANDLE hThread2 = NULL;
	static HANDLE hThread3 = NULL;

	switch (iMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		
		iInitialX = rc.right / 2;
		iInitialY = rc.bottom / 2;
		iInitialZ = rc.right / 2;


		E.X = iInitialX + (int) PointEX[0][0];
		E.Y = iInitialY + (int) PointEX[0][1];
						  
		F.X = iInitialX + (int) PointEX[1][0];
		F.Y = iInitialY + (int) PointEX[1][1];
						  
		G.X = iInitialX + (int) PointEX[2][0];
		G.Y = iInitialY + (int) PointEX[2][1];
						  
		H.X = iInitialX + (int) PointEX[3][0];
		H.Y = iInitialY + (int) PointEX[3][1];
						  
		A.X = iInitialX + (int) PointEX[4][0] ;
		A.Y = iInitialY + (int) PointEX[4][1] ;
						  
		B.X = iInitialX + (int) PointEX[5][0] ;
		B.Y = iInitialY + (int) PointEX[5][1] ;
						  
		C.X = iInitialX + (int) PointEX[6][0] ;
		C.Y = iInitialY + (int) PointEX[6][1] ;
						  
		D.X = iInitialX + (int) PointEX[7][0] ;
		D.Y = iInitialY + (int) PointEX[7][1] ;
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

		//hPen = ExtCreatePen(PS_COSMETIC | PS_SOLID, 1, &lb, 0, NULL);
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		SelectObject(hdc,hPen);
		DrawCube(hdc, E, F, G, H, A, B, C, D);
		DeleteObject(hPen);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'X': // add flag so that x , y , z can be pressed only once
			hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcOne, (LPVOID)hwnd, 0, NULL);
			break;
		case 'Y':
			hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcTwo, (LPVOID)hwnd, 0, NULL);
			break;
		case 'Z':
			hThread3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcThree, (LPVOID)hwnd, 0, NULL);
			break;

		case VK_UP:
			RotateAlong(10,0,hwnd);
			break;
		//case VK_DOWN:
		//	RotateAlong(-10,0,hwnd);
		//	break;
		case VK_LEFT:
			RotateAlong(10,1,hwnd);
			break;
		//case VK_RIGHT:
		//	RotateAlong(-10,1,hwnd);
		//	break;
		case 'A':
			RotateAlong(10, 2, hwnd);
			break;
		//case 'D':
		//	RotateAlong(-10, 2, hwnd);
		//	break;
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
	// Back Face
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

VOID RotateAlong(INT Degree,INT Axis,HWND hwnd)
{
	double TempPointEX[8][3] = {0};


	double sin, cos;
	if (Degree == 10)
	{
		sin = 0.1736481776;
		cos = 0.9848077530;
	}
	else
	{
		sin = -0.1736481776;
		cos = -0.9848077530;
	}


	if (Axis == 0)
	{
		double y[3][3] = { { 1,0,0 },{ 0,cos,-sin },{ 0,sin,cos } };
		for (int k = 0; k < 8; k++)
		{

			for (int l = 0; l < 3; l++)
			{
				double temp = 0;
				for (int m = 0; m < 3; m++)
				{
					temp += y[l][m] * PointEX[k][m];
				}
				TempPointEX[k][l] = temp;
			}
		}
	
	}
	else if (Axis == 1)
	{
		double y[3][3] = { { cos,0,sin },{ 0,1,0 },{ -sin,0,cos } };
		for (int k = 0; k < 8; k++)
		{

			for (int l = 0; l < 3; l++)
			{
				double temp = 0;
				for (int m = 0; m < 3; m++)
				{
					temp += y[l][m] * PointEX[k][m];
				}
				TempPointEX[k][l] = temp;
			}
		}
	}
	else
	{
		double y[3][3] = { { cos,-sin,0 },{ sin,cos,0 },{ 0,0,1 } };
		for (int k = 0; k < 8; k++)
		{

			for (int l = 0; l < 3; l++)
			{
				double temp = 0;
				for (int m = 0; m < 3; m++)
				{
					temp += y[l][m] * PointEX[k][m];
				}
				TempPointEX[k][l] = temp;
			}
		}
	}

//	double y[3][3] = { {cos,0,sin},{0,1,0},{-sin,0,cos} };
/*
	for (int k = 0; k < 8; k++)
	{
		
		for (int l = 0; l < 3; l++)
		{
			double temp = 0;
			for (int m = 0; m < 3; m++)
			{
				temp += y[l][m] * PointEX[k][m];
			}
			TempPointEX[k][l] = temp;
		}
	}
*/

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			PointEX[i][j] = TempPointEX[i][j];
		}
	}
}

/*
VOID RotateAlongX(INT Degree, HWND hwnd)
{
	TCHAR str[1000];
	double TempPointEX[8][3] = { 0 };

	double sin, cos;
	if (Degree == 30)
	{
		sin = 0.5;
		cos = 0.86;
	}
	else
	{
		sin = -0.5;
		cos = -0.86;
	}

//	double y[3][3] = { { 1,0,0 },{ 0,cos,-sin },{ 0,sin,cos } };

	for (int k = 0; k < 8; k++)
	{

		for (int l = 0; l < 3; l++)
		{
			double temp = 0;
			for (int m = 0; m < 3; m++)
			{
				temp += y[l][m] * PointEX[k][m];
			}
			TempPointEX[k][l] = temp;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			PointEX[i][j] = TempPointEX[i][j];
		}
	}
}
*/
 
DWORD WINAPI MyThreadProcOne(LPVOID param)
{
	double TempPointEX[8][3] = { 0 };
	HWND hwnd = (HWND)param;
	double	sin = 0.1736481776;
	double	cos = 0.9848077530;

	double y[3][3] = { { 1,0,0 },{ 0,cos,-sin },{ 0,sin,cos } }; 
	while (1)
	{
		for (int k = 0; k < 8; k++)
		{

			for (int l = 0; l < 3; l++)
			{
				double temp = 0;
				for (int m = 0; m < 3; m++)
				{
					temp += y[l][m] * PointEX[k][m];
				}
				TempPointEX[k][l] = temp;
			}
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				PointEX[i][j] = TempPointEX[i][j];
			}
		}

		Sleep(t);
		InvalidateRect(hwnd, NULL, TRUE);
	}
	return 0;
}


DWORD WINAPI MyThreadProcTwo(LPVOID param)
{
	double TempPointEX[8][3] = { 0 };
	HWND hwnd = (HWND)param;
	double	sin = 0.1736481776;
	double	cos = 0.9848077530;

	double y[3][3] = { { cos,0,sin },{ 0,1,0 },{ -sin,0,cos } };

	while (1)
	{
		for (int k = 0; k < 8; k++)
		{

			for (int l = 0; l < 3; l++)
			{
				double temp = 0;
				for (int m = 0; m < 3; m++)
				{
					temp += y[l][m] * PointEX[k][m];
				}
				TempPointEX[k][l] = temp;
			}
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				PointEX[i][j] = TempPointEX[i][j];
			}
		}

		Sleep(t);
		InvalidateRect(hwnd, NULL, TRUE);
	}
	return 0;
}

DWORD WINAPI MyThreadProcThree(LPVOID param)
{
	double TempPointEX[8][3] = { 0 };
	HWND hwnd = (HWND)param;
	double	sin = 0.1736481776;
	double	cos = 0.9848077530;

	double y[3][3] = { { cos,-sin,0 },{ sin,cos,0 },{ 0,0,1 } };
	while (1)
	{
		for (int k = 0; k < 8; k++)
		{

			for (int l = 0; l < 3; l++)
			{
				double temp = 0;
				for (int m = 0; m < 3; m++)
				{
					temp += y[l][m] * PointEX[k][m];
				}
				TempPointEX[k][l] = temp;
			}
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				PointEX[i][j] = TempPointEX[i][j];
			}
		}

		Sleep(t);
		InvalidateRect(hwnd, NULL, TRUE);
	}
	return 0;
}

