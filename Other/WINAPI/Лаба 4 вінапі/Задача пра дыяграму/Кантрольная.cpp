#undef UNICODE
#include <fstream>
#include <windows.h>
#include <string>
#include <wingdi.h>
#include <winuser.h>
#include <vector>
#include "resource1.h"
#include <iostream>

using namespace std;

struct Slupok
{
	int lik;
	HBRUSH bru;
	HRGN reg;
	string cat;
	Slupok (int l, HBRUSH b, HRGN r, string s): lik(l), bru(b), reg(r), cat(s){}
};

static vector<Slupok> slup;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Кантрольная Кліцуноў";

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
	static CHOOSECOLOR cc;
	HFONT hfont, hfont1;
	char buf[100];
	static COLORREF acc[16];
	static int max=1;
	static RECT rect;
	 vector<int> num;
	 vector <string> categ;
	PAINTSTRUCT ps;
	static int sx, sy;
	HBRUSH hbr;
	static OPENFILENAME ofn;
	static char szFile[MAX_PATH];
	HDC hdc;
	POINT point;
	static int i=0;
	static HDC hDC;
	static HINSTANCE hInstance;
 switch(message)
  {
 case WM_CREATE:
	 {
		 GetClientRect(hwnd, &rect);
	  sy=rect.bottom;
	  sx=rect.right;
	  ofn.lStructSize=sizeof(OPENFILENAME);
	  ofn.hwndOwner=hwnd;
	  ofn.lpstrFile=szFile;
	  ofn.nMaxFile=sizeof(szFile);
	  cc.lStructSize=sizeof(CHOOSECOLOR);
	  cc.hwndOwner=hwnd;
	  cc.lpCustColors=(LPDWORD)acc;
	  cc.Flags=CC_FULLOPEN | CC_SOLIDCOLOR;
	  cc.rgbResult=RGB(255,0,0);
		ifstream in("in.txt");
	while (!in.eof())
	{
		string s;
		int a;
		in >> s;
		in >> a;
		categ.push_back(s);
		num.push_back(a);
	}
	for (vector<int>::iterator it=num.begin(); it!=num.end(); it++)
	{
		if ((*it)>max)
		max=(*it);
	}
	for (int i=0; i<num.size(); i++)
		slup.push_back(Slupok(num[i], CreateSolidBrush(cc.rgbResult), CreateRectRgn(i*sx/num.size(), rect.bottom-(sy*num[i])/max, (i+1)*sx/num.size(), sy), categ[i]));
	break;
	 }
  case WM_SIZE:
	  sx=LOWORD(lParam);
	  sy=HIWORD(lParam);
	  InvalidateRect(hwnd, NULL, true);
	  break;
  case WM_COMMAND:
	  switch(LOWORD(wParam))
	  {
	  case ID_BRUSH:
		  if(ChooseColor(&cc))
		  {
			  for (int i=0; i<slup.size(); i++)
				  slup[i].bru=CreateSolidBrush(cc.rgbResult);
			  InvalidateRect(hwnd, NULL, true);
		  }
		  break;
	  case ID_EDIT:
		  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
		  break;
	  case ID_FILE:
		  {
			  strcpy(szFile, "");
		 if (GetOpenFileName(&ofn))
		 {
			 ifstream inn(szFile);
			 while (!inn.eof())
			 {
				 int a;
				 string s;
				 inn >> s;
				 inn >> a;
				 categ.push_back(s);
				 num.push_back(a);
				 for (int i=0; i<slup.size(); i++)
					 slup.clear();
				 max=0;
				 for (vector<int>::iterator it=num.begin(); it!=num.end(); it++)
				 {
					 if ((*it)>max)
						 max=(*it);
				 }

				 for (int i=0; i<num.size(); i++)
					 slup.push_back(Slupok(num[i], CreateSolidBrush(cc.rgbResult), CreateRectRgn(i*sx/num.size(), rect.bottom-(sy*num[i])/max, (i+1)*sx/num.size(), sy), categ[i]));
			 }
		 }
		 InvalidateRect(hwnd, NULL, true);
		 break;
		  }
	  }
	  break;
 case WM_RBUTTONDOWN:
	  point.x=LOWORD(lParam);
	  point.y=HIWORD(lParam);
	  for (int i=0; i<slup.size(); i++)
	  {
		  if(PtInRegion(slup[i].reg, point.x, point.y))
		  { 
			  if(ChooseColor(&cc))
				  slup[i].bru=CreateSolidBrush(cc.rgbResult);
		  }
	  }
	  InvalidateRect(hwnd, NULL, true);
	  break;
  case WM_PAINT:
	  {
	  hdc = BeginPaint(hwnd, &ps);
	  GetClientRect(hwnd, &rect);
	  sy=rect.bottom;
	  sx=rect.right;
	  	static LOGFONT lf, lf1;
	lf1.lfHeight=sy/20;
	lf1.lfWidth=sx/80;
	lf1.lfEscapement=0;
	lf1.lfOrientation=0;
	lf1.lfWeight=900;
	lf1.lfItalic=0;
	lf1.lfUnderline=0;
	lf1.lfStrikeOut=0;
	lf1.lfCharSet=5;
	lf1.lfOutPrecision=5;
	lf1.lfClipPrecision=0;
	lf1.lfQuality=0;
	lf1.lfPitchAndFamily=DEFAULT_PITCH;
	lf.lfHeight=sx/60;
	lf.lfWidth=sy/40;
	lf.lfEscapement=900;
	lf.lfOrientation=900;
	lf.lfWeight=900;
	lf.lfItalic=0;
	lf.lfUnderline=0;
	lf.lfStrikeOut=0;
	lf.lfCharSet=5;
	lf.lfOutPrecision=5;
	lf.lfClipPrecision=0;
	lf.lfQuality=0;
	lf.lfPitchAndFamily=DEFAULT_PITCH;
	hfont = CreateFontIndirect(&lf); 
	hfont1 = CreateFontIndirect(&lf1); 
	for (int i=0; i<slup.size(); i++)
	{
		SelectObject(hdc, slup[i].bru);
		Rectangle(hdc, i*sx/slup.size(), rect.bottom-(sy*slup[i].lik)/max, (i+1)*sx/slup.size(), sy);
		SelectObject(hdc, hfont1);
		TextOut (hdc, i*sx/slup.size(), rect.bottom-(sy*slup[i].lik)/max, slup[i].cat.c_str(), slup[i].cat.size());
		SelectObject(hdc, hfont);
		TextOut (hdc, i*sx/slup.size(), sy, slup[i].cat.c_str(), slup[i].cat.size());
	}
	EndPaint(hwnd, &ps);
      break;
	  }
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
	static HWND hEdit;
	switch (message)
	{
	case WM_INITDIALOG:
		{
			hEdit=GetDlgItem (hDlg,IDC_EDIT1);
			for (int i=0; i<slup.size(); i++)
			{
				char buf[100];
				strcpy( buf, slup[i].cat.c_str());
				SendDlgItemMessage (hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)&buf);
			}
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
		}
	}
	return (INT_PTR)FALSE;
}