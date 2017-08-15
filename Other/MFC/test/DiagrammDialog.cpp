#include "stdafx.h"
#include "DiagrammDialog.h"
using namespace std;

DiagrammDialog::DiagrammDialog(CWnd* pParent) : CDialogEx(DiagrammDialog::IDD, pParent){}


DiagrammDialog::~DiagrammDialog()
{
}
BEGIN_MESSAGE_MAP(DiagrammDialog, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void DiagrammDialog::OnPaint()
{
	CPaintDC dc(this);
	RECT rect;
	GetClientRect(&rect);
	int width = rect.right / draw.size();
	int max = 0;
	for (map<CString, int>::iterator it = draw.begin(); it != draw.end(); it++)
	{
		if (it->second > max)
		{
			max = it->second;
		}
	}
	int height = rect.bottom / max;
	int i = 0;
	for (map<CString, int>::iterator it = draw.begin(); it != draw.end(); it++)
	{
		dc.SelectObject(CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		dc.Rectangle(i*width, rect.bottom, (i+1)*width, rect.bottom-it->second*height);
		CString out;
		out.Format(TEXT("%s: %d"), it->first, it->second);
		dc.TextOutW(i*width, rect.bottom - 15, out);
		i++;
	}
	// device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
}
