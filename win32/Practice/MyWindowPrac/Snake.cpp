#include<windows.h>
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

LRESULT CALLBACK WndProc(HWND , UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("MY SNAKE APP !");
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

	hwnd = CreateWindow(szAppName, TEXT("MY SNAKE APP"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
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
	HBRUSH hBrushBlack, hBrushWhite;
	int iLen;
	int iTemp1,iTemp2;

	static int iLeft, iTop, iRight, iBottom;

	static int iLeftMove = 0;
	static int iTopMove = 0;
	static int iRightMove = 0;
	static int iBottomMove = 0;


	static int Matrix[20][20] = {0};
	//Matrix[0][0] = 1;
	static int x = 0;
	static int y = 0;

	//int i,j,err;
	TCHAR str[30],str2[30];
	//FILE *stream;
	switch (iMsg)
	{

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			iRightMove = iRightMove - 20;
			y--;
			break;
		case 'W':
			iBottomMove = iBottomMove - 20;
			x--;
			//y--;
			break;
		case 'D':
			iRightMove = iRightMove + 20;
			y++;
			break;
		case 'S':
			iBottomMove = iBottomMove + 20;
			x++;
			//y++;
			break;
		case VK_RIGHT:
			iRightMove = iRightMove + 20;
			y++;
			break;
		case VK_LEFT:
			iRightMove = iRightMove - 20;
			y--;
			break;
		case VK_UP:
			iBottomMove = iBottomMove - 20;
			x--;
			//y--;
			break;
		case VK_DOWN:
			iBottomMove = iBottomMove + 20;
			//y++;
			x++;
			break;
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		InvalidateRect(hwnd, NULL, false);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		
		iTemp1 = rc.bottom - rc.top;
		iTemp2 = rc.right - rc.left;

		if (iTemp1 < iTemp2)
			iLen = iTemp1;
		else
			iLen = iTemp2;

		if (iRightMove > iLen)
			iRightMove = 0;
		else if (iRightMove < rc.left)
			iRightMove = iLen;
		
		if (iBottomMove > iLen)
			iBottomMove = 0;
		else if (iBottomMove < 0)
			iBottomMove = iLen;

			iLeft = rc.left / 20 + iRightMove;
			iTop = rc.top / 20 + iBottomMove;
			iRight = iLen / 20 + iRightMove;
			iBottom = iLen / 20 + iBottomMove;
		
			if (y > 20)
				y = 0;
			else if (y < 0)
				y = 20;
			if (x > 20)
				x = 0;
			else if (x < 0)
				x = 20;

			//for (i = 0; i < 20; i++)
			//{
			//	for (j = 0; j < 20; j++)
			//	{
			//		wsprintf(str, "MATRIX[%d][%d] = %d \n", i, j, Matrix[i][j]);
			//		err = fopen_s(&stream, "write.txt", "a+");
			//		if (err != 0)
			//			MessageBox(hwnd, TEXT("UNABLE TO OPEN FILE"), TEXT("ERROR!!"), MB_OK);
			//		else
			//			fprintf_s(stream, "%s", str);
			//		fclose(stream);
			//	}
			//}
				wsprintf(str, "MATRIX[%d][%d] = %d \n", x, y, Matrix[x][y]);
				MessageBox(hwnd, str, TEXT("SEE"), MB_OK);
				if (Matrix[x][y] != 0)
				{
					MessageBox(hwnd, TEXT("YOU LOOS"), TEXT("OUT"), MB_OK);
					DestroyWindow(hwnd);
				}
					
				Matrix[x][y] = 1;
		
		hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, hBrushBlack);
		
		//Rectangle(hdc, rc.left, rc.top, iLen, iLen);

		hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, hBrushWhite);
		Rectangle(hdc, iLeft, iTop, iRight, iBottom);

		break;

	case WM_DESTROY:
		MessageBox(hwnd, TEXT("THANKS RU7W1K !!"), TEXT("END NOTE "), MB_OK);
		PostQuitMessage(0);
		break;
	
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}



