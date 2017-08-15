
// MFCTestKlicView.cpp : implementation of the CMFCTestKlicView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCTestKlic.h"
#endif

#include "MFCTestKlicDoc.h"
#include "MFCTestKlicView.h"
#include "EditDialog.h"
#include "DiagrammDialog.h"
#include "MyData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// CMFCTestKlicView

IMPLEMENT_DYNCREATE(CMFCTestKlicView, CFormView)

BEGIN_MESSAGE_MAP(CMFCTestKlicView, CFormView)
	ON_BN_CLICKED(IDC_ADD, &CMFCTestKlicView::OnAdd)
	ON_BN_CLICKED(IDC_EDIT, &CMFCTestKlicView::OnEdit)
	ON_BN_CLICKED(IDC_DELETE, &CMFCTestKlicView::OnDelete)
	ON_BN_CLICKED(IDC_DIAGRAMM, &CMFCTestKlicView::OnDrawDiagramm)
END_MESSAGE_MAP()

// CMFCTestKlicView construction/destruction

CMFCTestKlicView::CMFCTestKlicView()
	: CFormView(CMFCTestKlicView::IDD)
{
	// TODO: add construction code here

}

CMFCTestKlicView::~CMFCTestKlicView()
{
}

void CMFCTestKlicView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, myList);
}

BOOL CMFCTestKlicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMFCTestKlicView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	myList.ResetContent();
	CMFCTestKlicDoc* pDoc = GetDocument();
	for (int i = 0; i < pDoc->allData.GetSize(); i++)
	{
		myList.AddString(pDoc->allData[i].ToString());
	}
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	UpdateData(FALSE);
}


// CMFCTestKlicView diagnostics

#ifdef _DEBUG
void CMFCTestKlicView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCTestKlicView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCTestKlicDoc* CMFCTestKlicView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCTestKlicDoc)));
	return (CMFCTestKlicDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCTestKlicView message handlers
void CMFCTestKlicView::OnAdd()
{
	EditDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
			
		CMFCTestKlicDoc* pDoc = GetDocument();
		pDoc->allData.Add(dlg.value);
		myList.AddString(dlg.value.ToString());
		pDoc->SetModifiedFlag(TRUE);
	}
}

void CMFCTestKlicView::OnEdit()
{
	EditDialog dlg;
	int place = myList.GetCurSel();
	if (place != LB_ERR)
	{
		CMFCTestKlicDoc* pDoc = GetDocument();
		dlg.value = pDoc->allData[place];
		if (dlg.DoModal() == IDOK)
		{
			CMFCTestKlicDoc* pDoc = GetDocument();
			pDoc->allData[place] = dlg.value;
			myList.DeleteString(place);
			myList.AddString(dlg.value.ToString());
			pDoc->SetModifiedFlag(TRUE);
		}
	}
}


void CMFCTestKlicView::OnDelete()
{
	if (!UpdateData())
	{
		return;
	}
	int place = myList.GetCurSel();
	if (place!=LB_ERR)
	{ 
		CMFCTestKlicDoc* pDoc = GetDocument();
		pDoc->allData.RemoveAt(place, 1);
		myList.DeleteString(place);
		UpdateData(FALSE);
		GetDocument()->SetModifiedFlag(TRUE);
	}
}


void CMFCTestKlicView::OnDrawDiagramm()
{
	DiagrammDialog dlg;
	map<CString, int> data;
	CMFCTestKlicDoc* pDoc = GetDocument();
	for (int i = 0; i < pDoc->allData.GetSize(); i++)
	{
		data[pDoc->allData[i].type]++;
	}
	dlg.draw = data;
	dlg.DoModal();
}
