#include <afxwin.h>
#include <afxdlgs.h>
#include "resource.h"
#include "Dialog.h"

class MyWin : public CFrameWnd
{
public:
	int draw, n;
	COLORREF color;
	HBRUSH hbrush;
	RECT rect;
	MyWin(char*);
	void OnPaint();
	void OnRButtonDown(UINT, CPoint);
	void OnLButtonDown(UINT, CPoint);
	void OnTimer(UINT);
	DECLARE_MESSAGE_MAP();	// объявление Карты сообщений
};

MyWin::MyWin(char* title)
{
	Create(NULL,title);
	draw=7;
	color=RGB(0, 0, 0);
	n=0;
	
}

BEGIN_MESSAGE_MAP(MyWin,CFrameWnd)	// определение Карты сообщений
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void MyWin::OnPaint()
{
	CPaintDC dc(this);
	hbrush=CreateSolidBrush(color);
	SelectObject(dc,hbrush);
	GetClientRect(&rect);
	int stepW, stepH;
	stepW=rect.right/draw;
	stepH=rect.bottom/(2*draw);
	SetTimer(0,700,0);
	char buf[10];
	for (int j=0; j<10; j++)
		buf[j]=0;
	itoa(draw, buf, 10);
	dc.TextOutA(10, 10, buf, strlen(buf));
	for (int j=0; j<n; j++)
	{	
		hbrush=CreateSolidBrush(color+j*RGB(6, 6, 6));
		SelectObject(dc,hbrush);
		dc.Rectangle(rect.left+j*stepW, rect.bottom, rect.left+(j+1)*stepW, 
			(rect.bottom/2)-stepH*j);
		if (n==draw)
			KillTimer(0);
	}
}

void MyWin::OnTimer(UINT)
{
	InvalidateRect(NULL,TRUE);
	n++;
}

void MyWin::OnLButtonDown(UINT, CPoint)
{
	CColorDialog cc(color,CC_RGBINIT);
	if (cc.DoModal()==IDOK)
	{
		color=cc.m_cc.rgbResult;
		n=0;
		SetTimer(0,700,0);
	}
}

void MyWin::OnRButtonDown(UINT, CPoint)
{
	CMyDialog dlg;
	dlg.val=draw;
	if (dlg.DoModal()==IDOK)
	{
		draw=dlg.val;
		n=0;
		SetTimer(0,700,0);
	}
}



class MyApp:CWinApp
{
public:
	BOOL InitInstance();
};

BOOL MyApp::InitInstance()
{
	m_pMainWnd = new MyWin("Hello!!!");
	m_pMainWnd->ShowWindow(SW_NORMAL);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

MyApp app;
