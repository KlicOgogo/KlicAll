#pragma once
#include "MFCTestKlic.h"
#include "MyData.h"
#include "afxwin.h"
#include "afxdialogex.h"
class EditDialog :
	public CDialogEx
{
	enum { IDD = IDD_DIALOG1 };
public:
	~EditDialog();
	EditDialog(CWnd* pParent = NULL);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
public:
	int myNumber, myCost;
	MyData value;
	CString myType;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	
};

