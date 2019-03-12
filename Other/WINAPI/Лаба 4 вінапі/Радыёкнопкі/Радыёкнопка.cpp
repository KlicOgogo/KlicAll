#undef UNICODE
#include <windows.h>
#include <string>
#include <wingdi.h>
#include <winuser.h>
#include <vector>
#include "resource.h"

using namespace std;

struct Infa
{
	int cx;
	int cy;
	int rad;
	int re;
	int gr;
	int bl;
	int wi;
	Infa(int x1, int y1, int re1, int gr1, int bl1, int wi1, int rad=80): cx(x1), cy(y1), re(re1), gr(gr1), bl(bl1), wi(wi1), rad(rad){}
};

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgProc1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

int xx=255, yy=255, zz=255, tt=1;

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "ƒы€лаг≥ ≥ радыЄкнопк≥";

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
  MSG msg;
  /*хот€ параметр hPrevInstance в Win32 всегда равно NULLпродолжаем провер€ть его значение */
  if (!hPrevInstance) 
  {  /* инициализируем приложение -  подготавливаем данные класса окна и регистрируем его */
    if (!InitApplication(hInstance)) 
      return (FALSE);
  }
   /* завершаем создание копии приложени€ -     создаем главное окно приложени€ */
  if (!InitInstance(hInstance, nCmdShow)) 
    return (FALSE);  
  
  /* ÷икл обработки сообщений */
  while (GetMessage(&msg, NULL, 0, 0)) 
  {   	TranslateMessage(&msg);
    		DispatchMessage(&msg);
  }
  return (msg.wParam);
}

BOOL InitApplication(HINSTANCE hInstance)
{
  WNDCLASS  wc;
  // «аполн€ем структуру класса окна WNDCLASS
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(NULL, IDI_ASTERISK);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_3DSHADOW;
  wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);
  wc.lpszClassName = szClassName;
  // –егистрируем класс окна
  return RegisterClass(&wc);
} 
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND hWnd;
  hWnd = CreateWindow(
    szClassName,         // указатель на строку зарегистрированного имени класса
    szTitle,             // указатель на заголовка окна
    WS_OVERLAPPEDWINDOW, // стиль окна
    10,       // горизонтальна€ координата окна
    10,       // вертикальна€ координата окна
    1000,       // ширина окна
    500,       // высота окна
    NULL,                // дескриптор родительского окна
    NULL,                // дескриптор меню окна
    hInstance,           // дескриптор экземпл€ра приложени€
    NULL);               // указатель на дополнительные данные окна

  if (!hWnd)    return (FALSE); 
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  return (TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static int x, y;
	static HDC hDC;
	static vector<Infa> infa;
	static HINSTANCE hInstance;
	static HPEN hpen;

 switch(message)
  {
 case WM_COMMAND:
{
	switch (LOWORD(wParam))
	{
	case ID_SETCOLOR:
		DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc); 
		break;
	case ID_SETLINEWIDTH:
		DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, DlgProc1);
		break;
	}
	break;
}
 case WM_LBUTTONDOWN:
	  {
	  x=LOWORD(lParam);
	  y=HIWORD(lParam);
	  int count=0;
	  if(infa.size()!=0)
	  {
		  for (int t=0; t<infa.size(); t++)
		  {	
			  HRGN round=CreateEllipticRgn(infa[t].cx-infa[t].rad, infa[t].cy-infa[t].rad, infa[t].cx+infa[t].rad, infa[t].cy+infa[t].rad);
			  if (PtInRegion(round, x, y))
			  {	
				  infa[t].rad+=20;
				  count++;
			  }
		  }
	  }
	  if (count==0)
			infa.push_back(Infa(x, y, xx, yy, zz, tt));
	  InvalidateRect (hwnd, NULL, true);
	  break;
 }
  case WM_PAINT:
	  hDC = BeginPaint(hwnd, &ps);
	  for (int j=0; j<infa.size(); j++)
	   {
		   HBRUSH hbrush=CreateSolidBrush(RGB(infa[j].re, infa[j].gr, infa[j].bl));
		   HBRUSH hbrush2=(HBRUSH)SelectObject(hDC, hbrush);
		   hpen=CreatePen(PS_SOLID, infa[j].wi, RGB(0,0,0));
		   SelectObject(hDC, hpen);
		   Ellipse (hDC, infa[j].cx-infa[j].rad, infa[j].cy-infa[j].rad, infa[j].cx+infa[j].rad, infa[j].cy+infa[j].rad);
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
			{}
		case IDC_RADIO1:
			{
				zz=0;
				xx=255;
				yy=255;
				break;
			}
		case IDC_RADIO2:
			{
				zz=0;
				xx=255;
				yy=0;
				break;
			}	
		//еще кнопки
		}
	}
	return (INT_PTR)FALSE;
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
				tt=3;
				break;
			}
		case IDC_RADIO2:
			{
				tt=6;
				break;
			}	
		//еще кнопки
		}
	}
	return (INT_PTR)FALSE;
}