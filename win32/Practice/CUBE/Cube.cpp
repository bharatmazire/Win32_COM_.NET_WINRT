#include<windows.h>

struct BTL
{
	int X;
	int Y;
}E;

struct BTR
{
	int X;
	int Y;
}F;

struct BBR
{
	int X;
	int Y;
}G;

struct BBL
{
	int X;
	int Y;
}H;

struct FTL
{
	int X;
	int Y;
}A;

struct FTR
{
	int X;
	int Y;
}B;

struct FBR
{
	int X;
	int Y;
}C;

struct FBL
{
	int X;
	int Y;
}D;


//int x = -50;
//int y = -50;

int x = 0;
int y = 0;

int xCount = 0;
int yCount = 0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
VOID DrawCube(HDC, BTL, BTR, BBR, BBL, FTL, FTR, FBR, FBL);

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

	// Initialization of point
/*
	E.X = 350;
	E.Y = 350;

	F.X = 500;
	F.Y = 350;

	G.X = 500;
	G.Y = 500;

	H.X = 350;
	H.Y = 500;

*/
	switch (iMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);

		lb.lbStyle = BS_SOLID;
		lb.lbColor = RGB(255, 0, 0);
		lb.lbHatch = 0;

		E.X = rc.right / 4;
		E.Y = rc.bottom / 4;

		F.X = rc.right / 2 + E.X;
		F.Y = rc.bottom / 4;

		G.X = F.X;
		G.Y = rc.bottom / 2 + F.Y;

		H.X = E.X;
		H.Y = G.Y;

/*
		A.X = E.X + 50 + x;
		A.Y = E.Y + 50 + y;

		B.X = F.X + 50 + x;
		B.Y = F.Y + 50 + y;

		C.X = G.X + 50 + x;
		C.Y = G.Y + 50 + y;

		D.X = H.X + 50 + x;
		D.Y = H.Y + 50 + y;
*/
		
		A.X = E.X + x;
		A.Y = E.Y + y;

		B.X = F.X + x;
		B.Y = F.Y + y;

		C.X = G.X + x;
		C.Y = G.Y + y;

		D.X = H.X + x;
		D.Y = H.Y + y;

			hPen = ExtCreatePen(PS_COSMETIC | PS_SOLID, 1, &lb, 0, NULL);
			DrawCube(hdc, E, F, G, H, A, B, C, D);
/*
			// Back surface
			// ... start ...
			MoveToEx(hdc, E.X, E.Y, NULL);
			LineTo(hdc, H.X, H.Y);

			MoveToEx(hdc, E.X, E.Y, NULL);
			LineTo(hdc, F.X, F.Y );

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
*/
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			y = y - 10;
			break;
		case VK_DOWN:
			y = y + 10;
			break;
		case VK_LEFT:
			x = x - 10;
			break;
		case VK_RIGHT:
			x = x + 10;
			break;
 /*
		case VK_UP:
			if (yCount < 2)
			{
				y = y - 50;
				yCount++;
			}
			else
			{
				MessageBox(hwnd, TEXT("NOT ALLOWED"), TEXT("ERROR"), MB_OK);
			}
			break;
		case VK_DOWN:
			if (yCount >0)
			{
				y = y + 50;
				yCount--;
			}
			else
			{
				MessageBox(hwnd, TEXT("NOT ALLOWED"), TEXT("ERROR"), MB_OK);
			}
			break;
		case VK_LEFT:
			if (xCount < 2)
			{
				x = x - 50;
				xCount++;
			}
			else
			{
				MessageBox(hwnd, TEXT("NOT ALLOWED"), TEXT("ERROR"), MB_OK);
			}
			break;
		case VK_RIGHT:
			if (xCount > 0)
			{
				x = x + 50;
				xCount--;
			}
			else
			{
				MessageBox(hwnd, TEXT("NOT ALLOWED"), TEXT("ERROR"), MB_OK);
			}
			break;
*/
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break; 
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

VOID DrawCube(HDC hdc, BTL E, BTR F, BBR G, BBL H, FTL A, FTR B, FBR C, FBL D)
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