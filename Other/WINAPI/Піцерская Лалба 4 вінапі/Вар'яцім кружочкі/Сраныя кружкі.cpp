#undef UNICODE
#include <windows.h>
#include <string>
#include <wingdi.h>
#include <winuser.h>
//#include "resource.h"

using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Такс такс такс кружкі ахах наканецта";

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
  MSG msg;
  /*хотя параметр hPrevInstance в Win32 всегда равно NULLпродолжаем проверять его значение */
  if (!hPrevInstance) 
  {  /* инициализируем приложение -  подготавливаем данные класса окна и регистрируем его */
    if (!InitApplication(hInstance)) 
      return (FALSE);
  }
   /* завершаем создание копии приложения -     создаем главное окно приложения */
  if (!InitInstance(hInstance, nCmdShow)) 
    return (FALSE);  
  
  /* Цикл обработки сообщений */
  while (GetMessage(&msg, NULL, 0, 0)) 
  {   	TranslateMessage(&msg);
    		DispatchMessage(&msg);
  }
  return (msg.wParam);
}

BOOL InitApplication(HINSTANCE hInstance)
{
  WNDCLASS  wc;
  // Заполняем структуру класса окна WNDCLASS
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(NULL, IDI_ASTERISK);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_3DSHADOW;
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = szClassName;
  // Регистрируем класс окна
  return RegisterClass(&wc);
} 
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND hWnd;
  hWnd = CreateWindow(
    szClassName,         // указатель на строку зарегистрированного имени класса
    szTitle,             // указатель на заголовка окна
    WS_OVERLAPPEDWINDOW, // стиль окна
    10,       // горизонтальная координата окна
    10,       // вертикальная координата окна
    1200,       // ширина окна
    600,       // высота окна
    NULL,                // дескриптор родительского окна
    NULL,                // дескриптор меню окна
    hInstance,           // дескриптор экземпляра приложения
    NULL);               // указатель на дополнительные данные окна

  if (!hWnd)    return (FALSE); 
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  return (TRUE);
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
	HDC hdc;
 switch(message)
  {
  case WM_SIZE:
	  sx=LOWORD(lParam);
	  sy=HIWORD(lParam);  
	  break;
  case WM_CREATE:
	  SetTimer (hwnd, 1, 100, NULL);
	  for (int i=0; i<3; i++)
		  is[i]=true;
	  break;
  case WM_LBUTTONDOWN:
	  x=LOWORD(lParam);
	  y=HIWORD(lParam);
	  for (int i=0; i<3; i++)
	  {
		  round[i]=CreateEllipticRgn((i+1)*sx/5-50, (i+1)*sy/5-50, (i+1)*sx/5+50, (i+1)*sy/5+50);
		  if (PtInRegion(round[i], x, y))
			  is[i]=false;
	  }
	  InvalidateRect(hwnd, NULL, true);
	  break;
	  case WM_RBUTTONDOWN:
	  x=LOWORD(lParam);
	  y=HIWORD(lParam);
	  for (int i=0; i<3; i++)
	  {
		  round1[i]=CreateEllipticRgn((i+1)*sx/5-80, (i+1)*sy/5-80, (i+1)*sx/5+80, (i+1)*sy/5+80);
		  if (PtInRegion(round1[i], x, y))
			  is[i]=true;
	  }
	  InvalidateRect(hwnd, NULL, true);
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
