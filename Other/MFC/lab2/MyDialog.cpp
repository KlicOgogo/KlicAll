#include <afxwin.h>
#include "stdafx.h"
#include "resource.h"
#include "MyDialog.h"

BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();	
	SetDlgItemInt(IDC_EDIT2, 200);
	return true;
}

void CMyDialog::OnOK()
{
	val=GetDlgItemInt(IDC_EDIT2);
	CDialog::OnOK();
}

CMyDialog:: CMyDialog(CWnd* pParent) : CDialog(CMyDialog::IDD, pParent){}