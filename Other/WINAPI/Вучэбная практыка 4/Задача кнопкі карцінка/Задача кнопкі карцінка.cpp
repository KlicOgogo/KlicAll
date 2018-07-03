#undef UNICODE
#include <windows.h>
#include <string>
#include <wingdi.h>
#include <winuser.h>
#include "resource.h"

#define ID_BUTTON1 401
#define ID_BUTTON2 402
#define ID_BUTTON3 403
#define ID_BUTTON4 404
#define ID_BUTTON5 405
#define ID_BUTTON6 406
#define ID_BUTTON7 407
#define ID_BUTTON8 408
#define ID_BUTTON9 409

using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
//BOOL CALLBACK AboutDlgProc(HWND , UINT, WPARAM, LPARAM);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Кнопачкі";

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
	wcApp.lpszMenuName	= NULL;
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
	return (msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hbut[9];
	static OPENFILENAME ofn;
	static char szFile[MAX_PATH];
	PAINTSTRUCT ps;
	static RECT rect;
	static int sx, sy;
	static HBRUSH bkBrush;
	static int time=0;
	bool success;
	static HDC hdc;
	static HMENU hmenu;
	static HINSTANCE hInstance1, hInstance;
	POINT point;
	static HBITMAP hbmf;
 switch(message)
  {
  case WM_COMMAND:
     switch (LOWORD (wParam))
     {
	 case ID_BUTTON1:
	 case ID_BUTTON2:
	 case ID_BUTTON3:
	 case ID_BUTTON4:
	 case ID_BUTTON5:
	 case ID_BUTTON6:
	 case ID_BUTTON7:
	 case ID_BUTTON8:
	 case ID_BUTTON9:
		 ShowWindow(GetDlgItem(hwnd, LOWORD(wParam)), SW_HIDE);
		 break;
	 case ID_MENU_CHANGEBG:
		 {
		 strcpy(szFile, "");
		 if (GetOpenFileName(&ofn))
		 {
			 hbmf=(HBITMAP)LoadImage((HINSTANCE)(GetWindowLong(hwnd,GWL_HINSTANCE)),szFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			 bkBrush=CreatePatternBrush(hbmf);
			 SetClassLong(hwnd,GCL_HBRBACKGROUND,(LONG)bkBrush);
			 InvalidateRect(hwnd, NULL, true);
		 }
		 break;
		 }
	 case ID_MENU_MAKEBUTTONSVISIBLE:
		 for (int i=0; i<9; i++)
			 ShowWindow(GetDlgItem(hwnd, ID_BUTTON1+i), SW_NORMAL);
		 break;
	 }
		 break;
  case WM_SIZE:
	  sx=LOWORD(lParam);
	  sy=HIWORD(lParam);
	  InvalidateRect(hwnd, NULL, true);
	  break;
  case WM_CREATE:
	  GetClientRect(hwnd, &rect);
	  sy=rect.bottom;
	  sx=rect.right;
	  hdc=GetDC(hwnd);
	  hbmf=(HBITMAP)LoadImage((HINSTANCE)(GetWindowLong(hwnd,GWL_HINSTANCE)),"lalka.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	  bkBrush=CreatePatternBrush(hbmf);
	  SetClassLong(hwnd,GCL_HBRBACKGROUND,(LONG)bkBrush);
	  hbut[0]=CreateWindow("BUTTON", "кнопка 1", WS_CHILD|WS_VISIBLE, 0, 0, sx/12, sy/20, hwnd, (HMENU)ID_BUTTON1, (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE), NULL);
	  hbut[1]=CreateWindow("BUTTON", "кнопка 2", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, 0, 40, sx/12, sy/20, hwnd, (HMENU)ID_BUTTON2, (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE), NULL);
	  hbut[2]=CreateWindow("BUTTON", "кнопка 3", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, 0, 80, sx/12, sy/20, hwnd, (HMENU)ID_BUTTON3, (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE), NULL);
	  hbut[3]=CreateWindow("BUTTON", "кнопка 4", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, 0, 120, sx/12, sy/20, hwnd, (HMENU)ID_BUTTON4, (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE), NULL);
	  hbut[4]=CreateWindow("BUTTON", "кнопка 5", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, 0, 160, sx/12, sy/20, hwnd, (HMENU)ID_BUTTON5, (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE), NULL);
	  hbut[5]=CreateWindow("BUTTON", "кнопка 6", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, 0, 200, sx/12, sy/20, hwnd, (HMENU)ID_BUTTON6, (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE), NULL);
	  hbut[6]=CreateWindow("BUTTON", "кнопка 7", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, 0, 240, sx/12, sy/20, hwnd, (HMENU)ID_BUTTON7, (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE), NULL);
	  hbut[7]=CreateWindow("BUTTON", "кнопка 8", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, 0, 280, sx/12, sy/20, hwnd, (HMENU)ID_BUTTON8, (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE), NULL);
	  hbut[8]=CreateWindow("BUTTON", "кнопка 9", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, 0, 320, sx/12, sy/20, hwnd, (HMENU)ID_BUTTON9, (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE), NULL);
	  hInstance1=((LPCREATESTRUCT) lParam)->hInstance;
	  hmenu=LoadMenu(hInstance1, MAKEINTRESOURCE(IDR_MENU1));
	  hmenu=GetSubMenu(hmenu, 0);
	  ofn.lStructSize=sizeof(OPENFILENAME);
	  ofn.hwndOwner=hwnd;
	  ofn.lpstrFile=szFile;
	  ofn.nMaxFile=sizeof(szFile);
	  InvalidateRect(hwnd, NULL, true);
	  break;
  case WM_RBUTTONDOWN:
	  point.x=LOWORD(lParam);
	  point.y=HIWORD(lParam);
	  ClientToScreen(hwnd, &point);
	  TrackPopupMenu(hmenu, 0, point.x, point.y, 0, hwnd, NULL);
	  break;
  case WM_PAINT:
	  hdc = BeginPaint(hwnd, &ps);
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


INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		//еще кнопки
		}
	}
	return (INT_PTR)FALSE;
}  