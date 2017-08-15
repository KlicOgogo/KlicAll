#include "stdafx.h"

class CMyDialog : public CDialog
{
protected:
	enum {IDD = IDD_DIALOG1};
public:
	int val;
	CMyDialog(CWnd* pParent = NULL);
	BOOL OnInitDialog();
	void OnOK();
};