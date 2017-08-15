#undef UNICODE
#include <windows.h>
#include <string>
#include <wingdi.h>
#include <winuser.h>
#include <vector>

using namespace std;

struct Infa
{
	int cx;
	int cy;
	int rad;
	Infa(int x1, int y1, int rad=80): cx(x1), cy(y1), rad(rad){}
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Мышкай ціскаць";

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
    1000,       // ширина окна
    500,       // высота окна
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
	static int x, y;
	static HDC hDC;
	static vector<Infa> infa;
	static int x1, y1, z1;

 switch(message)
  {
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
			infa.push_back(Infa(x, y));
	  InvalidateRect (hwnd, NULL, true);
	  break;
 }
  case WM_PAINT:
	  hDC = BeginPaint(hwnd, &ps);
	   for (int j=0; j<infa.size(); j++)
	   {
		HBRUSH hbrush=CreateSolidBrush(RGB(x1, y1, z1));
		HBRUSH hbrush2=(HBRUSH)SelectObject(hDC, hbrush);
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
