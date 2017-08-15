#undef UNICODE
#include <fstream>
#include <windows.h>
#include <string>
#include <wingdi.h>
#include <winuser.h>
#include <vector>
#include <cmath>
#include "resource.h"
#include <iostream>

using namespace std;

struct Sect
{
	int numb;
	HBRUSH hbro;
	Sect(int n, HBRUSH h): numb(n), hbro(h){}
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutDlgProc(HWND , UINT, WPARAM, LPARAM);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "ƒы€грама";

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE HPrevInst, LPSTR lpCmdLine, int nCmdShow)
{		
HWND hwnd;
HACCEL haccel;
	MSG msg;
	WNDCLASS wcApp;
	// «аполн€ем структуру класса окна 
	wcApp.lpszClassName = szClassName;
	wcApp.hInstance		= hInstance;   
	wcApp.lpfnWndProc	= WndProc;
	wcApp.hCursor		= LoadCursor(NULL,IDC_ARROW);
	wcApp.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcApp.lpszMenuName	= NULL;//MAKEINTRESOURCE (IDR_MENU1);
	wcApp.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcApp.style			= CS_HREDRAW; //| CS_VREDRAW;
	wcApp.cbClsExtra	= 0;
	wcApp.cbWndExtra	= 0;
	
// –егистрируем класс окна
	if (!RegisterClass(&wcApp)){
		MessageBox(NULL, "Class hasn't been registered", "RegisterClass", MB_OK);
		return 0;
	}

	hwnd=CreateWindow(szClassName, szTitle, WS_OVERLAPPEDWINDOW,
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
	static double sum=0;
	PAINTSTRUCT ps;
	HBRUSH hbr;
	static int sx, sy;
	HDC hdc;
	static vector<int> num;
	static vector <Sect> sects;
	static RECT rect;
	POINT point;
	static int k=0;
	static double ang1=0;
	static double ang2=0;
 switch(message)
  {
  case WM_SIZE:
	  sx=LOWORD(lParam);
	  sy=HIWORD(lParam);  
	  break;
  case WM_CREATE:
	  {
	 ifstream in("Text.txt");
	while (!in.eof())
	{
		int a;
		in>>a;
		if (a!=0)
		num.push_back(a);
	}
	for (int i=0; i<num.size(); i++)
	sum+=num[i];
	for (int i=0; i<num.size(); i++)
		sects.push_back(Sect(num[i], CreateSolidBrush(RGB(rand()%256, rand()%256, rand()%256,))));
	break;
	  }
  case WM_RBUTTONDOWN:
	  point.x=LOWORD(lParam);
	  point.y=HIWORD(lParam);
	  break;
  case WM_PAINT:
	  hdc = BeginPaint(hwnd, &ps);
	  GetClientRect(hwnd, &rect);
	  sy=rect.bottom;
	  sx=rect.right;
	  SetViewportOrgEx(hdc, sx/2, sy/2, NULL);
	//  Ellipse(hdc, sx/2-sy/2, sy/2-sy/2, sx/2+sy/2, sy/2+sy/2);//
	  for (int i=0; i<sects.size(); i++)
	  {
		  SelectObject(hdc, sects[i].hbro);
		  ang1+=sects[i].numb;
		  hbr=sects[i].hbro;
		  Pie(hdc, -sy/2, -sy/2, sy/2, sy/2, (sy/2)*sin(2*3.1415926*ang2/sum), (sy/2)*cos(2*3.1415926*ang2/sum), (sy/2)*sin(2*3.1415926*ang1/sum), (sy/2)*cos(2*3.1415926*ang1/sum));
		  ang2=ang1;
		  k++;
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
