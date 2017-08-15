#undef UNICODE
#include <windows.h>
#include <string>
#include <wingdi.h>
#include <winuser.h>
#include "resource2.h"
#include <vector>

using namespace std;

struct Figure
{
	int x1, x2, y1, y2;
	COLORREF bru, pen;
	int wi, ty;
	Figure (int x3, int y3, int x4, int y4, COLORREF bru1, COLORREF pen1, int wi1, int ty1): x1(x3), y1(y3), x2(x4), y2(y4), bru(bru1), pen(pen1), wi(wi1), ty(ty1) {}  
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DlgProc1(HWND , UINT, WPARAM, LPARAM);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Пэйнт наканецта";
static int tyty=1, tt=2;

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
	wcApp.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU2);
	wcApp.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcApp.style			= CS_HREDRAW; //| CS_VREDRAW;
	wcApp.cbClsExtra	= 0;
	wcApp.cbWndExtra	= 0;
	
// Регистрируем класс окна
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
	return (msg.wParam);}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static vector<Figure> figures;
	vector<Figure>::iterator it;
	static int sx, sy, x1, y1, x2, y2;
	static int t=0;
	HDC hdc;
	static COLORREF acc[16], acc1[16];
	static HMENU hmenu;
	static HINSTANCE hInstance;
	static CHOOSECOLOR cc, cc1;
	POINT point;
 switch(message)
  {
  case WM_COMMAND:
     switch (LOWORD (wParam))
     {
	 case ID_MENU_PENWIDTH:
		 DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc1); 
		 break;
	 case ID_PAINT_ELLIPSE:
		 tyty=-1;
		 break;
	 case ID_PAINT_RECTANGLE:
		 tyty=1;
		 break;
	 case ID_MENU_BRUSHCOLOR:
		 if (ChooseColor(&cc))
		 {}
		 break;
	 case ID_MENU_PENCOLOR:
		 if (ChooseColor(&cc1))
		 {}
		 break;
     }
          break;
  case WM_SIZE:
	  sx=LOWORD(lParam);
	  sy=HIWORD(lParam);  
	  break;
  case WM_CREATE:
	  hInstance=((LPCREATESTRUCT) lParam)->hInstance;
	  hmenu=LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
	  hmenu=GetSubMenu(hmenu, 0);
	  cc.lStructSize=sizeof(CHOOSECOLOR); // диалог цвета
	  cc.hwndOwner=hwnd;
	  cc.lpCustColors=(LPDWORD)acc;
	  cc.Flags=CC_FULLOPEN | CC_SOLIDCOLOR;
	  cc.rgbResult=RGB(255,255,255);
	  cc1.lStructSize=sizeof(CHOOSECOLOR); // диалог цвета
	  cc1.hwndOwner=hwnd;
	  cc1.lpCustColors=(LPDWORD)acc;
	  cc1.Flags=CC_FULLOPEN | CC_SOLIDCOLOR;
	  cc1.rgbResult=RGB(0,0,0);
	  break;
  case WM_RBUTTONDOWN:
      point.x=LOWORD(lParam);
	  point.y=HIWORD(lParam);
	  ClientToScreen(hwnd, &point);
	  TrackPopupMenu(hmenu, 0, point.x, point.y, 0, hwnd, NULL);
	  break;
  case WM_LBUTTONDOWN:
	  x1=LOWORD(lParam);
	  y1=HIWORD(lParam);
	  InvalidateRect(hwnd, NULL, true);
	  break;
  case WM_LBUTTONUP:
	  x2=LOWORD(lParam);
	  y2=HIWORD(lParam);
	  figures.push_back(Figure(x1, y1, x2, y2, cc.rgbResult, cc1.rgbResult, tt, tyty));
	  InvalidateRect(hwnd, NULL, true);
	  break;
  case WM_PAINT:
	  hdc = BeginPaint(hwnd, &ps);
	  for (it=figures.begin(); it!=figures.end(); it++)
	  {
		  HBRUSH hbr=CreateSolidBrush(it->bru);
		  SelectObject(hdc, hbr);
		  HPEN hp=CreatePen(PS_SOLID, it->wi, it->pen);
		  SelectObject(hdc, hp);
		  if (it->ty==1)
			  Rectangle(hdc, it->x1, it->y1, it->x2, it->y2);
		  if(it->ty==-1)
			  Ellipse(hdc, it->x1, it->y1, it->x2, it->y2);
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

INT_PTR CALLBACK DlgProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
		return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		case IDCANCEL:
			{}
		case IDC_RADIO1:
			{
				tt=2;
				break;
			}
		case IDC_RADIO2:
			{
				tt=4;
				break;
			}	
		case IDC_RADIO3:
			{
				tt=6;
				break;
			}	
		//еще кнопки
		}
	}
	return (INT_PTR)FALSE;
}