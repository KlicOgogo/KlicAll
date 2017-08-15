
// MFCTestKlic.h : main header file for the MFCTestKlic application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCTestKlicApp:
// See MFCTestKlic.cpp for the implementation of this class
//

class CMFCTestKlicApp : public CWinApp
{
public:
	CMFCTestKlicApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCTestKlicApp theApp;
