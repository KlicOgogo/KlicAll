
// mfc lab2View.cpp : implementation of the Cmfclab2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mfc lab2.h"
#endif

#include "mfc lab2Doc.h"
#include "mfc lab2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmfclab2View

IMPLEMENT_DYNCREATE(Cmfclab2View, CView)

BEGIN_MESSAGE_MAP(Cmfclab2View, CView)
END_MESSAGE_MAP()

// Cmfclab2View construction/destruction

Cmfclab2View::Cmfclab2View()
{
	// TODO: add construction code here

}

Cmfclab2View::~Cmfclab2View()
{
}

BOOL Cmfclab2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cmfclab2View drawing

void Cmfclab2View::OnDraw(CDC* pDC)
{
	Cmfclab2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	if (pDoc->arr.IsEmpty())
		return;
	RECT rect;
	GetClientRect(&rect);
	double wi=rect.right/pDoc->arr.GetSize();
	double w1=(rect.right)*1./(pDoc->arr.GetSize());
	double max=0;
	for (int i=0; i<pDoc->arr.GetSize(); i++)
	{
		if (pDoc->arr[i]>max)
			max=pDoc->arr[i];
	}
	double h1=(rect.bottom)*1./max;
	for(int i=0; i<pDoc->arr.GetSize(); i++)
	{	
		HBRUSH hBrush = CreateSolidBrush(RGB(rand()%255,rand()%255,rand()%255));
		SelectObject(*pDC,hBrush);
		pDC->Rectangle(i*w1,rect.bottom,(i+1)*w1,rect.bottom-(pDoc->arr[i]*h1) );
		CString out;
		char buf[30];
		out.Format(_T("%d"), pDoc->arr[i]);
		//sprintf(buf,"%d",pDoc->arr[i]);
		pDC->TextOutW(i*w1, rect.bottom-15, out);
		DeleteObject(hBrush);
	}

}


// Cmfclab2View diagnostics

#ifdef _DEBUG
void Cmfclab2View::AssertValid() const
{
	CView::AssertValid();
}

void Cmfclab2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cmfclab2Doc* Cmfclab2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cmfclab2Doc)));
	return (Cmfclab2Doc*)m_pDocument;
}
#endif //_DEBUG


// Cmfclab2View message handlers
