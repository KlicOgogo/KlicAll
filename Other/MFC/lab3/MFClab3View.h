
// MFClab3View.h : interface of the CMFClab3View class
//

#pragma once

#include "resource.h"
#include "afxwin.h"


class CMFClab3View : public CFormView
{
protected: // create from serialization only
	CMFClab3View();
	DECLARE_DYNCREATE(CMFClab3View)

public:
	enum{ IDD = IDD_MFCLAB3_FORM };

// Attributes
public:
	CMFClab3Doc* GetDocument() const;

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
	virtual ~CMFClab3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedReplace();
	afx_msg void OnBnClickedRemove();
	afx_msg void OnBnClickedFind();
	int FindKeyInList(CString& strKey);
	CListBox myList;
	CString myTranslation;
	CString myWord;
	CString notFind;
};

#ifndef _DEBUG  // debug version in MFClab3View.cpp
inline CMFClab3Doc* CMFClab3View::GetDocument() const
   { return reinterpret_cast<CMFClab3Doc*>(m_pDocument); }
#endif

