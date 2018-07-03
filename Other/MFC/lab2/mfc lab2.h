
// mfc lab2.h : main header file for the mfc lab2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "MyDialog.h"

// Cmfclab2App:
// See mfc lab2.cpp for the implementation of this class
//

class Cmfclab2App : public CWinApp
{
public:
	Cmfclab2App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cmfclab2App theApp;
