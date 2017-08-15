#pragma once
#include "MFCTestKlic.h"
#include "afxdialogex.h"
#include <map>
using namespace std;

class DiagrammDialog :
	public CDialogEx
{
public:
	enum { IDD = IDD_DIAGRAMM };
	DiagrammDialog(CWnd* pParent = NULL);
	~DiagrammDialog();
	map<CString, int> draw;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};
