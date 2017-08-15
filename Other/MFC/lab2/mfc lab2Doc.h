
// mfc lab2Doc.h : interface of the Cmfclab2Doc class
//


#pragma once

class Cmfclab2Doc : public CDocument
{
protected: // create from serialization only
	Cmfclab2Doc();
	DECLARE_DYNCREATE(Cmfclab2Doc)

// Attributes
public:
	CArray<int> arr;
// Operations
public:
	void AddNumber();
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual	void DeleteContents();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~Cmfclab2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
