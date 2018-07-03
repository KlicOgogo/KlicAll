
// MFClab3.h : main header file for the MFClab3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFClab3App:
// See MFClab3.cpp for the implementation of this class
//

class CMFClab3App : public CWinApp
{
public:
	CMFClab3App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFClab3App theApp;
