#undef UNICODE
#include <windows.h>
#include <string>
#include <wingdi.h>
#include <winuser.h>
#include "resource.h"
#include <windowsx.h>

using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Такс такс такс кружкі ахах наканецта";

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE HPrevInst, LPSTR lpCmdLine, int nCmdShow)
{		
HWND hwnd;
HACCEL haccel;
	MSG msg;
	WNDCLASS wcApp;
	// Заполняем структуру класса окна 
	wcApp.lpszClassName = szClassName;
	wcApp.hInstance		= hInstance;   
	wcApp.lpfnWndProc	= WndProc;
	wcApp.hCursor		= LoadCursor(NULL,IDC_ARROW);
	wcApp.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcApp.lpszMenuName	= MAKEINTRESOURCE (IDR_MENU1);
	wcApp.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcApp.style			= CS_HREDRAW; //| CS_VREDRAW;
	wcApp.cbClsExtra	= 0;
	wcApp.cbWndExtra	= 0;
	
// Регистрируем класс окна
	if (!RegisterClass(&wcApp)){
		MessageBox(NULL, "Class hasn't been registered", "RegisterClass", MB_OK);
		return 0;
	}

	hwnd=CreateWindow(szClassName, "Simple Windows Program", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, hInstance, 0);
	ShowWindow(hwnd,SW_PARENTCLOSING /*nCmdShow*/);
	UpdateWindow(hwnd);

	haccel=LoadAccelerators (hInstance,MAKEINTRESOURCE(IDR_ACCELERATOR1));
	while (GetMessage(&msg,0,0,0)) {
		if(!TranslateAccelerator(hwnd, haccel,&msg))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	}
	return (msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static int sx, sy;
	HBRUSH hbr1, hbr2, hbr3;
	static int x, y;
	static HRGN round[3], round1[3];
	static int time=0;
	static bool is[3];
	static HMENU hmenu;
	static HINSTANCE hInstance;
	POINT point;
	HDC hdc;
	
 switch(message)
  {
 case WM_COMMAND:
	 switch (LOWORD (wParam))
	 {
	 case ID_FIRST_START:
		 is[0]=false;
		 InvalidateRect(hwnd, NULL, true);
		 break;
	 case ID_FIRST_STOP:
		 is[0]=true;
		 InvalidateRect(hwnd, NULL, true);
		 break;
	 case ID_SECOND_START:
		 is[1]=false;
		 InvalidateRect(hwnd, NULL, true);
		 break;
	 case ID_SECOND_STOP:
		 is[1]=true;
		 InvalidateRect(hwnd, NULL, true);
		 break;
	 case ID_THIRD_START:
		 is[2]=false;
		 InvalidateRect(hwnd, NULL, true);
		 break;
	 case ID_THIRD_STOP:
		 is[2]=true;
		 InvalidateRect(hwnd, NULL, true);
		 break;
	 case ID_ACCELERATORS_STARTALL:
		 for (int i=0; i<3; i++)
			 is[i]=false;
		 InvalidateRect(hwnd, NULL, true);
		 break;
	 case ID_ACCELERATORS_STOPALL:
		 for (int i=0; i<3; i++)
			 is[i]=true;
		 InvalidateRect(hwnd, NULL, true);
		 break; 
	 }
	break;
  case WM_SIZE:
	  sx=LOWORD(lParam);
	  sy=HIWORD(lParam);  
	  break;
  case WM_CREATE:
	  SetTimer (hwnd, 1, 500, NULL);
	  for (int i=0; i<3; i++)
		  is[i]=true;
	  hInstance=((LPCREATESTRUCT) lParam)->hInstance;
	  hmenu=LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
	  hmenu=GetSubMenu(hmenu, 0);
	  break;
  case WM_RBUTTONDOWN:
	  point.x=LOWORD(lParam);
	  point.y=HIWORD(lParam);
	  ClientToScreen(hwnd, &point);
	  TrackPopupMenu(hmenu, 0, point.x, point.y, 0, hwnd, NULL);
	  break;
  case WM_TIMER:
	  time++;
	  InvalidateRect(hwnd, NULL, true);
	  break;
  case WM_PAINT:
	  hdc = BeginPaint(hwnd, &ps);
	  hbr1=CreateSolidBrush(RGB(255, 0, 0));
	  hbr2=CreateSolidBrush(RGB(0, 255, 0));
	  hbr3=CreateSolidBrush(RGB(0, 0, 255));
	  SelectObject(hdc, hbr1);
	  for (int i=0; i<3; i++)
	  {
		  round[i]=CreateEllipticRgn((i+1)*sx/5-50, (i+1)*sy/5-50, (i+1)*sx/5+50, (i+1)*sy/5+50);
		  round1[i]=CreateEllipticRgn((i+1)*sx/5-80, (i+1)*sy/5-80, (i+1)*sx/5+80, (i+1)*sy/5+80);
	  }
	  FillRgn(hdc, round[0], hbr1);
	  FillRgn(hdc, round[1], hbr2);
	  FillRgn(hdc, round[2], hbr3);

	  if (time%2==0)
	  {
		  if (is[0]==true && is[1]==true && is[2]==true)
		  {
			  FillRgn(hdc, round[0], hbr1);
			  FillRgn(hdc, round[1], hbr2);
			  FillRgn(hdc, round[2], hbr3);
		  }
		  if (is[0]==true && is[1]==true && is[2]==false)
		  {
			  FillRgn(hdc, round[0], hbr1);
			  FillRgn(hdc, round[1], hbr2);
			  FillRgn(hdc, round1[2], hbr3);
		  }
		  if (is[0]==true && is[1]==false && is[2]==true)
		  {
			  FillRgn(hdc, round[0], hbr1);
			  FillRgn(hdc, round1[1], hbr2);
			  FillRgn(hdc, round[2], hbr3);
		  }
		  if (is[0]==true && is[1]==false && is[2]==false)
		  {
			  FillRgn(hdc, round[0], hbr1);
			  FillRgn(hdc, round1[1], hbr2);
			  FillRgn(hdc, round1[2], hbr3);
		  }
		  if (is[0]==false && is[1]==true && is[2]==true)
		  {
			  FillRgn(hdc, round1[0], hbr1);
			  FillRgn(hdc, round[1], hbr2);
			  FillRgn(hdc, round[2], hbr3);
		  }
		  if (is[0]==false && is[1]==true && is[2]==false)
		  {
			  FillRgn(hdc, round1[0], hbr1);
			  FillRgn(hdc, round[1], hbr2);
			  FillRgn(hdc, round1[2], hbr3);
		  }
		  if (is[0]==false && is[1]==false && is[2]==true)
		  {
			  FillRgn(hdc, round1[0], hbr1);
			  FillRgn(hdc, round1[1], hbr2);
			  FillRgn(hdc, round[2], hbr3);
		  }
		  if (is[0]==false && is[1]==false && is[2]==false)
		  {
			  FillRgn(hdc, round1[0], hbr1);
			  FillRgn(hdc, round1[1], hbr2);
			  FillRgn(hdc, round1[2], hbr3);
		  }

	  }
	  else
	  {
		  FillRgn(hdc, round[0], hbr1);
		  FillRgn(hdc, round[1], hbr2);
		  FillRgn(hdc, round[2], hbr3);
	  }
	  EndPaint(hwnd, &ps);
      break;
  case WM_DESTROY:
	  PostQuitMessage(0);
	  break;
    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
  }
 return  0;
}
