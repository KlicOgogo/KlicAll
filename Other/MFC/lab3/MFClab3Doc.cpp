
// MFClab3Doc.cpp : implementation of the CMFClab3Doc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFClab3.h"
#endif

#include "MFClab3Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFClab3Doc

IMPLEMENT_DYNCREATE(CMFClab3Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFClab3Doc, CDocument)
END_MESSAGE_MAP()


// CMFClab3Doc construction/destruction

CMFClab3Doc::CMFClab3Doc()
{
	// TODO: add one-time construction code here

}

CMFClab3Doc::~CMFClab3Doc()
{
}

BOOL CMFClab3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFClab3Doc serialization

void CMFClab3Doc::Serialize(CArchive& ar)
{
	allData.Serialize(ar);
}

void CMFClab3Doc::OnDeleteContents()
{
	allData.RemoveAll();
	CDocument::DeleteContents();
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFClab3Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMFClab3Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFClab3Doc::SetSearchContent(const CString& value)
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

// CMFClab3Doc diagnostics

#ifdef _DEBUG
void CMFClab3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFClab3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFClab3Doc commands
