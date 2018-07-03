#include "stdafx.h"
#include "EditDialog.h"


EditDialog::EditDialog(CWnd* pParent) : CDialogEx(EditDialog::IDD, pParent)
{
	myNumber = 0;
	myCost = 0;
	myType = '\0';
	
}


EditDialog::~EditDialog()
{
}


void EditDialog::DoDataExchange(CDataExchange* pDX)
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUMBER, myNumber);
	DDX_Text(pDX, IDC_COST, myCost);
	DDV_MinMaxInt(pDX, myCost, 4000, 10000);
	DDX_Text(pDX, IDC_TYPE, myType);
	DDV_MaxChars(pDX, myType, 10);
}

BEGIN_MESSAGE_MAP(EditDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditDialog::OnOK)
END_MESSAGE_MAP()

void EditDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if (!UpdateData())
	{
		return;
	}
	value.number = myNumber;
	value.cost = myCost;
	value.type = myType;
	CDialogEx::OnOK();
}


BOOL EditDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	myNumber = value.number;
	myCost = value.cost;
	myType = value.type;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
