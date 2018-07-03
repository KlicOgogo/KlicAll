
// MFCTestKlicView.h : interface of the CMFCTestKlicView class
//

#pragma once

#include "resource.h"


class CMFCTestKlicView : public CFormView
{
protected: // create from serialization only
	CMFCTestKlicView();
	DECLARE_DYNCREATE(CMFCTestKlicView)

public:
	enum{ IDD = IDD_MFCTESTKLIC_FORM };

// Attributes
public:
	CMFCTestKlicDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMFCTestKlicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	CListBox myList;
	afx_msg void OnAdd();
	afx_msg void OnEdit();
	afx_msg void OnDelete();
	afx_msg void OnDrawDiagramm();
};

#ifndef _DEBUG  // debug version in MFCTestKlicView.cpp
inline CMFCTestKlicDoc* CMFCTestKlicView::GetDocument() const
   { return reinterpret_cast<CMFCTestKlicDoc*>(m_pDocument); }
#endif
