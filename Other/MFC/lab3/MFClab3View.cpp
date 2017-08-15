
// MFClab3View.cpp : implementation of the CMFClab3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFClab3.h"
#endif

#include "MFClab3Doc.h"
#include "MFClab3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFClab3View

IMPLEMENT_DYNCREATE(CMFClab3View, CFormView)

BEGIN_MESSAGE_MAP(CMFClab3View, CFormView)
	ON_BN_CLICKED(IDC_ADD, &CMFClab3View::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_REMOVE, &CMFClab3View::OnBnClickedRemove)
	ON_BN_CLICKED(IDC_FIND, &CMFClab3View::OnBnClickedFind)
END_MESSAGE_MAP()

// CMFClab3View construction/destruction

CMFClab3View::CMFClab3View()
	: CFormView(CMFClab3View::IDD)
	, myTranslation(_T(""))
	, myWord(_T(""))
	, notFind(_T(""))
{
	// TODO: add construction code here

}

CMFClab3View::~CMFClab3View()
{
}

void CMFClab3View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, myList);
	DDX_Text(pDX, IDC_TRANSLATION, myTranslation);
	DDX_Text(pDX, IDC_WORD, myWord);
	DDX_Text(pDX, IDC_NOTFIND, notFind);
	DDV_MaxChars(pDX, myWord, 15);
	DDV_MaxChars(pDX, myTranslation, 15);
}

BOOL CMFClab3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMFClab3View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	myList.ResetContent();
	CString strKey, strValue;
	CMapStringToString& myMap = GetDocument()->allData;
	POSITION pos = myMap.GetStartPosition();
	while (pos != NULL)
	{
		myMap.GetNextAssoc(pos, strKey, strValue);
		CString str = (strKey + _T(" - ") + strValue);
		myList.AddString(str);
	}
	pos = myMap.GetStartPosition();
	if (pos != NULL)
	{
		myMap.GetNextAssoc(pos, myWord, myTranslation);
	}
	else
	{
		myWord = '\0';
		myTranslation = '\0';
		notFind = '\0';
	}
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CMFClab3View diagnostics

#ifdef _DEBUG
void CMFClab3View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFClab3View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFClab3Doc* CMFClab3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFClab3Doc)));
	return (CMFClab3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFClab3View message handlers




void CMFClab3View::OnBnClickedAdd()
{
	// TODO: Add your control notification handler code here
	if (!UpdateData())
	{
		return;
	}
	int nIndex = FindKeyInList(myWord);
	if (nIndex != LB_ERR)
	{
		myList.DeleteString(nIndex);
	}
	CString term = myWord + " - " + myTranslation;
	myList.AddString(term);
	notFind = '\0';
	myList.SetCurSel(nIndex);
	GetDocument()->allData[myWord] = myTranslation;
	GetDocument()->SetModifiedFlag(TRUE);
	UpdateData(FALSE);
}

void CMFClab3View::OnBnClickedRemove()
{
	// TODO: Add your control notification handler code here
	if (!UpdateData())
	{
		return;
	}
	if (!GetDocument()->allData.Lookup(myWord, myTranslation))
	{
		notFind = "Didn't find!";
	}
	else
	{
		notFind = '\0';
		int index = FindKeyInList(myWord);
		myList.DeleteString(index);
		GetDocument()->allData.RemoveKey(myWord);
	}
	UpdateData(FALSE);
	GetDocument()->SetModifiedFlag(TRUE);
}


void CMFClab3View::OnBnClickedFind()
{
	if (!UpdateData())
	{
		return;
	}
	CString strValue;
	if (!GetDocument()->allData.Lookup(myWord, myTranslation))
	{
		notFind = "Didn't find!";
	}
	else
	{
		notFind = '\0';
		FindKeyInList(myWord);
	}
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}

int CMFClab3View::FindKeyInList(CString& strKey)
{
	CString strValue;
	if (!GetDocument()->allData.Lookup(strKey, strValue))
	{
		return LB_ERR;
	}
	CString sPattern = strKey + " - " + strValue;
	int index = -1;
	CString term("");
	do
	{
		index = myList.FindStringExact(index, sPattern);
		myList.GetText(index, term);
		if (term == sPattern)
		{
			break;
		}
	} while (TRUE);
	myList.SetTopIndex(index);
	myList.SetCurSel(index);
	return index;
}
	