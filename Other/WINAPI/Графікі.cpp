#undef UNICODE
#include <windows.h>
#include <string>
#include <wingdi.h>
#include <winuser.h>
#include <vector>
#include <cmath>

using namespace std;

struct Points
{
	double x;
	double y;
	Points(double x1, double y1): x(x1), y(y1) {}
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Графікі малякаем";

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
	HDC hdc, hDC;
	static double x1, y1, x2, y2, x3, y3, x11, y11;
	static char out[10], outx[100], outy[100];
	vector<Points> point, point1, point2;
	vector<Points>::iterator it;
	static bool yeah=false;
 switch(message)
  {
  case WM_SIZE:
	  sx=LOWORD(lParam);
	  sy=HIWORD(lParam);  
	  break;
  case WM_LBUTTONDOWN:
	  x1=LOWORD(lParam);
	  y1=HIWORD(lParam);
	  break;

  case WM_RBUTTONDOWN:
	  x11=LOWORD(lParam);
	  y11=HIWORD(lParam);
	  yeah=true;
	  InvalidateRect(hwnd, NULL, true);
	  break;
  case WM_LBUTTONUP:
	  x2=LOWORD(lParam);
	  y2=HIWORD(lParam);
	  InvalidateRect(hwnd, NULL, true);
  case WM_PAINT:
	  hdc = BeginPaint(hwnd, &ps);
	  if (x1==x2)
	  {
		  for (double t=sx/2; t<=sx; t+=0.5*sx/1200)
			  point.push_back(Points(t, sy/2+(t-sx/2)*(t-sx/2)/sx));
		  for (it=point.begin(); it!=(--point.end()); it++)
		  {
			  MoveToEx(hdc, it->x, it->y, NULL);
			  LineTo(hdc, (it+1)->x, (it+1)->y);
		  }
		  for (double t=sx/2; t>=0; t-=0.5*sx/1200)
			  point1.push_back(Points(t, sy/2+(t-sx/2)*(t-sx/2)/sx));
		  for (it=point1.begin(); it!=(--point1.end()); it++)
		  {
			  MoveToEx(hdc, it->x, it->y, NULL);
			  LineTo(hdc, (it+1)->x, (it+1)->y);
		  }
	  }
	  if (x1>x2)
	  {
		  if (x1>sx/2 && x2>=sx/2)
		  {
			  for (double t=x2; t<=x1+(x1-x2)/2; t+=0.5*sx/1200)
				  point.push_back(Points((t+sx/2-x1/2-x2/2-(x1-x2)/4), sy/2+((t-sx/2)*(t-sx/2)/sx)/1.5-(x1+(x1-x2)/2-sx/2)*(x1+(x1-x2)/2-sx/2)/sx/2/1.5-(x2-sx/2)*(x2-sx/2)/sx/2/1.5));
			  for (it=point.begin(); it!=(--point.end()); it++)
			  {
				  MoveToEx(hdc, it->x, it->y, NULL);
				  LineTo(hdc, (it+1)->x, (it+1)->y);
			  }
		  }
		  if (x1>sx/2 && x2<sx/2)
		  {
			  for (double t=sx/2; t>=x2-(x1-x2)/4; t-=0.5*sx/1200)
				  point1.push_back(Points(t+sx/2-x1/2-x2/2, sy/2+(t-sx/2)*(t-sx/2)/sx/1.5-(x1-sx/2)*(x1-sx/2)/sx/2/1.5-(x2-sx/2)*(x2-sx/2)/sx/2/1.5));
			  for (it=point1.begin(); it!=(--point1.end()); it++)
			  {
				  MoveToEx(hdc, it->x, it->y, NULL);
				  LineTo(hdc, (it+1)->x, (it+1)->y);
			  }
			  for (double t=sx/2; t<=x1+(x1-x2)/4; t+=0.5*sx/1200)
				  point.push_back(Points(t+sx/2-x1/2-x2/2, sy/2+(t-sx/2)*(t-sx/2)/sx/1.5-(x1-sx/2)*(x1-sx/2)/sx/2/1.5-(x2-sx/2)*(x2-sx/2)/sx/2/1.5));
			  for (it=point.begin(); it!=(--point.end()); it++)
			  {
				  MoveToEx(hdc, it->x, it->y, NULL);
				  LineTo(hdc, (it+1)->x, (it+1)->y);
			  }
		  }
		  if (x1<=sx/2 && x2<sx/2)
		  {
			  for (double t=x1; t>=x2-(x1-x2)/2; t-=0.5*sx/1200)
				  point2.push_back(Points(t+sx/2-x1/2-x2/2+(x1-x2)/4, sy/2+(t-sx/2)*(t-sx/2)/sx/1.5-(x1-sx/2)*(x1-sx/2)/sx/2/1.5-(x2-(x1-x2)/2-sx/2)*(x2-(x1-x2)/2-sx/2)/sx/2/1.5));
			  for (it=point2.begin(); it!=(--point2.end()); it++)
			  {
				  MoveToEx(hdc, it->x, it->y, NULL);
				  LineTo(hdc, (it+1)->x, (it+1)->y);
			  }
		  }
	  }
	  if (x1<x2)
	  {
		  if (x2>sx/2 && x1>=sx/2)
		  {
			  for (double t=x1; t<=x2+(x2-x1)/2; t+=0.5*sx/1200)
				  point.push_back(Points(t+sx/2-x1/2-x2/2-(x2-x1)/4, sy/2+(t-sx/2)*(t-sx/2)/sx/1.5-(x1-sx/2)*(x1-sx/2)/sx/2/1.5-(x2+(x2-x1)/2-sx/2)*(x2+(x2-x1)/2-sx/2)/sx/2/1.5));
			  for (it=point.begin(); it!=(--point.end()); it++)
			  {
				  MoveToEx(hdc, it->x, it->y, NULL);
				  LineTo(hdc, (it+1)->x, (it+1)->y);
			  }
		  }
		  if (x2>sx/2 && x1<sx/2)
		  {
			  for (double t=sx/2; t>=x1-(x2-x1)/4; t-=0.5*sx/1200)
				  point1.push_back(Points(t+sx/2-x1/2-x2/2, sy/2+(t-sx/2)*(t-sx/2)/sx/1.5-(x1-sx/2)*(x1-sx/2)/sx/2/1.5-(x2-sx/2)*(x2-sx/2)/sx/2/1.5));
			  for (it=point1.begin(); it!=(--point1.end()); it++)
			  {
				  MoveToEx(hdc, it->x, it->y, NULL);
				  LineTo(hdc, (it+1)->x, (it+1)->y);
			  }
			  for (double t=sx/2; t<=x2+(x2-x1)/4; t+=0.5*sx/1200)
				  point.push_back(Points(t+sx/2-x1/2-x2/2, sy/2+(t-sx/2)*(t-sx/2)/sx/1.5-(x1-sx/2)*(x1-sx/2)/sx/2/1.5-(x2-sx/2)*(x2-sx/2)/sx/2/1.5));
			  for (it=point.begin(); it!=(--point.end()); it++)
			  {
				  MoveToEx(hdc, it->x, it->y, NULL);
				  LineTo(hdc, (it+1)->x, (it+1)->y);
			  }
		  }
		  if (x2<=sx/2 && x1<sx/2)
		  {
			  for (double t=x2; t>=x1-(x2-x1)/2; t-=0.5*sx/1200)
				  point2.push_back(Points(t+sx/2-x1/2-x2/2+(x2-x1)/4, sy/2+(t-sx/2)*(t-sx/2)/sx/1.5-(x1-(x2-x1)/2-sx/2)*(x1-sx/2)/sx/2/1.5-(x2-(x2-x1)/2-sx/2)*(x2-sx/2)/sx/2/1.5));
			  for (it=point2.begin(); it!=(--point2.end()); it++)
			  {
				  MoveToEx(hdc, it->x, it->y, NULL);
				  LineTo(hdc, (it+1)->x, (it+1)->y);
			  }
		  }
	  }
	  MoveToEx(hdc, sx/2, 0, NULL);
	  LineTo(hdc, sx/2, sy);
	  MoveToEx(hdc, 0, sy/2, NULL);
	  LineTo(hdc, sx, sy/2);
	  if (yeah)
	  {
		  char buf[100];
		  sprintf (buf, "X: %.2f	Y: %.2f", x11-sx/2, -(x11-sx/2)*(x11-sx/2)/sx);
		  MessageBox(hwnd, buf, "Каардынаты", MB_OK);
		  yeah=false;
	  }
      break;
  case WM_DESTROY:
	  PostQuitMessage(0);
	  break;
    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
  }
 return  0;
}
