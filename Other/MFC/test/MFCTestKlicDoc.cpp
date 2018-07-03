
// MFCTestKlicDoc.cpp : implementation of the CMFCTestKlicDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCTestKlic.h"
#endif

#include "MFCTestKlicDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCTestKlicDoc

IMPLEMENT_DYNCREATE(CMFCTestKlicDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCTestKlicDoc, CDocument)
END_MESSAGE_MAP()


// CMFCTestKlicDoc construction/destruction

CMFCTestKlicDoc::CMFCTestKlicDoc()
{
	// TODO: add one-time construction code here

}

CMFCTestKlicDoc::~CMFCTestKlicDoc()
{
}

BOOL CMFCTestKlicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCTestKlicDoc serialization

void CMFCTestKlicDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << allData.GetSize();
		for (int i = 0; i < allData.GetSize(); i++)
			allData[i].Serialize(ar);
		// TODO: add storing code here
	}
	else
	{
		int mySize;
		ar >> mySize;
		allData.SetSize(mySize);
		for (int i = 0; i < allData.GetSize(); i++)
			allData[i].Serialize(ar);
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCTestKlicDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMFCTestKlicDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCTestKlicDoc::SetSearchContent(const CString& value)
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

// CMFCTestKlicDoc diagnostics

#ifdef _DEBUG
void CMFCTestKlicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCTestKlicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCTestKlicDoc commands

void CMFCTestKlicDoc::DeleteContents()
{
	allData.RemoveAll();
	CDocument::DeleteContents();
}