
// mfc lab2Doc.cpp : implementation of the Cmfclab2Doc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mfc lab2.h"
#endif

#include "mfc lab2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cmfclab2Doc

IMPLEMENT_DYNCREATE(Cmfclab2Doc, CDocument)

BEGIN_MESSAGE_MAP(Cmfclab2Doc, CDocument)
	ON_COMMAND(ID_EDIT_ADDNUMBER, &Cmfclab2Doc::AddNumber)
END_MESSAGE_MAP()


// Cmfclab2Doc construction/destruction

Cmfclab2Doc::Cmfclab2Doc()
{
	// TODO: add one-time construction code here

}

Cmfclab2Doc::~Cmfclab2Doc()
{
}

BOOL Cmfclab2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here,
	// (SDI documents will reuse this document)

	return TRUE;
}

void Cmfclab2Doc::DeleteContents()
{
	arr.RemoveAll();
	CDocument::DeleteContents();
	return;
}


// Cmfclab2Doc serialization

void Cmfclab2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << arr.GetSize();
		for (int i=0; i<arr.GetSize(); i++)
			ar << arr[i];
		// TODO: add storing code here
	}
	else
	{
		int size;
		ar >> size;
		arr.SetSize(size);
		for (int i=0; i<arr.GetSize(); i++)
			ar >> arr[i];
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void Cmfclab2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void Cmfclab2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cmfclab2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Cmfclab2Doc diagnostics

#ifdef _DEBUG
void Cmfclab2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cmfclab2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cmfclab2Doc commands

void Cmfclab2Doc::AddNumber()
{
	CMyDialog dlg;
	if (dlg.DoModal()==IDOK)
	{
		arr.Add(dlg.val);
		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL);
	}
	return;
}