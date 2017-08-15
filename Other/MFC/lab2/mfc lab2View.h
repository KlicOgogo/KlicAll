
// mfc lab2View.h : interface of the Cmfclab2View class
//

#pragma once


class Cmfclab2View : public CView
{
protected: // create from serialization only
	Cmfclab2View();
	DECLARE_DYNCREATE(Cmfclab2View)

// Attributes
public:
	Cmfclab2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~Cmfclab2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfc lab2View.cpp
inline Cmfclab2Doc* Cmfclab2View::GetDocument() const
   { return reinterpret_cast<Cmfclab2Doc*>(m_pDocument); }
#endif

